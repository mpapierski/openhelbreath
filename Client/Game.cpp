#include "Game.h"

Game::Game()
{
	Running = true;

	ChangeScene(new LoadingScene);

	Sprites.assign(DEF_MAXSPRITES, Sprite::Sprite());
}

int Game::OnExecute()
{
	if (!OnInitialize())
		return -1;

	SDL_Event EventHandle;

	while (Running)
	{
		while (SDL_PollEvent(&EventHandle))
		{
			OnEvent(&EventHandle);

			CurrentScene->OnEvent(&EventHandle);

			MouseCursor.OnEvent(&EventHandle);
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

#ifndef __unix__
	WSADATA wsdat;
	memset(&wsdat, 0, sizeof(wsdat));
	if (WSAStartup(0x0101, &wsdat))
	{
		fprintf(stderr, "WSAStartup() failed.\n");
		return false;
	}
#endif

#ifdef DEF_FULLSCREEN
	MainWindow.Create("HelGame", 640, 480, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	MainWindow.Create("HelGame", 640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif

	MainWindow.SetKeyRepeat(5, 200);
	MainWindow.ShowCursor(false);
	MainWindow.SetCursorPos(320, 240);

#ifdef DEF_FPSLIMIT
	MainWindow.SetFpsLimit(DEF_FPSLIMIT);
#endif

	SDL_EnableUNICODE( SDL_ENABLE);

	Font = TTF_OpenFont("FONTS/VeraSe.ttf", 12);
	if(Font == NULL)
	{
		printf("Unable to load font file: FONTS/VeraSe.ttf\n");
		return false;
	}

	Audio = new AudioManager();

	//Load some Sprites before Loading
	Sprites[SPRID_CURSOR].LoadFromFile("interface.pak", 0);
	Sprites[SPRID_CURSOR].SetColorKey();

	Sprites[SPRID_SPRFONT_NUM].LoadFromFile("interface2.pak", 0);
	Sprites[SPRID_SPRFONT_NUM].SetColorKey();

	Sprites[SPRID_SPRFONT].LoadFromFile("SPRFONTS.PAK", 0);
	Sprites[SPRID_SPRFONT].SetColorKey();
	Sprites[SPRID_SPRFONT2].LoadFromFile("SPRFONTS.PAK", 1);
	Sprites[SPRID_SPRFONT2].SetColorKey();

	Sprites[SPRID_LOADING].LoadFromFile("New-Dialog.pak", 0);

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
#ifdef DEBUG
	if (EventSource->type == SDL_USEREVENT)
	{
		switch (EventSource->user.code)
		{
			case SDL_THREAD_START:
			{
				printf("Thread started (ID: " INT_FMT ")\n", reinterpret_cast<INT>(EventSource->user.data2));
			}
				break;
			case SDL_THREAD_FINISHED:
			{
				printf("Thread finished (ID: " INT_FMT ")\n", reinterpret_cast<INT>(EventSource->user.data2));
			}
				break;
		}

	}
#endif
	Event::OnEvent(EventSource);
}

void Game::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
#ifdef DEBUG
	if (Sym == SDLK_F11)
	{
		ChangeScene(new SelectCharScene);
	}
	if (Sym == SDLK_F12)
	{
		ChangeScene(new DebugScene);
	}
#endif
}

void Game::OnExit()
{
	ChangeScene(new ExitScene);
}

void Game::OnQuit()
{
	Running = false;
}

void Game::OnCleanup()
{
	delete Audio;

	TTF_CloseFont(Font);

	MainWindow.Close();
}

void Game::ChangeScene(Scene *NewScene)
{
	delete CurrentScene;

	CurrentScene = NewScene;
}
