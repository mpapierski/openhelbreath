#include <string>

#include "NetSock.h"
#include "Threading.h"
#include "Callback.h"

#ifdef WINDOWS
#	include <windows.h>
#	include <winsock.h>
#endif

#ifdef WINDOWS
bool InitWinsock();
#endif

//#include <sigc++/sigc++.h>
class SocketCallbacks
{
	public:
		virtual void Connected(void*) {};
		virtual void Disconnected(void*) {};
		virtual void Received(void*, char*) {};
};


class BaseTcpClient: public SocketCallbacks
{
	public:
		string m_sAddress;
		int m_iPort;
		NetSock * m_pSock;
		bool m_bConnected;
		BaseTcpClient(string sAddress, int iPort);
		virtual ~BaseTcpClient();
		bool Connect();
		void Disconnect();
};

class TcpClient : public BaseTcpClient, public CThread
{
	public:
		CallBack<SocketCallbacks, void, void*> * cbConnect;
		CallBack<SocketCallbacks, void, void*> * cbDisconnect;
		CallBack<SocketCallbacks, void, void*, char*> * cbReceive;

		TcpClient(string sAddress, int iPort) : BaseTcpClient(sAddress, iPort), CThread()
		{
					
		};
		void run();
};
