#include "Game.h"

MenuScene::MenuScene()
{
	MenuFocus = Login;
}

void MenuScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_MAINMENU], 0, 0,
			SPRID_MAINMENU_BACKGROUND);

	switch (MenuFocus)
	{
		case Login:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_MAINMENU],
					385, 178, SPRID_MAINMENU_LOGIN);
			break;
		case NewAccount:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_MAINMENU],
					385, 216, SPRID_MAINMENU_NEWACCOUNT);
			break;
		case Exit:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_MAINMENU],
					385, 255, SPRID_MAINMENU_EXIT);
			break;
	}
}

void MenuScene::OnMouseMove(
		int X,
		int Y,
		int RelX,
		int RelY,
		bool Left,
		bool Right,
		bool Middle)
{
	if (X > 385 && X < (385 + 164))
	{
		if (Y > 178 && Y < (178 + 22))
			MenuFocus = Login;
		if (Y > 216 && Y < (216 + 22))
			MenuFocus = NewAccount;
		if (Y > 255 && Y < (255 + 22))
			MenuFocus = Exit;
	}
}

void MenuScene::OnLButtonDown(int X, int Y)
{
	if (X > 385 && X < (385 + 164)) // Login Button
	{

		if (Y > 178 && Y < (178 + 22))
		{
#ifdef DEF_SELECTSERVER
			Game::GetInstance().ChangeScene(new SelectServerScene);
#else
			Game::GetInstance().ChangeScene(new LoginScene);
#endif
		}

#ifdef DEF_MAKEACCOUNT
		if (Y > 216 && Y < (216 + 22))
			Game::GetInstance().ChangeScene(new SignupScene); // New Account Button
#endif

		if (Y > 255 && Y < (255 + 22))
			Game::GetInstance().ChangeScene(new ExitScene); // Exit Button
	}
}

void MenuScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new ExitScene);
	}

	if (Sym == SDLK_RETURN)
	{
		switch (MenuFocus)
		{
			case Login:
#ifdef DEF_SELECTSERVER
				Game::GetInstance().ChangeScene(new SelectServerScene);
#else
				Game::GetInstance().ChangeScene(new LoginScene);
#endif
				break;
#ifdef DEF_MAKEACCOUNT
			case NewAccount:
				Game::GetInstance().ChangeScene(new SignupScene);
				break;
#endif
			case Exit:
				Game::GetInstance().ChangeScene(new ExitScene);
				break;
		}
	}

	if (Sym == SDLK_UP)
	{
		switch (MenuFocus)
		{
			case Login:
				MenuFocus = Exit;
				break;
			case NewAccount:
				MenuFocus = Login;
				break;
			case Exit:
				MenuFocus = NewAccount;
				break;
		}
	}

	if (Sym == SDLK_DOWN || Sym == SDLK_TAB)
	{
		switch (MenuFocus)
		{
			case Login:
				MenuFocus = NewAccount;
				break;
			case NewAccount:
				MenuFocus = Exit;
				break;
			case Exit:
				MenuFocus = Login;
				break;
		}
	}
}
