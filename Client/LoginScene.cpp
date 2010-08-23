#include "Game.h"

LoginScene::LoginScene(const std::string& serverName)
{
	loginFocus = LOGIN;

	loginEdit.setPosition(180, 162);
	loginEdit.setMaxLength(10);

	passwordEdit.setPosition(180, 185);
	passwordEdit.setMaxLength(10);
	passwordEdit.setPasswordMode(true);
	passwordEdit.setEnabled(false);

	int x = 320 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(
			INTERFACE_DIALOG_MESSAGEBOX).w / 2);
	int y = 240 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(
			INTERFACE_DIALOG_MESSAGEBOX).h / 2);
	msgBox.setPosition(x, y);
	msgBox.setButtons(gui::MessageDialog::OK);
	msgBox.setVisible(false);
	msgBox.setEnabled(false);

	MLSocket = 0;
	worldServerName = serverName;

	form = Surface::createSurface(SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(
			LOGIN_FRAME).w, SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(
			LOGIN_FRAME).h, 255, 255, 255, 0);

	Surface::draw(form, SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getSurface(), 0, 0,
			SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(LOGIN_FRAME).x,
			SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(LOGIN_FRAME).y,
			SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(LOGIN_FRAME).w,
			SpriteBank::manager.getSprite(SPRID_LOGINDIALOG).getFrameRect(LOGIN_FRAME).h);

	alpha = 0;
	formTimer.start();
}

LoginScene::~LoginScene()
{
	SDL_FreeSurface(form);
}

void LoginScene::onLoop()
{
	if (formTimer.getTicks() > 3)
	{
		if (alpha < 254)
		{
			alpha += 1;
			SDL_SetAlpha(form, SDL_SRCALPHA, alpha);
			formTimer.start();
		}
	}
}

void LoginScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_LOGINDIALOG, LOGIN_BACKGROUND);
	Surface::draw(dest, form, 38, 121);

	switch (loginFocus)
	{
		case LOGIN:
		case PASSWORD:
		case CONNECT:
			if (passwordEdit.getText().size() && loginEdit.getText().size())
			{
				SpriteBank::manager.draw(dest, 80, 282, SPRID_LOGINDIALOG, LOGIN_BUTTON_CONNECT);
			}
			break;
		case CANCEL:
			SpriteBank::manager.draw(dest, 256, 282, SPRID_LOGINDIALOG, LOGIN_BUTTON_CANCEL);
			break;
	}

	loginEdit.draw(dest);
	passwordEdit.draw(dest);

	connectingBox.draw(dest);
	msgBox.draw(dest);

	Game::drawVersion(dest);
}

void LoginScene::onEvent(SDL_Event* eventSource)
{
	if (!msgBox.isEnabled())
	{
		Event::onEvent(eventSource);

		if (loginFocus == LOGIN)
			loginEdit.onEvent(eventSource);
		if (loginFocus == PASSWORD)
			passwordEdit.onEvent(eventSource);
	}

	msgBox.onEvent(eventSource);
}

void LoginScene::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	if (connectingBox.isVisible())
		return;

	if (y > 282 && y < (282 + 20))
	{
		if (x > 80 && x < (80 + 84))
		{
			if (passwordEdit.getText().size() && loginEdit.getText().size())
			{
				loginFocus = CONNECT;
			}
		}
		if (x > 256 && x < (256 + 76))
		{
			loginEdit.setEnabled(false);
			passwordEdit.setEnabled(false);
			loginFocus = CANCEL;
		}
	}
}

void LoginScene::onLButtonDown(int x, int y)
{
	if (connectingBox.isVisible())
		return;

	if (x > 170 && x < (170 + 160))
	{
		if (y > 160 && y < (160 + 20)) // LoginEdit
		{
			SoundBank::manager.play("E14");
			loginEdit.setEnabled(true);
			passwordEdit.setEnabled(false);
			loginFocus = LOGIN;
		}
		if (y > 180 && y < (180 + 20)) // passwordEdit
		{
			SoundBank::manager.play("E14");
			loginEdit.setEnabled(false);
			passwordEdit.setEnabled(true);
			loginFocus = PASSWORD;
		}
	}

	if (y > 282 && y < (282 + 20))
	{
		if (x > 80 && x < (80 + 84)) // Connect Button
		{
			if (passwordEdit.getText().size() && loginEdit.getText().size())
			{
				connect();
			}
		}
		if (x > 256 && x < (256 + 76)) // Cancel Button
		{
			cancel();
		}
	}
}

void LoginScene::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_ESCAPE)
	{
		if (connectingBox.isVisible())
		{
			connectingBox.setVisible(false);
			return;
		}
		cancel();
	}

	if (connectingBox.isVisible())
		return;

	if (sym == SDLK_RETURN)
	{
		switch (loginFocus)
		{
			case LOGIN:
				SoundBank::manager.play("E14");
				loginEdit.setEnabled(false);
				passwordEdit.setEnabled(true);
				loginFocus = PASSWORD;
				break;
			case PASSWORD:
				passwordEdit.setEnabled(false);
			case CONNECT:
				if (passwordEdit.getText().size() && loginEdit.getText().size())
				{
					connect();
				}
				break;
			case CANCEL:
				cancel();
				break;
		}
	}

	if (sym == SDLK_UP)
	{
		switch (loginFocus)
		{
			case LOGIN:
				loginEdit.setEnabled(false);
				loginFocus = CANCEL;
				break;
			case PASSWORD:
				passwordEdit.setEnabled(false);
				loginEdit.setEnabled(true);
				loginFocus = LOGIN;
				break;
			case CONNECT:
				passwordEdit.setEnabled(true);
				loginFocus = PASSWORD;
				break;
			case CANCEL:
				loginFocus = CONNECT;
				break;
		}
	}

	if (sym == SDLK_DOWN || sym == SDLK_TAB)
	{
		switch (loginFocus)
		{
			case LOGIN:
				loginEdit.setEnabled(false);
				passwordEdit.setEnabled(true);
				loginFocus = PASSWORD;
				break;
			case PASSWORD:
				passwordEdit.setEnabled(false);
				loginFocus = CONNECT;
				break;
			case CONNECT:
				loginFocus = CANCEL;
				break;
			case CANCEL:
				loginEdit.setEnabled(true);
				loginFocus = LOGIN;
				break;
		}
	}
}

