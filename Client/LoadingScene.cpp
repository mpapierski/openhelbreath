#include "Game.h"

LoadingScene::LoadingScene()
{
	Percent = 0;
}

void LoadingScene::OnLoop()
{
	switch (Percent)
	{
		case 0:
			Game::GetInstance().Sprites[SPRID_MAINMENU].LoadFromFile("New-Dialog.pak", 1);
			Game::GetInstance().Sprites[SPRID_EXIT].LoadFromFile("New-Dialog.pak", 2);
			Game::GetInstance().Sprites[SPRID_LOGIN].LoadFromFile("LoginDialog.pak", 0);
			Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].LoadFromFile("GameDialog.pak", 3);
			Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].SetColorKey();
			Game::GetInstance().Sprites[SPRID_GAMEDIALOG_8].LoadFromFile("GameDialog.pak", 8);
			Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS].LoadFromFile("DialogText.pak", 1);
			Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS].SetColorKey();
			break;
		case 1:
			Game::GetInstance().Audio->Add("E14", AUDIO_SOUND);
			break;
		case 100:
			Game::GetInstance().ChangeScene(new MenuScene);
			break;
	}

	if (Percent <= 100)
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

	Scene::DrawVersion(Dest);
}
