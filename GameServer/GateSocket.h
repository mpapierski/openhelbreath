#ifndef GATESOCKET_H
#define GATESOCKET_H

#include <string>
#include "Threading.h"
#include "NetSock.h"
#include "GlobalDef.h"
#include "NetMessages.h"
#include "Buffers.h"

class CGateConnector : public CThread
{
	private:
		fd_set socks_r;

		struct timeval timeout;
		int readsocks;
		int highsock;
		int __BuildList();
	public:
		NetSock * m_pSocket[DEF_MAXGATESOCKET];
		Buffer * m_pBuffer[DEF_MAXGATESOCKET];
		CGateConnector();
		~CGateConnector();
		bool m_bIsConnected;
		unsigned short m_wGSID;
		void __Reader(int iSockIndex);
		bool bConnect();
		void __Connected(int iSockIndex);
		void __Disconnected(int iSockIndex);
		void __DataAvail(int iSockIdx);
		void _RegisterSockets();
		void run();
};
#endif
