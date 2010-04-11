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
}

void LoginScene::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);

	if (LoginFocus == Login)
		LoginEdit.OnEvent(EventSource);
	if (LoginFocus == Password)
		PasswordEdit.OnEvent(EventSource);
}

void LoginScene::OnMouseMove(
		int X,
		int Y,
		int RelX,
		int RelY,
		bool Left,
		bool Right,
		bool Middle)
{
	if (Y > 282 && Y < (282 + 20))
	{
		if (X > 80 && X < (80 + 84))
		{
			LoginFocus = Connect;
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
	if (X > 170 && X < (170 + 160))
	{
		if (Y > 160 && Y < (160 + 20)) // LoginEdit
		{
			LoginEdit.SetEnabled(true);
			PasswordEdit.SetEnabled(false);
			LoginFocus = Login;
		}
		if (Y > 180 && Y < (180 + 20)) // PasswordEdit
		{
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
#ifdef DEBUG
	printf("Login: %s Password: %s\n", LoginEdit.GetText().c_str(),
			PasswordEdit.GetText().c_str());
#endif
	ConnectingBox.SetEnabled(true);
}

void LoginScene::_Cancel()
{
#ifdef DEF_SELECTSERVER
	Game::GetInstance().ChangeScene(new SelectServerScene);
#else
	Game::GetInstance().ChangeScene(new MenuScene);
#endif
}

LoginScene::~LoginScene()
{

}
