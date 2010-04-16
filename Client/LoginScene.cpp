#include "Game.h"

LoginScene::LoginScene(const std::string &WS)
{
	LoginFocus = Login;
	LoginEdit.SetPosition(180, 162);
	LoginEdit.SetMaxLength(10);

	PasswordEdit.SetPosition(180, 185);
	PasswordEdit.SetCursorVisible(false);
	PasswordEdit.SetMaxLength(10);
	PasswordEdit.SetPasswordMode(true);

	DlgBox.SetMode(-1, INTERFACE_BUTTON_OK);
	MLSocket = 0;
	WorldServerName = WS;
}

void LoginScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0, SPRID_LOGIN_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 39, 121, SPRID_LOGIN_FRAME);

	switch (LoginFocus)
	{
		case Login:
		case Password:
		case Connect:
			if (PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 80, 282, SPRID_LOGIN_BUTTON_CONNECT);
			}
			break;
		case Cancel:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 256, 282, SPRID_LOGIN_BUTTON_CANCEL);
			break;
	}

	LoginEdit.Draw(Dest);
	PasswordEdit.Draw(Dest);

	ConnectingBox.Draw(Dest);
	DlgBox.Draw(Dest);

	Scene::DrawVersion(Dest);
}

void LoginScene::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);

	if (LoginFocus == Login)
		LoginEdit.OnEvent(EventSource);
	if (LoginFocus == Password)
		PasswordEdit.OnEvent(EventSource);
}

void LoginScene::OnUser(Uint8 Type, int Code, void *Data1, void *Data2)
{
	switch (Code)
	{
		case SDL_CLICKED_RIGHT:
			//DlgBox onclick event
			Game::GetInstance().ChangeScene(new MenuScene);
			break;

		case SDL_NETWORK_INIT:
			// Socket thread initialized
#ifdef DEBUG
			puts("INIT");
#endif
			ConnectingBox.SetEnabled(true);
			break;

		case SDL_NETWORK_ERROR:
			// Socket error (ie unable to establish connection)
#ifdef DEBUG
			puts("ERROR");
#endif
			break;

		case SDL_NETWORK_CONNECTED:
		{
			// Socket is connected to server
			ConnectingBox.SetState(1);
#ifdef DEBUG
			puts("CONNECTED");
			printf("Log in : %s/%s at %s\n", LoginEdit.GetText().c_str(), PasswordEdit.GetText().c_str(), WorldServerName.c_str());
#endif
			Packet p1(MSGID_REQUEST_LOGIN, DEF_MSGTYPE_CONFIRM);
			p1.push<char> (LoginEdit.GetText().c_str(), 10);
			p1.push<char> (PasswordEdit.GetText().c_str(), 10);
			p1.push<char> (WorldServerName.c_str(), 30);
			p1.send((NetSock*) Data1);
		}
			break;

		case SDL_NETWORK_RECEIVE:
		{
			// Got data

			Buffer *data = (Buffer*) Data2;

			unsigned int MsgID = data->next<int> ();
			unsigned short MsgType = data->next<unsigned short> ();
#ifdef DEBUG
			printf("Size:%d Received -> MsgID: 0x%08X MsgType: 0x%04X\n", data->size(), MsgID, MsgType);
#endif
			switch (MsgID)
			{
				case MSGID_RESPONSE_LOG:
#ifdef DEBUG
					puts("MSGID_RESPONSE_LOG");
#endif
					switch (MsgType)
					{
						case DEF_MSGTYPE_CONFIRM:
						{
							unsigned short Lower = data->next<unsigned short> ();
							unsigned short Upper = data->next<unsigned char> ();
							unsigned short AccountStatus = data->next<unsigned short> ();
#ifdef DEBUG
							printf("Login OK! Server version: %d.%d (Client version: %d.%d) Account Status: %d\n", Lower, Upper, DEF_LOWERVERSION, DEF_UPPERVERSION, AccountStatus);
#endif
							Disconnect();
							if ((Lower == DEF_LOWERVERSION) && (Upper == DEF_UPPERVERSION))
								Game::GetInstance().ChangeScene(new SelectCharScene);
#ifdef DEF_CHECKVERSION
							else
							Game::GetInstance().ChangeScene(new VersionNotMatchScene);
#endif
							return;
						}
							break;
						case DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
							__PasswordMismatch();
							break;
						case DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
							__NotExistingAccount();
							break;
						case DEF_LOGRESMSGTYPE_REJECT:
						{
							unsigned int A = data->next<unsigned int> ();

							unsigned int B = data->next<unsigned int> ();
							unsigned int C = data->next<unsigned int> ();

#ifdef DEBUG
							printf("Account banned till %04d-%02d-%02d\n", A, B, C);
#endif
							__AccountBlocked(A, B, C);
						}
							break;
						case DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER:
						{
#ifdef DEBUG
							puts("World server is not activated.");
#endif
							__WorldNotActivated();
						}
							break;
					}
					Disconnect();
					break;
			}

		}
			break;

		case SDL_NETWORK_CLOSED:
			// Closed connection
#ifdef DEBUG
			puts("CLOSED");
#endif
			break;
		case SDL_NETWORK_FINISH:
			// Socket thread finished
#ifdef DEBUG
			puts("FINISH");
#endif
			Disconnect();
			break;
		case SDL_NETWORK_BUSY:
			// Socket is connected and waits for data
#ifdef DEBUG
			puts("BUSY");
#endif
			break;
	}
}

