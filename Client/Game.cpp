#include "Game.h"

Game::Game()
{
	Running = true;

	ChangeScene(new LoadingScene);
}

int Game::OnExecute()
{
	if(!OnInitialize())
	{
		return -1;
	}

	SDL_Event EventHandle;

	while(Running)
	{
		while(SDL_PollEvent(&EventHandle))
		{
			OnEvent(&EventHandle);

			MouseCursor.OnEvent(&EventHandle);

			CurrentScene->OnEvent(&EventHandle);
		}

		OnLoop();

		OnDraw();

		MainWindow.Update();
	}

	OnCleanup();

	return 0;
}

bool Game::OnInitialize()
{
#ifdef DEF_FULLSCREEN
	MainWindow.Create("HelGame", 640, 480, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	MainWindow.Create("HelGame", 640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif

	MainWindow.SetKeyRepeat(50, 150);
	MainWindow.ShowCursor(false);
	MainWindow.SetCursorPos(320, 240);
	//MainWindow.SetFpsLimit(60);

	//Load some Sprites before Loading
	Sprites.push_back(Sprite::Sprite("sprites/interface.pak", 0)); //SPRID_CURSOR 0
	Surface::SetTransparent(Sprites[SPRID_CURSOR].GetSurface(), 255, 132, 66);

	Sprites.push_back(Sprite::Sprite("sprites/New-Dialog.pak", 0)); //SPRID_LOADING 1

	return true;
}

void Game::OnLoop()
{
	CurrentScene->OnLoop();
}

void Game::OnDraw()
{
	CurrentScene->Draw(MainWindow.GetSurface());

	MouseCursor.Draw(MainWindow.GetSurface());
}

void Game::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);
}

void Game::OnExit()
{
	Running = false;
}

void Game::OnCleanup()
{
	for(unsigned int i = 0; i < Sprites.size(); i++)
	{
		SDL_FreeSurface(Sprites[i].GetSurface());
	}

	MainWindow.Close();
}

void Game::ChangeScene(Scene *NewScene)
{
	delete CurrentScene;
	
	CurrentScene = NewScene;
}
