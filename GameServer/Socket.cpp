#include "GlobalDef.h"
#include "Socket.h"

#ifdef WINDOWS
bool
InitWinsock()
{
	WSADATA wsdat;
	memset(&wsdat,0,sizeof(wsdat));
	if(WSAStartup(0x0101,&wsdat))
	{
    		throw "WSAStartup() failed.";
    		return false;
	}
	return true;
}
#endif

BaseTcpClient::BaseTcpClient(string sAddress, int iPort)
{
	m_pSock = new NetSock();
	m_sAddress = sAddress;
	m_iPort = iPort;
}

BaseTcpClient::~BaseTcpClient()
{
	Disconnect();
}

bool
BaseTcpClient::Connect()
{
	if (m_bConnected)
		return false;
	bool bStatus = m_pSock->Connect(m_sAddress.c_str(), m_iPort);
	m_bConnected = bStatus;
	return bStatus;
}

void
BaseTcpClient::Disconnect()
{
	if (m_pSock)
	{
		if (m_bConnected)
			m_pSock->Disconnect();
		delete m_pSock;
		m_bConnected = false;
	}
}
void
TcpClient::run()
{
	if (Connect())
	{
		(*cbConnect)(this);
		int iResult = 0;
		unsigned char Buffer[1024*1024];
		do
		{
			iResult = m_pSock->Read(Buffer, sizeof(Buffer));
			(*cbReceive)(this, (char*)Buffer);
			if (iResult == 0)
			{
				break;
			}
		} while (iResult > 0);
	}
	else
	{
		//puts("Not connected");
		
		//Not connected
	}
	puts("TcpClient thread ends...");
	(*cbDisconnect)(this);
	//Done
}
