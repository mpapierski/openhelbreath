#include "Game.h"

DebugScene::DebugScene()
{
	rect = Surface::CreateSurface(640-100, 480-100, 255, 255, 255, 128);

	TextSurface = NULL;

	MainFont.LoadFont("font/VeraSe.ttf", 12);

	Print("Press ESC to exit Debug console");
}

DebugScene::~DebugScene()
{
	SDL_FreeSurface(rect);

	SDL_FreeSurface(TextSurface);
}

void
DebugScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0, SPRID_LOGIN_BACKGROUND);

	Surface::Draw(Dest, rect, 50, 50);

	int y = 0;
	int size = (int)backlog.size();
	int start = size - 19;
	if (start < 0)
		start = 0;

	for(int i = start; i < size; i++)
	{
		if(i >= size)
			break;
		SDL_FreeSurface(TextSurface);
		TextSurface = Font::Draw(MainFont, backlog[i].c_str());
		Surface::Draw(Dest, TextSurface, 55, 53+y);
		y+=20;
	}
}

void
DebugScene::OnLoop()
{

}

void
DebugScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if(Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}
	else if(Sym == SDLK_RETURN)
	{
		Print("SDLK_RETURN");
	}
}

void
DebugScene::Print(std::string txt)
{
	backlog.push_back(txt);
}
