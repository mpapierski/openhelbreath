#include "DebugScene.h"

DebugScene::DebugScene()
{
	rect = NULL;
	SDL_Surface * ReturnSurface;
	
	ReturnSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 640-100, 480-100, 32, 0, 0, 0, 0);

	if(ReturnSurface == NULL)
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_FillRect(ReturnSurface, NULL, SDL_MapRGB(ReturnSurface->format, 255,255,255));
	SDL_SetAlpha(ReturnSurface, SDL_SRCALPHA | SDL_RLEACCEL, 128);

	MainFont.LoadFont("font/VeraSe.ttf", 12);

	rect = ReturnSurface;

	Print("Press ESC to exit Debug console");
}
DebugScene::~DebugScene()
{
	delete rect;
}

void
DebugScene::Draw(SDL_Surface * Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0, SPRID_LOGIN_BACKGROUND);
	if (rect != NULL)
		Surface::Draw(Dest, rect,50,50);
	
	int y = 0;
	int size = (int)backlog.size();
	int start = size - 19;
	if (start < 0)
		start = 0;
	
	for (int i = start; i < size; i++)
	{
		if (i >= size)
			break;
		Surface::Draw(Dest, Font::Draw(MainFont, backlog[i].c_str()), 55,53+y);
		y+=20;
	}
}

void
DebugScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}
	else if (Sym == SDLK_RETURN)
	{
		Print("SDLK_RETURN");
	}

}

void
DebugScene::Print(std::string txt)
{
	backlog.push_back(txt);
}
