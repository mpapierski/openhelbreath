/*
 This file is part of OpenHelbreath.
 OpenHelbreath is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenHelbreath is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GATESOCKET_H
#define GATESOCKET_H

#include <string>
#include "Threading.h"
#include "NetSock.h"
#include "GlobalDef.h"
#include "NetMessages.h"
#include "Buffers.h"

class CGateConnector: public Thread
{
	private:
		fd_set SocksSet;

		struct timeval Timeout;
		int ReadSocks;
		int HighSock;
		int BuildList();

		int CurrentSocket;
	public:
		NetSock * Sockets[DEF_MAXGATESOCKET];
		Buffer * Buffers[DEF_MAXGATESOCKET];
		CGateConnector();
		~CGateConnector();

		NetSock * GetSock();

		bool IsConnected;
		unsigned short GSID;
		void __Reader(int iSockIndex);
		bool Connect();
		void OnConnected(int iSockIndex);
		void OnDisconnected(int iSockIndex);
		void OnDataAvailable(int iSockIdx);
		void RegisterSockets();
		void Run();
};
#endif