void LoginScene::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
{
	if (DlgBox.IsEnabled())
	{
		DlgBox.OnMouseMove(X, Y, RelX, RelY, Left, Right, Middle);
		return;
	}
	if (Y > 282 && Y < (282 + 20))
	{
		if (X > 80 && X < (80 + 84))
		{
			if (PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				LoginFocus = Connect;
			}
		}
		if (X > 256 && X < (256 + 76))
		{
			LoginEdit.SetEnabled(false);
			PasswordEdit.SetEnabled(false);
			LoginFocus = Cancel;
		}
	}
}

void LoginScene::OnLButtonDown(int X, int Y)
{
	if (DlgBox.IsEnabled())
	{
		DlgBox.OnLButtonDown(X, Y);
		return;
	}
	if (X > 170 && X < (170 + 160))
	{
		if (Y > 160 && Y < (160 + 20)) // LoginEdit
		{
			Game::GetInstance().Audio->Play("E14");
			LoginEdit.SetEnabled(true);
			PasswordEdit.SetEnabled(false);
			LoginFocus = Login;
		}
		if (Y > 180 && Y < (180 + 20)) // PasswordEdit
		{
			Game::GetInstance().Audio->Play("E14");
			PasswordEdit.SetEnabled(true);
			LoginEdit.SetEnabled(false);
			LoginFocus = Password;
		}
	}

	if (Y > 282 && Y < (282 + 20))
	{
		if (X > 80 && X < (80 + 84)) // Connect Button
		{
			if (PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				_Connect();
			}
		}
		if (X > 256 && X < (256 + 76)) // Cancel Button
		{
			_Cancel();
		}
	}
}

void LoginScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (DlgBox.IsEnabled())
	{
		DlgBox.OnKeyDown(Sym, Mod, Unicode);
		return;
	}
	if (ConnectingBox.IsEnabled())
	{
		if (Sym == SDLK_ESCAPE)
		{
			ConnectingBox.SetEnabled(false);
			if (MLSocket != 0)
				Disconnect();
		}
		return;
	}
	if (Sym == SDLK_ESCAPE)
	{
		_Cancel();
	}

	if (Sym == SDLK_RETURN)
	{
		switch (LoginFocus)
		{
			case Login:
				Game::GetInstance().Audio->Play("E14");
				LoginEdit.SetEnabled(false);
				PasswordEdit.SetEnabled(true);
				LoginFocus = Password;
				break;
			case Password:
				PasswordEdit.SetEnabled(false);
			case Connect:
				if (PasswordEdit.GetText().size() && LoginEdit.GetText().size())
				{
					_Connect();
				}
				break;
			case Cancel:
				_Cancel();
				break;
		}
	}

	if (Sym == SDLK_UP)
	{
		switch (LoginFocus)
		{
			case Login:
				LoginEdit.SetEnabled(false);
				LoginFocus = Cancel;
				break;
			case Password:
				PasswordEdit.SetEnabled(false);
				LoginEdit.SetEnabled(true);
				LoginFocus = Login;
				break;
			case Connect:
				PasswordEdit.SetEnabled(true);
				LoginFocus = Password;
				break;
			case Cancel:
				LoginFocus = Connect;
				break;
		}
	}

	if (Sym == SDLK_DOWN || Sym == SDLK_TAB)
	{
		switch (LoginFocus)
		{
			case Login:
				LoginEdit.SetEnabled(false);
				PasswordEdit.SetEnabled(true);
				LoginFocus = Password;
				break;
			case Password:
				PasswordEdit.SetEnabled(false);
				LoginFocus = Connect;
				break;
			case Connect:
				LoginFocus = Cancel;
				break;
			case Cancel:
				LoginEdit.SetEnabled(true);
				LoginFocus = Login;
				break;
		}
	}
}

void LoginScene::_Connect()
{
	if (MLSocket != 0)
		return;
	Game::GetInstance().Audio->Play("E14");
#ifdef DEBUG
	printf("Login: %s Password: %s\n", LoginEdit.GetText().c_str(), PasswordEdit.GetText().c_str());
#endif

	MLSocket = new Socket(DEF_SERVER_ADDR, DEF_SERVER_PORT);
	if (!MLSocket->Connect())
		fprintf(stderr, "Connect() failed.\n");
}

void LoginScene::_Cancel()
{
	Game::GetInstance().Audio->Play("E14");
#ifdef DEF_SELECTSERVER
	Game::GetInstance().ChangeScene(new SelectServerScene);
#else
	Game::GetInstance().ChangeScene(new MenuScene);
#endif
}

LoginScene::~LoginScene()
{

}

void LoginScene::__PasswordMismatch()
{
	ConnectingBox.SetEnabled(false);
	DlgBox.SetEnabled(false);
	DlgBox.ClearText();
	DlgBox.SetTitle("Password is not correct!");
	DlgBox.AddText("Password is not correct!");
	DlgBox.SetEnabled(true);
}

void LoginScene::__NotExistingAccount()
{
	ConnectingBox.SetEnabled(false);
	DlgBox.SetEnabled(false);
	DlgBox.ClearText();
	DlgBox.SetTitle("Not existing account!");
	DlgBox.AddText("Non-existing account!");
	DlgBox.AddText("Check your account ID.");
	DlgBox.SetEnabled(true);
}

void LoginScene::__WorldNotActivated()
{
	ConnectingBox.SetEnabled(false);
	DlgBox.SetEnabled(false);
	DlgBox.ClearText();
	DlgBox.SetTitle("");
	DlgBox.AddText("World server is not active now.");
	DlgBox.AddText("Try again a few minutes later.");
	DlgBox.SetEnabled(true);
}

void LoginScene::__AccountBlocked(int Y, int M, int D)
{
	ConnectingBox.SetEnabled(false);
	DlgBox.SetEnabled(false);
	DlgBox.ClearText();
	DlgBox.SetTitle("Connection Rejected!");
	DlgBox.AddText("You can't login because account is blocked.");
	char Txt[30];
	sprintf(Txt, "Block date: Until %dY %dM %dD", Y, M, D);
	DlgBox.AddText(Txt);
	DlgBox.SetEnabled(true);

}
void LoginScene::Disconnect()
{
	if (MLSocket == 0)
		return;

	MLSocket->Disconnect();
#ifdef WIN32
	// Dont know why, SDL_WaitThread does not like dead (finished) threads.
	MLSocket->Join();
#endif
	delete MLSocket;
	MLSocket = 0;
}
