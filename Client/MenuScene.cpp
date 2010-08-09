#include "Game.h"

MenuScene::MenuScene()
{
	menuFocus = LOGIN;
}

MenuScene::~MenuScene()
{

}

void MenuScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_NEWDIALOG_MAINMENU, MAINMENU_BACKGROUND);

	switch (menuFocus)
	{
		case LOGIN:
			SpriteBank::manager.draw(dest, 385, 178, SPRID_NEWDIALOG_MAINMENU, MAINMENU_LOGIN);
			break;
		case NEW_ACCOUNT:
			SpriteBank::manager.draw(dest, 385, 216, SPRID_NEWDIALOG_MAINMENU, MAINMENU_NEWACCOUNT);
			break;
		case EXIT:
			SpriteBank::manager.draw(dest, 385, 255, SPRID_NEWDIALOG_MAINMENU, MAINMENU_EXIT);
			break;
	}

	Game::drawVersion(dest);
}

void MenuScene::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	if (x > 385 && x < (385 + 164))
	{
		if (y > 178 && y < (178 + 22))
			menuFocus = LOGIN;
		if (y > 216 && y < (216 + 22))
			menuFocus = NEW_ACCOUNT;
		if (y > 255 && y < (255 + 22))
			menuFocus = EXIT;
	}
}

void MenuScene::onLButtonDown(int x, int y)
{
	if (x > 385 && x < (385 + 164)) // Login Button
	{
		if (y > 178 && y < (178 + 22))
			login();

#ifdef DEF_MAKEACCOUNT
		if (y > 216 && y < (216 + 22))
			newAccount();
#endif

		if (y > 255 && y < (255 + 22))
			onExit();
	}
}

void MenuScene::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_ESCAPE)
	{
		onExit();
	}

	if (sym == SDLK_RETURN)
	{
		switch (menuFocus)
		{
			case LOGIN:
				login();
				break;
			case NEW_ACCOUNT:
#ifdef DEF_MAKEACCOUNT
				newAccount();
#endif
				break;
			case EXIT:
				onExit();
				break;
		}
	}

	if (sym == SDLK_UP)
	{
		switch (menuFocus)
		{
			case LOGIN:
				menuFocus = EXIT;
				break;
			case NEW_ACCOUNT:
				menuFocus = LOGIN;
				break;
			case EXIT:
				menuFocus = NEW_ACCOUNT;
				break;
		}
	}

	if (sym == SDLK_DOWN || sym == SDLK_TAB)
	{
		switch (menuFocus)
		{
			case LOGIN:
				menuFocus = NEW_ACCOUNT;
				break;
			case NEW_ACCOUNT:
				menuFocus = EXIT;
				break;
			case EXIT:
				menuFocus = LOGIN;
				break;
		}
	}
}

void MenuScene::onExit()
{
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new ExitScene);
}

void MenuScene::newAccount()
{
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new SignupScene);
}

void MenuScene::login()
{
	SoundBank::manager.play("E14");
#ifdef DEF_SELECTSERVER
	Game::getInstance().changeScene(new SelectServerScene);
#else
	Game::getInstance().changeScene(new LoginScene);
#endif
}

