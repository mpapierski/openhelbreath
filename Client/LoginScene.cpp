#include "Game.h"

LoginScene::LoginScene()
{
	LoginFocus = Login;
	LoginEdit.SetPosition(180, 162);
	LoginEdit.SetMaxLength(11);

	PasswordEdit.SetPosition(180, 185);
	PasswordEdit.SetCursorVisible(false);
	PasswordEdit.SetMaxLength(11);
	PasswordEdit.SetPasswordMode(true);

	DlgBox.SetMode(-1, INTERFACE_BUTTON_OK);
	MLSocket = 0;
}

void LoginScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0,
			SPRID_LOGIN_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 39, 121,
			SPRID_LOGIN_FRAME);

	switch (LoginFocus)
	{
		case Login:
		case Password:
		case Connect:
			if (PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN],
						80, 282, SPRID_LOGIN_BUTTON_CONNECT);
			}
			break;
		case Cancel:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 256,
					282, SPRID_LOGIN_BUTTON_CANCEL);
			break;
	}

	LoginEdit.Draw(Dest);
	PasswordEdit.Draw(Dest);

	ConnectingBox.Draw(Dest);
	DlgBox.Draw(Dest);
}

void LoginScene::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);
	if (EventSource->type == SDL_USEREVENT)
	{
		switch (EventSource->user.code)
		{

			////////////////////////////
			case SDL_CLICKED_RIGHT:
				Game::GetInstance().ChangeScene(new MenuScene);
				break;
				////////////////////////////

			case SDL_NETWORK_ERROR:
				puts("ERROR");
				Disconnect();
				break;
			case SDL_NETWORK_INIT:
				puts("INIT");
				break;
			case SDL_NETWORK_CONNECTED:
			{
				ConnectingBox.SetState(1);
				puts("CONNECTED");
				Packet p1(MSGID_REQUEST_LOGIN, DEF_MSGTYPE_CONFIRM);
				p1.push<char> (LoginEdit.GetText().c_str(), 10);
				p1.push<char> (PasswordEdit.GetText().c_str(), 10);
				p1.push<char> (DEF_SERVER_NAME1, 30);
				p1.send((NetSock*) EventSource->user.data1);
			}
				break;
			case SDL_NETWORK_RECEIVE:
			{
				Buffer * data = (Buffer*) EventSource->user.data2;

				unsigned int MsgID = data->next<int> ();
				unsigned short MsgType = data->next<unsigned short> ();

				printf("Size:%d Received -> MsgID: 0x%08X MsgType: 0x%04X",
						data->size(), MsgID, MsgType);
				switch (MsgID)
				{
					case MSGID_RESPONSE_LOG:
						puts("MSGID_RESPONSE_LOG");
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

								printf(
										"Login OK! Server version: %d.%d Account Status: %d",
										Upper, Lower, AccountStatus);
								Disconnect();
								Game::GetInstance().ChangeScene(new SelectCharScene);
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
								unsigned short AccountStatus = data->next<
										unsigned short> ();
								printf(
										"Account banned till %04d-%02d-%02d (Account status: %d)",
										A, B, C, AccountStatus);
							}
								break;
						}
						Disconnect();
						break;
				}

			}
				break;
			case SDL_NETWORK_CLOSED:
				puts("CLOSED");
				break;
			case SDL_NETWORK_FINISH:
				puts("FINISH");
				Disconnect();
				break;
			case SDL_NETWORK_BUSY:
				puts("BUSY");
				break;
		}
		return;
	}

	if (LoginFocus == Login)
		LoginEdit.OnEvent(EventSource);
	if (LoginFocus == Password)
		PasswordEdit.OnEvent(EventSource);
}

void LoginScene::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left,
		bool Right, bool Middle)
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
		ConnectingBox.OnKeyDown(Sym, Mod, Unicode);
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
	printf("Login: %s Password: %s\n", LoginEdit.GetText().c_str(),
			PasswordEdit.GetText().c_str());
#endif
	MLSocket = new Socket(DEF_SERVER_ADDR, DEF_SERVER_PORT);
	bool OK = MLSocket->Connect();
	printf("Connect: %s\n", OK ? "true" : "false");
	ConnectingBox.SetEnabled(true);
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

void LoginScene::Disconnect()
{
	if (MLSocket == 0)
		return;

	MLSocket->Disconnect();
	MLSocket->Join();
	delete MLSocket;
	MLSocket = 0;
}
