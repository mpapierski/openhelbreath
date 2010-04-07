#include "Game.h"

ExitScene::ExitScene()
{

}

void ExitScene::OnLoop()
{
	if(!ExitTimer.IsStarted())
	{
		ExitTimer.Start();
	}
	if(ExitTimer.GetTicks() > 2000)
	{
		Game::GetInstance().OnQuit();
	}
}

void ExitScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_EXIT], 0, 0, SPRID_EXIT_BACKGROUND);
	
	if(ExitTimer.GetTicks() > 500)
	{
		Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_EXIT], 255, 123, SPRID_EXIT_MESSAGE);
	}
}

void ExitScene::OnLButtonDown(int X, int Y)
{
	Game::GetInstance().OnExit();
}
