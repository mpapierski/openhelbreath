#include "Game.h"

LoginScene::LoginScene()
{
	LoginFocus = Login;

	LoginEdit.SetPosition(175, 161);
	LoginEdit.SetCursorVisible(true);
	LoginEdit.SetMaxLength(20);

	PasswordEdit.SetPosition(175, 181);
	PasswordEdit.SetCursorVisible(false);
	PasswordEdit.SetMaxLength(24);
	PasswordEdit.SetPasswordMode(true);
}

void LoginScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0, SPRID_LOGIN_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 39, 121, SPRID_LOGIN_FRAME);

	switch(LoginFocus)
	{
	case Login:
		break;
	case Password:
	case Connect:
		if(PasswordEdit.GetText().size() && LoginEdit.GetText().size())
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
}

void LoginScene::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);

	if(LoginFocus == Login) LoginEdit.OnEvent(EventSource);
	if(LoginFocus == Password) PasswordEdit.OnEvent(EventSource);
}

void LoginScene::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
{
	if(Y > 282 && Y < (282+20))
	{
		if(X > 80 && X < (80+84)) LoginFocus = Connect;
		if(X > 256 && X < (256+76)) LoginFocus = Cancel;
	}
}

void LoginScene::OnLButtonDown(int X, int Y)
{
	if(X > 170 && X < (170+160))
	{
		if(Y > 160 && Y < (160+20)) // LoginEdit
		{
			LoginEdit.SetColor(0, 0, 0);
			LoginEdit.SetCursorVisible(true);
			PasswordEdit.SetColor(102, 102, 102);
			PasswordEdit.SetCursorVisible(false);
			LoginFocus = Login;
		}
		if(Y > 180 && Y < (180+20)) // PasswordEdit
		{
			PasswordEdit.SetColor(0, 0, 0);
			PasswordEdit.SetCursorVisible(true);
			LoginEdit.SetColor(102, 102, 102);
			LoginEdit.SetCursorVisible(false);
			LoginFocus = Password;
		}
	}

	if(Y > 282 && Y < (282+20))
	{
		if(X > 80 && X < (80+84)) // Connect Button
		{
			if(PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				Game::GetInstance().ChangeScene(new SelectServerScene);
			}
		}
		if(X > 256 && X < (256+76)) // Cancel Button
		{
			Game::GetInstance().ChangeScene(new MenuScene);
		}
	}
}

void LoginScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if(Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}

	if(Sym == SDLK_RETURN)
	{
		switch(LoginFocus)
		{
		case Login:
			LoginEdit.SetColor(102, 102, 102);
			LoginEdit.SetCursorVisible(false);
			PasswordEdit.SetColor(0, 0, 0);
			PasswordEdit.SetCursorVisible(true);
			LoginFocus = Password;
			break;
		case Password:
			PasswordEdit.SetColor(102, 102, 102);
			PasswordEdit.SetCursorVisible(false);

		case Connect:
			if(PasswordEdit.GetText().size() && LoginEdit.GetText().size())
			{
				Game::GetInstance().ChangeScene(new SelectServerScene);
			}
			break;
		case Cancel:
			Game::GetInstance().ChangeScene(new MenuScene);
			break;
		}
	}

	if(Sym == SDLK_UP)
	{
		switch(LoginFocus)
		{
		case Login:
			LoginEdit.SetColor(102, 102, 102);
			LoginEdit.SetCursorVisible(false);
			LoginFocus = Cancel;
			break;
		case Password:
			PasswordEdit.SetColor(102, 102, 102);
			PasswordEdit.SetCursorVisible(false);
			LoginEdit.SetColor(0, 0, 0);
			LoginEdit.SetCursorVisible(true);
			LoginFocus = Login;
			break;
		case Connect:
			PasswordEdit.SetColor(0, 0, 0);
			PasswordEdit.SetCursorVisible(true);
			LoginFocus = Password;
			break;
		case Cancel:
			LoginFocus = Connect;
			break;
		}
	}

	if(Sym == SDLK_DOWN || Sym == SDLK_TAB)
	{
		switch(LoginFocus)
		{
		case Login:
			LoginEdit.SetColor(102, 102, 102);
			LoginEdit.SetCursorVisible(false);
			PasswordEdit.SetColor(0, 0, 0);
			PasswordEdit.SetCursorVisible(true);
			LoginFocus = Password;
			break;
		case Password:
			PasswordEdit.SetColor(102, 102, 102);
			PasswordEdit.SetCursorVisible(false);
			LoginFocus = Connect;
			break;
		case Connect:
			LoginFocus = Cancel;
			break;
		case Cancel:
			LoginEdit.SetColor(0, 0, 0);
			LoginEdit.SetCursorVisible(true);
			LoginFocus = Login;
			break;
		}
	}
}
