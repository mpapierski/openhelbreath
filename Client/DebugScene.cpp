#include "Game.h"

DebugScene::DebugScene()
{
	rect = Surface::CreateSurface(640 - 100, 480 - 100, 255, 255, 255, 128);

	TextSurface = NULL;

	Print("Press ESC to exit Debug console");

	state = 0;
	MLSocket = 0;
}

DebugScene::~DebugScene()
{
	SDL_FreeSurface(rect);
	SDL_FreeSurface(TextSurface);

	if (MLSocket != 0)
	{
		delete MLSocket;
		MLSocket = 0;
	}
}

void DebugScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0,
			SPRID_LOGIN_BACKGROUND);

	Surface::Draw(Dest, rect, 50, 50);

	int y = 0;
	int size = (int) backlog.size();
	int start = size - 19;
	if (start < 0)
		start = 0;

	for (int i = start; i < size; i++)
	{
		if (i >= size)
			break;
		Font::PutText(Dest, 55, 53 + y, backlog[i], 0, 0, 0);
		y += 20;
	}
}

void DebugScene::OnLoop()
{

}
void DebugScene::OnEvent(SDL_Event *EventSource)
{
	if (EventSource->type == SDL_USEREVENT)
	{
		switch (EventSource->user.code)
		{
			case SDL_NETWORK_ERROR:
				Print("ERROR");
				break;
			case SDL_NETWORK_INIT:
				Print("INIT");
				break;
			case SDL_NETWORK_CONNECTED:
			{
				Print("CONNECTED");
				Packet p1(MSGID_REQUEST_LOGIN, DEF_MSGTYPE_CONFIRM);
				p1.push<char> ("asdfff", 10);
				p1.push<char> ("asdff", 10);
				p1.push<char> ("WS1", 30);
				p1.send((NetSock*) EventSource->user.data1);
			}
				break;
			case SDL_NETWORK_RECEIVE:
				{
					Buffer * data = (Buffer*) EventSource->user.data2;

				unsigned int MsgID = data->next<int> ();
				unsigned short MsgType = data->next<unsigned short> ();

				char testlog[100];
				sprintf(testlog,
						"Size:%d Received -> MsgID: 0x%08X MsgType: 0x%04X",
						data->size(), MsgID, MsgType);
				Print(testlog);
				switch (MsgID)
				{
					case MSGID_RESPONSE_LOG:
						Print("MSGID_RESPONSE_LOG");

						switch (MsgType)
						{
							case DEF_MSGTYPE_CONFIRM:
							{
								unsigned short Upper =
										data->next<unsigned short> ();
								unsigned short Lower =
										data->next<unsigned char> ();
								unsigned short AccountStatus = data->next<
										unsigned short> ();

								char buffer[100];
								sprintf(
										buffer,
										"Login OK! Server version: %d.%d Account Status: %d",
										Upper, Lower, AccountStatus);
								Print(buffer);
							}
								break;
							case DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
								Print("Password mismatch!");
								break;
							case DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
								Print("Account does not exists!");
								break;
							case DEF_LOGRESMSGTYPE_REJECT:
							{
								unsigned int A = data->next<unsigned int> ();

								unsigned int B = data->next<unsigned int> ();
								unsigned int C = data->next<unsigned int> ();
								unsigned short AccountStatus = data->next<
										unsigned short> ();
								char buffer[100];
								sprintf(
										buffer,
										"Account banned till %04d-%02d-%02d (Account status: %d)",
										A, B, C, AccountStatus);
								Print(buffer);
							}
								break;
						}

						break;
				}

				delete MLSocket;
				MLSocket = 0;
				}
				break;
			case SDL_NETWORK_CLOSED:
				Print("CLOSED");
				break;
			case SDL_NETWORK_FINISH:
				Print("FINISH");
				if (MLSocket != 0)
				{
					delete MLSocket;
					MLSocket = 0;
				}
				break;
		}
	}

	Event::OnEvent(EventSource);
}
void DebugScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}
	else if (Sym == SDLK_RETURN)
	{
		if (MLSocket == 0)
		{
			MLSocket = new Socket("localhost", 9501);
			if (MLSocket->Connect())
			{
				Print("MLSocket->Connect() == TRUE");
			}
			else
				Print("MLSocket->Connect() == FALSE");
		}
		else
		{
			delete MLSocket;
			MLSocket = 0;
			Print("Cleaned up.");
		}
	}
}

void DebugScene::Print(std::string txt)
{
	backlog.push_back(txt);
	puts(txt.c_str());
}

void Socket::run()
{
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_NETWORK_INIT;
	Ev.user.data1 = Connection;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);
	puts("Before connect");
	bool OK = Connection->Connect(Address.c_str(), Port);
	puts("After connect");
	Ev.user.code = OK ? SDL_NETWORK_CONNECTED : SDL_NETWORK_ERROR;
	Ev.user.data1 = Connection;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);

	puts("Before loop");
	while (Connection != 0 && OK)
	{
		FD_ZERO(&Reader);
		FD_SET((unsigned int)Connection->socket, &Reader);
		int Ret = select(Connection->socket + 1, &Reader, (fd_set*) 0,
				(fd_set*) 0, &Timeout);
		if (Ret == -1)
		{
			puts("Select() == -1. Critical Error.");
			KillSocket();
			break;
		}
		else
		{
			printf("select: %d\n", Ret);
		}
		if (FD_ISSET(Connection->socket, &Reader))
		{
			puts("OnDataPresent()");
			OnDataPresent();
		}
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
		puts("Disconnected.");
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
	SDL_KillThread(Th);
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
	Th = 0;
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
	KillSocket();
	Connected = false;
}
int Socket::Wrapper(void * param)
{
	((Socket*) param)->run();
	return 0;
}
void Socket::Start()
{
	Th = SDL_CreateThread(Wrapper, this);
}
void Socket::Join()
{
	int status;
	SDL_WaitThread(Th, &status);
}
