#include "Socket.h"

void Socket::Run()
{
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_NETWORK_INIT;
	Ev.user.data1 = Connection;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);
	bool OK = Connection->Connect(Address.c_str(), Port);
	Ev.user.code = OK ? SDL_NETWORK_CONNECTED : SDL_NETWORK_ERROR;
	Ev.user.data1 = Connection;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);

	while (Connection != 0 && OK)
	{
		FD_ZERO(&Reader);
		FD_SET((unsigned int)Connection->socket, &Reader);
		int Ret = select(Connection->socket + 1, &Reader, (fd_set*) 0,
				(fd_set*) 0, &Timeout);
		if (Ret == -1)
		{
			KillSocket();
			break;
		}
		if (FD_ISSET(Connection->socket, &Reader))
			OnDataPresent();
		else
		{
			Ev.user.code = SDL_NETWORK_BUSY;
			Ev.user.data1 = Connection;
			Ev.user.data2 = 0;
			SDL_PushEvent(&Ev);
		}
	}
	Ev.user.code = SDL_NETWORK_FINISH;
	Ev.user.data1 = Connection;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);
}
void Socket::OnDataPresent()
{
	if (!Data->receive(Connection))
	{
		SDL_Event Ev;
		Ev.type = SDL_USEREVENT;
		Ev.user.code = SDL_NETWORK_CLOSED;
		Ev.user.data1 = Connection;
		Ev.user.data2 = 0;
		SDL_PushEvent(&Ev);
		KillSocket();
		return;
	}
	unsigned short packetSize;

	while (true)
	{
		memcpy(&packetSize, Data->data() + 1, 2);

		if (packetSize <= Data->size() && packetSize > 0)
		{
			unsigned char cKey = Data->next<unsigned char> ();
			unsigned short dwSize = Data->next<unsigned short> ();

			if (cKey > 0)
			{
				char * buf = Data->data();
				for (int i = 0; i < dwSize - 3; i++)
				{
					buf[i] ^= (cKey ^ (dwSize - i - 3));
					buf[i] -= i ^ cKey;
				}
			}
			Readable(dwSize);
		}
		else
			break;
	}
}
void Socket::Readable(int SizeHeader)
{
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_NETWORK_RECEIVE;
	Ev.user.data1 = Connection;
	Buffer * copybuffer = new Buffer(SizeHeader);
	copybuffer->clear();
	memcpy(copybuffer->writeptr(), Data->data(), SizeHeader);
	copybuffer->_written(SizeHeader);
	Data->seek(SizeHeader);
	Ev.user.data2 = copybuffer;
	SDL_PushEvent(&Ev);
}
inline bool Socket::IsConnected() const
{
	return this->Connected;
}

Socket::~Socket()
{
	KillSocket();
	delete Data;
}
void Socket::KillSocket()
{
	if (Connection != 0)
	{
		delete Connection;
		Connection = 0;
	}

	Connected = false;
}

Socket::Socket(std::string Addr, int Port)
{
	Connected = false;
	Connection = 0;
	Connection = new NetSock();
	Connection->SetMode(NetSock::ASYNCHRONIC);
	Data = new Buffer(DEF_BUFFERSIZE);
	Timeout.tv_sec = 1;
	Timeout.tv_usec = 0;
	this->Address = Addr;
	this->Port = Port;
}

bool Socket::Connect()
{
	if (Connection == 0)
		return false;
	this->Start();
	return true;
}

void Socket::Disconnect()
{
	Connection->Disconnect();
	Connected = false;
}
