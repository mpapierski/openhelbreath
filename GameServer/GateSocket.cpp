#include "GateSocket.h"
#include "GameServer.h"

CGateConnector::CGateConnector()
{
	for (int i = 0; i < DEF_MAXGATESOCKET;i++)
	{
		m_pBuffer[i] = new Buffer(DEF_BUFFERSIZE);
		m_pSocket[i] = NULL;
	}
	m_bIsConnected = false;
	__currsocket = 0;
}


CGateConnector::~CGateConnector()
{
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		if (m_pSocket[i] != NULL)
		{
			delete m_pSocket[i];
			m_pSocket[i] = NULL;
		}
		delete m_pBuffer[i];
		m_pBuffer[i] = NULL;
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

bool
CGateConnector::bConnect()
{
	int iRet = 0;
	char _buf[100];
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		m_pSocket[i] = new NetSock;
		memset(_buf, 0, sizeof(_buf));
		if (m_pSocket[i]->Connect(GameServer::getInstance().m_sGateServerAddr.c_str(), GameServer::getInstance().m_iGateServerPort))
		{
			sprintf(_buf, "(*) Connection-%d established!", i);
			GameServer::getInstance().PutLog(_buf);
			iRet += 1;
			__Connected(i);
		} else {
			sprintf(_buf, "(!) Failed on connection-%d", i);
			GameServer::getInstance().PutLog(_buf);
			delete m_pSocket[i];
			m_pSocket[i] = NULL;
		}	
	}
	return iRet == DEF_MAXGATESOCKET;
}

void
CGateConnector::__Connected(int iSockIndex)
{
	if (iSockIndex == 0)
	{
		GameServer::getInstance().PutLog("(!) Try to register game server(" + GameServer::getInstance().m_sServerName + ")");
		Packet p(MSGID_REQUEST_REGISTERGAMESERVER, DEF_MSGTYPE_CONFIRM);
		p.push<char>(GameServer::getInstance().m_sServerName.c_str(), 10);
		p.push<char>(GameServer::getInstance().m_sGameServerAddr.c_str(), 16);
		p.push<unsigned short>(GameServer::getInstance().m_iGameServerPort);
		p.push<bool>(false); //Do I have configs?
		int iTotalMaps = GameServer::getInstance().m_pMapList.size();
		p.push<unsigned char>(iTotalMaps);
		p.push<unsigned short>(getpid()); //Server ID
		for (int i = 0; i < iTotalMaps; i++)
			p.push<char>(GameServer::getInstance().m_pMapList[i].m_sMapName.c_str(), 11);
		m_pSocket[iSockIndex]->Write((unsigned char*)p.data(), p.size());
	} 
}

void
CGateConnector::run()
{
	m_bIsConnected = false;
	
	if (!bConnect())
	{
		GameServer::getInstance().PutLog("(!!!) Could not connect to gate server.");
		return;
	}

	while (true)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		if (__BuildList() == 0)
		{
			GameServer::getInstance().PutLog("(!!!) Lost connection to Login Server!");
			break;
		}
		
		readsocks = select(highsock+1, &socks_r, (fd_set*)0, (fd_set*)0,&timeout);
		
		if (readsocks == -1)
		{
			GameServer::getInstance().PutLog("(!!!) CRITICAL ERROR. SELECT() == -1!");
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
		char _buf[100];
		sprintf(_buf, "(!) Try to register game server socket(%d) on ID[%d]", i, m_wGSID);
		GameServer::getInstance().PutLog(_buf);
		m_pSocket[i]->Write((unsigned char*)p.data(), p.size());
	}
	m_bIsConnected = true;
}
void
CGateConnector::__Reader(int iSockIndex)
{
	unsigned int dwMsgID = m_pBuffer[iSockIndex]->next<int>();
	unsigned short wMsgType = m_pBuffer[iSockIndex]->next<unsigned short>();
	char _buf[100];
	switch (dwMsgID)
	{
		case MSGID_RESPONSE_REGISTERGAMESERVER:
			switch (wMsgType)
			{
				case DEF_MSGTYPE_CONFIRM:
					m_wGSID = m_pBuffer[iSockIndex]->next<unsigned short>();
					sprintf(_buf, "(!) Game Server registration to Log Server - Success! GSID[%d]", m_wGSID);
					GameServer::getInstance().PutLog(_buf);
					_RegisterSockets();
					break;
				case DEF_MSGTYPE_REJECT:
					GameServer::getInstance().PutLog("(!) Game Server registration to Log Server - Fail!");
					break;
			}
			break;
		case MSGID_ITEMCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) ITEM configuration contents received. Now decoding...");
			int iCount = m_pBuffer[iSockIndex]->next<int>();
			for (int i = 0; i < iCount; i++)
			{
				// Copy record one by one from buffer
				CItem _item;
				memcpy(&_item, m_pBuffer[iSockIndex]->data(), sizeof(CItem));
				// Move buffer +sizeof(CItem) bytes
				m_pBuffer[iSockIndex]->seek(sizeof(CItem));
				// Push item to m_pItemConfig list
				GameServer::getInstance().m_pItemConfig.push_back(_item);
			}
			memset(_buf, 0, sizeof(_buf));
			sprintf(_buf,"(!) ITEM(Total:%d) configuration - success!", iCount);
			GameServer::getInstance().PutLog(_buf);
			break;
	}
}

void
CGateConnector::__Disconnected(int iSockIndex)
{
	//Reconnecting
	char _buf[100];
	sprintf(_buf, "(!!!) Lost connection to login server on socket-%d.", iSockIndex);
	GameServer::getInstance().PutLog(_buf);
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

NetSock*
CGateConnector::pGetSock()
{
	int idx = __currsocket;
	__currsocket += 1;
	if (__currsocket > DEF_MAXGATESOCKET)
		__currsocket = 0;
	return m_pSocket[idx];
}
