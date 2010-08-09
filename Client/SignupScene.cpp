#include "Game.h"

SignupScene::SignupScene()
{
	form[0].name.setText("Login:");
	form[0].name.setPosition(350, 85);
	form[0].input.setPosition((350 + Font::textWidth("Login:", Font::NORMAL) + 10), 85);
	form[0].input.setMaxLength(10);
	form[0].tip.setPosition(290, 330);
	form[0].tip.setText("Enter your account ID, only letters and numbers,\nno special characters.");

	form[1].name.setText("Password:");
	form[1].name.setPosition(350, 110);
	form[1].input.setMaxLength(10);
	form[1].input.setPasswordMode(true);
	form[1].tip.setText("Enter your account password.");

	form[2].name.setText("Confirm:");
	form[2].name.setPosition(350, 135);
	form[2].input.setMaxLength(10);
	form[2].input.setPasswordMode(true);
	form[2].tip.setText("Confirm your account password.");

	form[3].name.setText("Email:");
	form[3].name.setPosition(350, 160);
	form[3].input.setMaxLength(50);
	form[3].tip.setText(
			"Enter your E-mail address. You should enter a correct\nE-mail address to confirm the account owner.");

	form[4].name.setText("Quiz:");
	form[4].name.setPosition(300, 185);
	form[4].input.setMaxLength(45);
	form[4].tip.setText("Enter the secret question.");

	form[5].name.setText("Answer:");
	form[5].name.setPosition(300, 210);
	form[5].input.setMaxLength(20);
	form[5].tip.setText("Answer the question.");

	for (int i = 1; i < 6; i++)
	{
		form[i].input.setEnabled(false);
		form[i].input.setPosition(
				(form[i].name.x() + Font::textWidth(form[i].name.getText(), Font::NORMAL) + 10), (85 + i * 25));
		form[i].tip.setPosition(290, 330);
	}

	int x = 320 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(
			INTERFACE_DIALOG_MESSAGEBOX).w / 2);
	int y = 240 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(
			INTERFACE_DIALOG_MESSAGEBOX).h / 2);

	dlgBox.setPosition(x, y);
	dlgBox.setButtons(gui::MessageDialog::OK);
	dlgBox.setVisible(false);
	dlgBox.setEnabled(false);

	MLSocket = 0;

	setFocus(0);
}

SignupScene::~SignupScene()
{
	disconnect();
}

void SignupScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_LOGINDIALOG, LOGIN_BACKGROUND);

	for (int i = 0; i < 6; i++)
	{
		form[i].name.draw(dest);
		form[i].input.draw(dest);
	}

	if (formFocus < 6)
		form[formFocus].tip.draw(dest);
	else
	{
		switch (formFocus)
		{
			case 6:
				Font::putTextShaded(dest, 290, 330, "Create an account with your input.", Font::NORMAL, 255, 255, 255);
				break;
			case 7:
				Font::putTextShaded(dest, 290, 330, "Clear all.", Font::NORMAL, 255, 255, 255);
				break;
			case 8:
				Font::putTextShaded(dest, 290, 330, "Back to main menu.", Font::NORMAL, 255, 255, 255);
				break;
		}
	}

	SpriteBank::manager.draw(dest, 297, 398, SPRID_DIALOGTEXT_BUTTONS, formFocus == 6
			? INTERFACE_BUTTON_CREATE + 1 : INTERFACE_BUTTON_CREATE);
	SpriteBank::manager.draw(dest, 392, 398, SPRID_DIALOGTEXT_BUTTONS, formFocus == 7
			? INTERFACE_BUTTON_RESET + 1 : INTERFACE_BUTTON_RESET);
	SpriteBank::manager.draw(dest, 488, 398, SPRID_DIALOGTEXT_BUTTONS, formFocus == 8
			? INTERFACE_BUTTON_CANCEL + 1 : INTERFACE_BUTTON_CANCEL);

	connectingBox.draw(dest);
	dlgBox.draw(dest);

	Game::drawVersion(dest);
}

void SignupScene::onEvent(SDL_Event* eventSource)
{
	Event::onEvent(eventSource);

	connectingBox.onEvent(eventSource);
	dlgBox.onEvent(eventSource);

	if (formFocus < 6)
		form[formFocus].input.onEvent(eventSource);
}

void SignupScene::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	if ((x >= 297) && (x <= 370) && (y >= 396) && (y <= 417))
		setFocus(6);
	if ((x >= 392) && (x <= 465) && (y >= 396) && (y <= 417))
		setFocus(7);
	if ((x >= 488) && (x <= 561) && (y >= 396) && (y <= 417))
		setFocus(8);
}

void SignupScene::onLButtonDown(int x, int y)
{
	for (int i = 0; i < 6; i++)
	{
		int tmpX = form[i].input.x();
		int tmpY = form[i].input.y();
		if (x >= tmpX && x <= 640 && y >= tmpY && y <= tmpY + 20)
		{
			SoundBank::manager.play("E14");
			setFocus(i);
			break;
		}
	}
	if ((x >= 297) && (x <= 370) && (y >= 396) && (y <= 417))
		connect();
	if ((x >= 392) && (x <= 465) && (y >= 396) && (y <= 417))
		reset();
	if ((x >= 488) && (x <= 561) && (y >= 396) && (y <= 417))
		cancel();

}