void LoginScene::onUser(Uint8 type, int code, void* data1, void* data2)
{
	switch (code)
	{
		case SDL_NETWORK_INIT:
			// Socket thread initialized
#ifdef DEBUG
			puts("INIT");
#endif
			connectingBox.setVisible(true);
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
			connectingBox.setState(1);
			char * WS = strdup(worldServerName.c_str()); // WHY.
#ifdef DEBUG
			puts("CONNECTED");
			printf("Log in : %s/%s at %s\n", Game::getInstance().login.c_str(),
					Game::getInstance().password.c_str(), WS);
#endif
			Packet p1(MSGID_REQUEST_LOGIN, DEF_MSGTYPE_CONFIRM);

			p1.push<char> (Game::getInstance().login.c_str(), 10);
			p1.push<char> (Game::getInstance().password.c_str(), 10);
			p1.push<char> (WS, 30);
			delete WS;
			p1.send(reinterpret_cast<NetSock*> (data1));
		}
			break;

		case SDL_NETWORK_RECEIVE:
		{
			// Got data
			Buffer* data = reinterpret_cast<Buffer*> (data2);

			unsigned int MsgID = data->next<int> ();
			unsigned short MsgType = data->next<unsigned short> ();
#ifdef DEBUG
			printf("Size:%d Received -> MsgID: 0x%08X MsgType: 0x%04X\n", data->size(), MsgID,
					MsgType);
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
							printf(
									"Login OK! Server version: %d.%d (Client version: %d.%d) Account Status: %d\n",
									Lower, Upper, DEF_LOWERVERSION, DEF_UPPERVERSION, AccountStatus);
#endif
							disconnect();
							if ((Lower == DEF_LOWERVERSION) && (Upper == DEF_UPPERVERSION))
								Game::getInstance().changeScene(new SelectCharScene(data));
#ifdef DEF_CHECKVERSION
							else
							Game::getInstance().changeScene(new VersionNotMatchScene);
#endif
							return;
						}
							break;
						case DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
							passwordMismatch();
							break;
						case DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
							notExistingAccount();
							break;
						case DEF_LOGRESMSGTYPE_REJECT:
						{
							unsigned int A = data->next<unsigned int> ();

							unsigned int B = data->next<unsigned int> ();
							unsigned int C = data->next<unsigned int> ();

#ifdef DEBUG
							printf("Account banned till %04d-%02d-%02d\n", A, B, C);
#endif
							accountBlocked(A, B, C);
						}
							break;
						case DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER:
						{
#ifdef DEBUG
							puts("World server is not activated.");
#endif
							worldNotActivated();
						}
							break;
					}
					disconnect();
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
			disconnect();
			break;
		case SDL_NETWORK_BUSY:
			// Socket is connected and waits for data
#ifdef DEBUG
			puts("BUSY");
#endif
			break;
	}
}

void LoginScene::connect()
{
	SoundBank::manager.play("E14");
	if (MLSocket != 0)
		return;

	Game::getInstance().login.assign(loginEdit.getText());
	Game::getInstance().password.assign(passwordEdit.getText());
#ifdef DEBUG
	printf("Login: %s Password: %s\n", Game::getInstance().login.c_str(), Game::getInstance().password.c_str());
#endif

	MLSocket = new Socket(DEF_SERVER_ADDR, DEF_SERVER_PORT);
	if (!MLSocket->Connect())
		fprintf(stderr, "Connect() failed.\n");
}

void LoginScene::disconnect()
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

void LoginScene::cancel()
{
	SoundBank::manager.play("E14");
#ifdef DEF_SELECTSERVER
	Game::getInstance().changeScene(new SelectServerScene);
#else
	Game::getInstance().changeScene(new MenuScene);
#endif
}

void LoginScene::passwordMismatch()
{
	connectingBox.setVisible(false);
	msgBox.setTitle("Password is not correct!");
	msgBox.setMessage("Password is not correct!");
	msgBox.setVisible(true);
	msgBox.setEnabled(true);
}

void LoginScene::notExistingAccount()
{
	connectingBox.setVisible(false);
	msgBox.setTitle("Not existing account!");
	msgBox.setMessage("Non-existing account!\nCheck your account ID.");
	msgBox.setVisible(true);
	msgBox.setEnabled(true);
}

void LoginScene::worldNotActivated()
{
	connectingBox.setVisible(false);
	msgBox.setTitle("");
	msgBox.setMessage("World server is not active now.\nTry again a few minutes later.");
	msgBox.setVisible(true);
	msgBox.setEnabled(true);
}

void LoginScene::accountBlocked(int Y, int M, int D)
{
	connectingBox.setVisible(false);
	msgBox.setTitle("Connection Rejected!");
	char Txt[80];
	snprintf(Txt, 80, "You can't login because account is blocked.\nBlock date: Until %dY %dM %dD", Y, M, D);
	msgBox.setMessage(Txt);
	msgBox.setVisible(true);
	msgBox.setEnabled(true);
}

