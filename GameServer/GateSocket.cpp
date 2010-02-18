#include "GateSocket.h"
#include "GameServer.h"

CGateConnector::CGateConnector()
{
	//
	puts("CGateConnector constructor...");
}


CGateConnector::~CGateConnector()
{
	//
	puts("CGateConnector destructor...");
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
		if (m_pSocket[i])
		{
			delete m_pSocket[i];
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
	
	char asdf[100];
	sprintf(asdf,"Hello from %d socket!\n", iSockIndex);
	m_pSocket[iSockIndex]->Write((unsigned char*)&asdf, strlen(asdf));
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
			unsigned char Buffer[DEF_BUFFERSIZE];
			for (int i = 0; i< DEF_MAXGATESOCKET;i++)
			{
				if (FD_ISSET(m_pSocket[i]->socket, &socks_r) && (m_pSocket[i] != NULL))
				{
					memset(Buffer, 0, DEF_BUFFERSIZE);
					int iResult = m_pSocket[i]->Read(Buffer, sizeof(Buffer));
					if (iResult <= 0)
					{
						delete m_pSocket[i];		
						__Disconnected(i);
						continue;
					} else {
						__Reader(i, Buffer);
					}
				}
			}
		}
	}
}

void
CGateConnector::__Reader(int iSockIndex, unsigned char *pBuffer)
{
	printf("Sock-%d: %s\n", iSockIndex, (char*)pBuffer);
}

void
CGateConnector::__Disconnected(int iSockIndex)
{
	//Reconnecting
	printf("(!!!) Lost connection to login server on socket-%d.\n", iSockIndex);
}