void SignupScene::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (connectingBox.isVisible())
	{
		if (sym == SDLK_ESCAPE)
		{
			disconnect();
			connectingBox.setVisible(false);
		}
		return;
	}

	if (sym == SDLK_ESCAPE)
	{
		cancel();
	}

	if (sym == SDLK_RETURN)
	{
		if (formFocus < 6)
			setFocus(formFocus + 1);
		else
			switch (formFocus)
			{
				case 6:
					connect();
					break;
				case 7:
					reset();
					break;
				case 8:
					cancel();
					break;
			}
	}

	if (sym == SDLK_TAB || sym == SDLK_DOWN)
		setFocus((formFocus + 1) % (6 + 3));

	if (sym == SDLK_UP)
		setFocus((formFocus - 1) % (6 + 3));
}

void SignupScene::onUser(Uint8 Type, int Code, void* Data1, void* Data2)
{
	switch (Code)
	{
		case SDL_NETWORK_CONNECTED:
		{
			Packet P(MSGID_REQUEST_CREATENEWACCOUNT, 0);
			P.push<char> (form[0].input.getText().c_str(), 10); //Login
			P.push<char> (form[1].input.getText().c_str(), 10); //Password
			P.push<char> (form[3].input.getText().c_str(), 50); //Mail
			P.push<char> (" ", 10); // Gender
			P.push<char> (" ", 10); // Account Age
			P.push<int> (0);
			P.push<short> (0);
			P.push<short> (0);
			P.push<char> (" ", 17); // Country
			P.push<char> (" ", 28); // SSN
			P.push<char> (form[4].input.getText().c_str(), 45); // Q
			P.push<char> (form[5].input.getText().c_str(), 20); // A
			P.push<char> (" ", 50);
			P.send(MLSocket->Connection);
		}
			break;
		case SDL_NETWORK_RECEIVE:
		{
			connectingBox.setState(1);
			Buffer* data = reinterpret_cast<Buffer*> (Data2);
			unsigned int MsgID = data->next<int> ();
			unsigned short MsgType = data->next<unsigned short> ();
			printf("MsgID: 0x%08X MsgType: 0x%04X\n", MsgID, MsgType);
			switch (MsgID)
			{
				case MSGID_RESPONSE_LOG:
					switch (MsgType)
					{
						case DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED:
							dlgBox.setTitle("New account created.");
							dlgBox.setMessage("New account created.\nYou can login with your ID.");
							break;
						case DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT:
							dlgBox.setTitle("Already existing account name.");
							dlgBox.setMessage(
									"Already existing account name.\nEnter another account name.");
							break;
						default:
							// DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT and others
							dlgBox.setTitle("Can not create new account!");
							dlgBox.setMessage("Can not create new account!");
							break;
					}
					connectingBox.setVisible(false);
					dlgBox.setVisible(true);
					dlgBox.setEnabled(true);
					disconnect();
					break;
			}
		}
			break;
		case SDL_NETWORK_FINISH:
			disconnect();
			break;
	}
}

void SignupScene::setFocus(int newId)
{
	if (newId < 0)
		return;

	formFocus = newId;

	for (int i = 0; i < 6; i++)
	{
		form[i].input.setEnabled(false);
	}

	if (newId >= 6)
		return;

	form[newId].input.setEnabled(true);
}

void SignupScene::connect()
{
	SoundBank::manager.play("E14");

	for (int i = 0; i < 6; i++)
	{
		if (form[i].input.getText().length() == 0)
		{
			dlgBox.setTitle("Can not create new account!");
			dlgBox.setMessage("Please fill in all the required fields.");
			dlgBox.setVisible(true);
			dlgBox.setEnabled(true);
			return;
		}
	}

	if (form[1].input.getText() != form[2].input.getText())
	{
		dlgBox.setTitle("Can not create new account!");
		dlgBox.setMessage("Please confirm your password carefully.");
		dlgBox.setVisible(true);
		dlgBox.setEnabled(true);
		return;
	}

	if (MLSocket != 0)
		return;

	MLSocket = new Socket(DEF_SERVER_ADDR, DEF_SERVER_PORT);
	if (!MLSocket->Connect())
		fprintf(stderr, "Connect() failed.\n");

	connectingBox.setVisible(true);
}

void SignupScene::disconnect()
{
	if (MLSocket == 0)
		return;

	MLSocket->Disconnect();
#ifdef WIN32
	MLSocket->Join();
#endif
	delete MLSocket;
	MLSocket = 0;
}

void SignupScene::cancel()
{
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new MenuScene);
}

void SignupScene::reset()
{
	SoundBank::manager.play("E14");
	for (int i = 0; i < 6; i++)
		form[i].input.clear();
}
