#include "Game.h"

DebugScene::DebugScene()
{
	rect = Surface::CreateSurface(640 - 100, 480 - 100, 255, 255, 255, 128);

	TextSurface = NULL;

	Print("Press ESC to exit Debug console");

	state = 0;

	sock = 0;
	data = new Buffer(1024 * 32);
}

DebugScene::~DebugScene()
{
	SDL_FreeSurface(rect);

	SDL_FreeSurface(TextSurface);
	if (sock != 0)
		delete sock;
	delete data;
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
		SDL_FreeSurface(TextSurface);
		TextSurface = Font::Text(Game::GetInstance().Font, backlog[i].c_str(),
				0, 0, 0);
		Surface::Draw(Dest, TextSurface, 55, 53 + y);
		y += 20;
	}
}

void DebugScene::OnLoop()
{
	if (state != 3)
		return;
	fd_set _reader;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	FD_ZERO(&_reader);
	FD_SET((unsigned int)sock->socket, &_reader);
	int _ret = select(sock->socket + 1, &_reader, (fd_set*) 0, (fd_set*) 0,
			&timeout);
	if (_ret == -1)
	{
		Print("Select() == -1. Critical Error.");
		delete sock;
		sock = 0;
		state = 0;
		return;
	}
	if (sock != NULL && FD_ISSET(sock->socket, &_reader))
		_OnRead();
	else
		Print("...");
}

void DebugScene::_OnRead()
{
	if (!data->receive(sock))
	{
		Print("Disconnected.");
		delete sock;
		sock = 0;
		state = 0;
		return;
	}

	unsigned short packetSize;

	while (true)
	{
		memcpy(&packetSize, data->data() + 1, 2);

		if (packetSize <= data->size() && packetSize > 0)
		{
			int _before = data->pos();
			unsigned char cKey = data->next<unsigned char> ();
			unsigned short dwSize = data->next<unsigned short> ();

			if (cKey > 0)
			{
				char * buf = data->data();
				for (int i = 0; i < dwSize - 3; i++)
				{
					buf[i] ^= (cKey ^ (dwSize - i - 3));
					buf[i] -= i ^ cKey;
				}
			}

			_Readable();
			int _readcount = _before - data->pos();
			printf("_readcount = %d\n", _readcount);
			data->seek(dwSize - _readcount);
		}
		else
		{
			Print("BREAK!!!");
			break;
		}
	}
}
void DebugScene::_Readable()
{
	unsigned int MsgID = data->next<int> ();
	unsigned short MsgType = data->next<unsigned short> ();

	char testlog[100];
	sprintf(testlog, "Received -> MsgID: 0x%08X MsgType: 0x%04X", MsgID,
			MsgType);
	Print(testlog);
	switch (MsgID)
	{
		case MSGID_RESPONSE_LOG:
			Print("MSGID_RESPONSE_LOG");

			switch (MsgType)
			{
				case DEF_MSGTYPE_CONFIRM:
				{
					unsigned short Upper = data->next<unsigned short> ();
					unsigned short Lower = data->next<unsigned char> ();
					unsigned short AccountStatus =
							data->next<unsigned short> ();

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
					unsigned short AccountStatus =
							data->next<unsigned short> ();
					char buffer[100];
					sprintf(
							buffer,
							"Account banned till %04d-%02d-%02d (Account status: %d)",
							A, B, C, AccountStatus);
					Print(buffer);
				}
					break;
			}

			delete sock;
			sock = 0;
			state = 0;

			break;
	}
}

void DebugScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}
	else if (Sym == SDLK_RETURN)
	{
		switch (state)
		{
			case 0:
				Print("Connecting...");

				if (sock == 0)
					sock = new NetSock();

				sock->SetMode(NetSock::ASYNCHRONIC);
				if (sock->Connect("127.0.0.1", 9501))
				{
					Print("Connected.");
					state++;
				}
				else
				{
					Print("Failed.");
				}
				break;
			case 1:
			{
				Print("Log...");
				Packet p1(MSGID_REQUEST_LOGIN, DEF_MSGTYPE_CONFIRM);
				p1.push<char> ("asdf", 10);
				p1.push<char> ("asdffffffffff", 10);
				p1.push<char> ("WS1", 30);
				p1.send(sock);
				state += 1;
			}
				break;
			case 2:
				Print("Reader...");
				state++;
				break;

		}
	}
}

void DebugScene::Print(std::string txt)
{
	backlog.push_back(txt);
	puts(txt.c_str());
}
