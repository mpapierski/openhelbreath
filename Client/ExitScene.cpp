#include "Game.h"

ExitScene::ExitScene()
{

}

ExitScene::~ExitScene()
{

}

void ExitScene::onLoop()
{
	if(!exitTimer.isStarted())
	{
		exitTimer.start();
	}
	if(exitTimer.getTicks() > 2000)
	{
		Game::getInstance().onQuit();
	}
}

void ExitScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_NEWDIALOG_EXIT, EXIT_BACKGROUND);

	if(exitTimer.getTicks() > 500)
	{
		SpriteBank::manager.draw(dest, 255, 123, SPRID_NEWDIALOG_EXIT, EXIT_MESSAGE);
	}

	Game::drawVersion(dest);
}

void ExitScene::onLButtonDown(int x, int y)
{
	Game::getInstance().onQuit();
}
