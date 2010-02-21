#include "GateSocket.h"
#include "GameServer.h"

CGateConnector::CGateConnector()
{
	//
	puts("CGateConnector constructor...");
	for (int i = 0; i < DEF_MAXGATESOCKET;i++)
	{
		m_pBuffer[i] = new Buffer(DEF_BUFFERSIZE);
	}

}


CGateConnector::~CGateConnector()
{
	//
	puts("CGateConnector destructor...");
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
		if (m_pSocket[i])
		{
			delete m_pSocket[i];
			delete m_pBuffer[i];
		}
}

int
CGateConnector::__BuildList()
{
	FD_ZERO(&socks_r);
	highsock = 0;
	int c = 0;
	for (unsigned int i = 0; i<DEF_MAXGATESOCKET; i++)
		if (m_pSocket[i] != NULL)
		{
			FD_SET((unsigned int)m_pSocket[i]->socket, &socks_r);
			c++;
			if (m_pSocket[i]->socket > highsock)
				highsock = m_pSocket[i]->socket;
		}
	return c;
}

void
CGateConnector::__Connect()
{
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		m_pSocket[i] = new NetSock;
		if (m_pSocket[i]->Connect(GameServer::getInstance().m_sGateServerAddr.c_str(), GameServer::getInstance().m_iGateServerPort))
		{
			printf("(*) Connection-%d established!\n", i);
			__Connected(i);
		} else {
			printf("(!) Failed on connection-%d\n", i);
		}	
	}
}

void
CGateConnector::__Connected(int iSockIndex)
{
	if (iSockIndex == 0)
	{
		printf("(!) Try to register game server(%s)\n", GameServer::getInstance().m_sServerName.c_str());
		Packet p(MSGID_REQUEST_REGISTERGAMESERVER, DEF_MSGTYPE_CONFIRM);
		p.push<char>(GameServer::getInstance().m_sServerName.c_str(), 10);
		p.push<char>(GameServer::getInstance().m_sGameServerAddr.c_str(), 16);
		p.push<unsigned short>(GameServer::getInstance().m_iGameServerPort);
		p.push<bool>(false); //Do I have configs?
		int iTotalMaps = GameServer::getInstance().m_pMapList.size();
		p.push<unsigned char>(iTotalMaps);
		p.push<unsigned short>(123); //Server ID; TODO : Send process ID ?
		for (int i = 0; i < iTotalMaps; i++)
			p.push<char>(GameServer::getInstance().m_pMapList[i].m_sMapName.c_str(), 11);
		m_pSocket[iSockIndex]->Write((unsigned char*)p.data(), p.size());
	} 
}

void
CGateConnector::run()
{
	__Connect();
	
	m_bIsConnected = false;
	while (true)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		if (__BuildList() == 0)
		{
			puts("(!!!) Lost connection to Login Server!\n");
			break;
		}
		
		readsocks = select(highsock+1, &socks_r, (fd_set*)0, (fd_set*)0,&timeout);
		
		if (readsocks == -1)
		{
			puts("(!!!) CRITICAL ERROR. SELECT() == -1!\n");
			break;
		} else {
			for (int i = 0; i< DEF_MAXGATESOCKET;i++)
			{
				if (FD_ISSET(m_pSocket[i]->socket, &socks_r) && (m_pSocket[i] != NULL))
				{
					__DataAvail(i);
				}
			}
		}
	}
}
void
CGateConnector::_RegisterSockets()
{
	Packet p(MSGID_REQUEST_REGISTERGAMESERVERSOCKET, m_wGSID);
	for (int i = 1; i < DEF_MAXGATESOCKET; i++)
	{
		printf("(!) Try to register game server socket(%d) on ID[%d]\n", i, m_wGSID);
		m_pSocket[i]->Write((unsigned char*)p.data(), p.size());
	}
}
void
CGateConnector::__Reader(int iSockIndex)
{
	unsigned int dwMsgID = m_pBuffer[iSockIndex]->next<int>();
	unsigned short wMsgType = m_pBuffer[iSockIndex]->next<unsigned short>();

	switch (dwMsgID)
	{
		case MSGID_RESPONSE_REGISTERGAMESERVER:
			switch (wMsgType)
			{
				case DEF_MSGTYPE_CONFIRM:
					m_wGSID = m_pBuffer[iSockIndex]->next<unsigned short>();
					printf("(!) Game Server registration to Log Server - Success! GSID[%d]\n", m_wGSID);
					_RegisterSockets();
					break;
				case DEF_MSGTYPE_REJECT:
					puts("(!) Game Server registration to Log Server - Fail!");
					break;
			}
			break;
	}
}

void
CGateConnector::__Disconnected(int iSockIndex)
{
	//Reconnecting
	printf("(!!!) Lost connection to login server on socket-%d.\n", iSockIndex);
}

void
CGateConnector::__DataAvail(int iSockIdx)
{
	int iReadCount = m_pSocket[iSockIdx]->Read((unsigned char*)m_pBuffer[iSockIdx]->writeptr(), m_pBuffer[iSockIdx]->spaceAvailable());

	if (iReadCount > 0)
	{
		m_pBuffer[iSockIdx]->_written(iReadCount);
	} else
	{
		__Disconnected(iSockIdx);
		delete m_pSocket[iSockIdx];
		return;
	}
	
	unsigned short packetSize;
	
	while(true)
	{	
		memcpy(&packetSize, m_pBuffer[iSockIdx]->data() + 1, 2);
		if (packetSize <= m_pBuffer[iSockIdx]->size())
		{
			int _before = m_pBuffer[iSockIdx]->pos();
			unsigned char cKey = m_pBuffer[iSockIdx]->next<unsigned char>();
			unsigned short dwSize = m_pBuffer[iSockIdx]->next<unsigned short>();
			
			if (cKey > 0)
			{
				char * buf = m_pBuffer[iSockIdx]->data();
				for (int i = 0; i < dwSize-3; i++)
				{
					buf[i] = (char)(buf[i] ^ (cKey ^ (char)(dwSize - i)));
					buf[i] -= (char)((char)i ^ cKey);
				}
			}
			__Reader(iSockIdx);
			
			int _readcount = _before - m_pBuffer[iSockIdx]->pos();
			m_pBuffer[iSockIdx]->seek(dwSize-_readcount);
		}
		else
			break;
	}
}
