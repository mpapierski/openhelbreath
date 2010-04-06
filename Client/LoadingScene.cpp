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
		Game::GetInstance().Sprites[SPRID_MAINMENU].LoadFromFile("sprites/New-Dialog.pak", 1);
		Game::GetInstance().Sprites[SPRID_EXIT].LoadFromFile("sprites/New-Dialog.pak", 2);
		Game::GetInstance().Sprites[SPRID_LOGIN].LoadFromFile("sprites/LoginDialog.pak", 0);
		Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON].LoadFromFile("sprites/DialogText.pak", 1);
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
	// New-Dialog.pak is bugged. So we need to draw background +1, +1. TODO: Fix New-Dialog.pak
	// Crazy koreans, they didn't fix it up to most recent versions
	// Notice when original client is loading there is black line on edges.
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOADING], 1, 1, SPRID_LOADING_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOADING], 473, 443, Percent, 17, SPRID_LOADING_PROGRESSBAR);
}
