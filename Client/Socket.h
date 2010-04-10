#ifndef SOCKET_H_
#define SOCKET_H_

#include <SDL.h>
#include <string>

#include "NetSock.h"
#include "Threading.h"
#include "Buffers.h"
#include "GlobalDef.h"

class Socket : public Thread
{
	private:
		bool Connected;
		void KillSocket();
	public:
		Socket(std::string Addr, int Port);
		virtual ~Socket();
		void Run();
		inline bool IsConnected() const;
		bool Connect();
		void OnDataPresent();
		void Readable(int SizeHeader);
		void Disconnect();
		static int Wrapper(void* param);
		std::string Address;
		int Port;
		fd_set Reader;
		struct timeval Timeout;
		NetSock * Connection;
		Buffer * Data;
};
#endif /* SOCKET_H_ */
