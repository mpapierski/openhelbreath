#include "Game.h"

VersionNotMatchScene::VersionNotMatchScene()
{

}

VersionNotMatchScene::~VersionNotMatchScene()
{

}

void VersionNotMatchScene::onLoop()
{
	if(!exitTimer.isStarted())
	{
		exitTimer.start();
	}
	if(exitTimer.getTicks() > 4000)
	{
		Game::getInstance().onQuit();
	}
}

void VersionNotMatchScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_NEWDIALOG_EXIT, 0);
	SpriteBank::manager.draw(dest, 162, 125, SPRID_GAMEDIALOG_3, 2);
	Font::putAlignedText(dest, 168, 160, 474 - 168, "Client program version does not match with server!", Font::NORMAL, 255, 255, 255);
	Font::putAlignedText(dest, 168, 180, 474 - 168, "Download recent version and try again.", Font::NORMAL, 255, 255, 255);
	Font::putAlignedText(dest, 168, 250, 474 - 168, MSG_HOMEPAGE, Font::NORMAL, 255, 255, 255);

	Game::drawVersion(dest);
}

void VersionNotMatchScene::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if(exitTimer.getTicks() > 1000)
		Game::getInstance().onQuit();
}

void VersionNotMatchScene::onLButtonDown(int x, int y)
{
	Game::getInstance().onQuit();
}

