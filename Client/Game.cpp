#include "Game.h"

Game::Game()
{
	running = true;

	previousScene = 0;

	changeScene(new LoadingScene);
}

int Game::onExecute()
{
	if (!onInitialize())
		return -1;

	SDL_Event eventHandle;

	while (running)
	{
		while (SDL_PollEvent(&eventHandle))
		{
			onEvent(&eventHandle);

			mouseCursor.onEvent(&eventHandle);

			currentScene->onEvent(&eventHandle);
		}

		onLoop();

		onDraw();

		mainWindow.update();

		if (previousScene != 0)
		{
			delete previousScene;
			previousScene = 0;
		}
	}

	onCleanup();

	return 0;
}

bool Game::onInitialize()
{
#ifdef DEF_FULLSCREEN
	mainWindow.create("HelGame", 640, 480, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	mainWindow.create("HelGame", 640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif

	mainWindow.setKeyRepeat(1, 175);
	mainWindow.showCursor(false);
	mainWindow.setCursorPos(320, 240);

#ifdef DEF_FPSLIMIT
	mainWindow.setFpsLimit(DEF_FPSLIMIT);
#endif

	SDL_EnableUNICODE( SDL_ENABLE);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		fprintf(stderr, "Unable to open audio channel\n");
		return false;
	}

	SoundBank::manager.load("E14");

	Font::smallFont = TTF_OpenFont("FONTS/VeraSe.ttf", 10);
	if (Font::smallFont == NULL)
	{
		fprintf(stderr, "Unable to load font file: FONTS/VeraSe.ttf\n");
		return false;
	}

	Font::normalFont = TTF_OpenFont("FONTS/VeraSe.ttf", 12);
	if (Font::normalFont == NULL)
	{
		fprintf(stderr, "Unable to load font file: FONTS/VeraSe.ttf\n");
		return false;
	}

	SpriteBank::manager.load("interface");
	SpriteBank::manager.getSprite(SPRID_INTERFACE_CURSOR).setColorKey();
	SpriteBank::manager.load("interface2");
	SpriteBank::manager.getSprite(SPRID_INTERFACE2_NUM).setColorKey();
	SpriteBank::manager.load("SPRFONTS");
	SpriteBank::manager.getSprite(SPRID_SPRFONT).setColorKey();
	SpriteBank::manager.load("New-Dialog");
	SpriteBank::manager.load("LoginDialog");
	SpriteBank::manager.load("DialogText");
	SpriteBank::manager.getSprite(SPRID_DIALOGTEXT_BUTTONS).setColorKey();
	return true;
}

void Game::onLoop()
{
	currentScene->onLoop();
}

void Game::onDraw()
{
	currentScene->onDraw(mainWindow.getSurface());

	mouseCursor.onDraw(mainWindow.getSurface());

	char fps[12];
	snprintf(fps, 12, "fps: %d", mainWindow.getFps());
	Font::putTextShaded(mainWindow.getSurface(), 0, 0, fps, Font::NORMAL, 255, 255, 255);
}

void Game::onEvent(SDL_Event* eventSource)
{
	Event::onEvent(eventSource);
}

void Game::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F11)
	{
		changeScene(new CreateNewCharScene);
	}
}

void Game::onExit()
{
	changeScene(new ExitScene);
}

void Game::onQuit()
{
	running = false;
}

void Game::onCleanup()
{
	delete currentScene;
	delete previousScene;

	Mix_CloseAudio();

	TTF_CloseFont(Font::smallFont);
	TTF_CloseFont(Font::normalFont);

	mainWindow.close();

	SpriteBank::manager.cleanUp();
	SoundBank::manager.cleanUp();
}

void Game::changeScene(Scene* newScene)
{
	previousScene = currentScene;
	currentScene = newScene;
}

void Game::drawVersion(SDL_Surface* dest)
{
	char ver[20];
	sprintf(ver, "V%d.%d", DEF_LOWERVERSION, DEF_UPPERVERSION);
	Font::putTextSprF(dest, 14, 463, ver);
}
