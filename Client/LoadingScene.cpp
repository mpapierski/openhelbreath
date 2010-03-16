#include "Game.h"

LoadingScene::LoadingScene()
{
	Percent = 0;
}

void LoadingScene::OnLoop()
{
	switch(Percent)
	{
	case 0:
		Game::GetInstance().Sprites.push_back(Sprite::Sprite("sprites/New-Dialog.pak", 1)); //SPRID_MENU 2
		Game::GetInstance().Sprites.push_back(Sprite::Sprite("sprites/New-Dialog.pak", 2)); //SPRID_EXIT 3
		break;
	case 100:
		Game::GetInstance().ChangeScene(new MenuScene);
		break;
	}
	if(Percent <= 100)
	{
		Percent++;
	}
}

void LoadingScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOADING], 0, 0, SPRID_LOADING_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOADING], 473, 443, Percent, 17, SPRID_LOADING_PROGRESSBAR);
}
