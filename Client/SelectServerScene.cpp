#include "Game.h"

SelectServerScene::SelectServerScene()
{
	selectServerFocus = ABADDON;
}

SelectServerScene::~SelectServerScene()
{

}

void SelectServerScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_LOGINDIALOG, LOGIN_BACKGROUND);
	SpriteBank::manager.draw(dest, 40, 121, SPRID_LOGINDIALOG, SELECTSERVER_FRAME);

	switch(selectServerFocus)
	{
	case ABADDON:
		SpriteBank::manager.draw(dest, 139, 176, SPRID_LOGINDIALOG, SELECTSERVER_BUTTON_ABADDON);
		break;
	case APOCALYPSE:
		SpriteBank::manager.draw(dest, 131, 204, SPRID_LOGINDIALOG, SELECTSERVER_BUTTON_APOCALYPSE);
		break;
	case CANCEL:
		SpriteBank::manager.draw(dest, 257, 282, SPRID_LOGINDIALOG, LOGIN_BUTTON_CANCEL);
		break;
	}

	Game::drawVersion(dest);
}

void SelectServerScene::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	if(x > 139 && x < (139+138)) // ABADDON Button
	{
		if(y > 176 && y < (176+19))
		{
			selectServerFocus = ABADDON;
		}
	}

	if(x > 131 && x < (139+157)) // APOCALYPSE Button
	{
		if(y > 204 && y < (204+19))
		{
			selectServerFocus = APOCALYPSE;
		}
	}

	if(x > 256 && x < (256+76)) // CANCEL Button
	{
		if(y > 282 && y < (282+20))
		{
			selectServerFocus = CANCEL;
		}
	}
}

void SelectServerScene::onLButtonDown(int x, int y)
{
	if(x > 139 && x < (139+138)) // ABADDON Button
	{
		if(y > 176 && y < (176+19))
		{
			selectServerFocus = ABADDON;
			server1();
		}
	}

	if(x > 131 && x < (139+157)) // APOCALYPSE Button
	{
		if(y > 204 && y < (204+19))
		{
			selectServerFocus = APOCALYPSE;
			server2();
		}
	}

	if(x > 256 && x < (256+76)) // Cancel Button
	{
		if(y > 282 && y < (282+20))
		{
			cancel();
		}
	}
}

void SelectServerScene::onKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if(Sym == SDLK_ESCAPE)
	{
		Game::getInstance().changeScene(new MenuScene);
	}

	if(Sym == SDLK_RETURN)
	{
		switch(selectServerFocus)
		{
		case ABADDON:
			server1();
			break;
		case APOCALYPSE:
			server2();
			break;
		case CANCEL:
			cancel();
			break;
		}
	}

	if(Sym == SDLK_UP)
	{
		switch(selectServerFocus)
		{
		case ABADDON:
			selectServerFocus = CANCEL;
			break;
		case APOCALYPSE:
			selectServerFocus = ABADDON;
			break;
		case CANCEL:
			selectServerFocus = APOCALYPSE;
			break;
		}
	}

	if(Sym == SDLK_DOWN || Sym == SDLK_TAB)
	{
		switch(selectServerFocus)
		{
		case ABADDON:
			selectServerFocus = APOCALYPSE;
			break;
		case APOCALYPSE:
			selectServerFocus = CANCEL;
			break;
		case CANCEL:
			selectServerFocus = ABADDON;
			break;
		}
	}
}

void SelectServerScene::server1()
{
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new LoginScene);
}

void SelectServerScene::server2()
{
#ifdef DEF_SELECTSERVER
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new LoginScene(DEF_SERVER_NAME2));
#else
	server1();
#endif
}

void SelectServerScene::cancel()
{
	SoundBank::manager.play("E14");
	Game::getInstance().changeScene(new MenuScene);
}

void SelectServerScene::onExit()
{
	Game::getInstance().changeScene(new ExitScene);
}
