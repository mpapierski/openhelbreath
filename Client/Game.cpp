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
	Sprites[SPRID_CURSOR].Init("interface.pak", 0);
	Sprites[SPRID_CURSOR].SetColorKey();

	Sprites[SPRID_SPRFONT_NUM].Init("interface2.pak", 0);
	Sprites[SPRID_SPRFONT_NUM].SetColorKey();

	Sprites[SPRID_SPRFONT].Init("SPRFONTS.PAK", 0);
	Sprites[SPRID_SPRFONT].SetColorKey();
	Sprites[SPRID_SPRFONT2].Init("SPRFONTS.PAK", 1);
	Sprites[SPRID_SPRFONT2].SetColorKey();

	Sprites[SPRID_LOADING].Init("New-Dialog.pak", 0);

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
			case SDL_DELETE_SCENE:
				Scene * prev = static_cast<Scene*>(EventSource->user.data1);
				delete prev;
				break;
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
#ifdef DEF_CACHE
	if (Sym == SDLK_F11)
	{
		printf("Cache listing:\n");
		for (unsigned int i = 0; i < Sprite::Cache.size(); i++)
		{
			printf("%s:%d (Locked: %s RAM: %s)\n", Sprite::Cache[i]->Name.c_str(), Sprite::Cache[i]->ID, Sprite::Cache[i]->Locked ? "true" : "false", Sprite::Cache[i]->getImage() == 0 ? "false" : "true");
		}
		printf("OK.\n");
	}
	if (Sym == SDLK_F10)
	{
		printf("Releasing unused sprites...\n");
		Sprite::ReleaseUnused();
		printf("\nDone\n");
	}
#endif
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
#ifdef DEF_CACHE
	Sprite::ReleaseUnused();
	for (unsigned int i = 0; i < Sprite::Cache.size(); i++)
	{
		Sprite::Cache[i]->Locked = false;
		Sprite::Cache[i]->Priority = 0;
	}
#endif
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_DELETE_SCENE;
	Ev.user.data1 = CurrentScene;
	Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);
	CurrentScene = NewScene;
}

void Game::DrawVersion(SDL_Surface *Dest)
{
	char Ver[20];
	sprintf(Ver, "V%d.%d", DEF_LOWERVERSION, DEF_UPPERVERSION);
	Font::PutTextSprF(Dest, 14, 463, Ver);
}
