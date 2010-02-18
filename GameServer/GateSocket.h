#ifndef GATESOCKET_H
#define GATESOCKET_H

#include <string>
#include "Threading.h"
#include "NetSock.h"
#include "GlobalDef.h"
#include "NetMessages.h"

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
		CGateConnector();
		~CGateConnector();
		bool m_bIsConnected;
		void __Reader(int iSockIndex, unsigned char *pBuffer);
		void __Connect();
		void __Connected(int iSockIndex);
		void __Disconnected(int iSockIndex);
		void run();
};
#endif
