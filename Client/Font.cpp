#include "Game.h"
#include "Font.h"
#include "Surface.h"

SDL_Surface * Font::Text(const std::string &Text, int R, int G, int B)
{
	if (Text.empty())
		return NULL;

	SDL_Surface *ReturnSurface = NULL;

	SDL_Color Color;
	Color.r = R;
	Color.g = G;
	Color.b = B;
	ReturnSurface = TTF_RenderUTF8_Solid(Game::GetInstance().Font,
			Text.c_str(), Color);
	return ReturnSurface;
}

int Font::TextWidth(const std::string & Text)
{
	int W, H;
	TTF_SizeText(Game::GetInstance().Font, Text.c_str(), &W, &H);
	return W;
}

int Font::TextHeight(const std::string & Text)
{
	int W, H;
	TTF_SizeUTF8(Game::GetInstance().Font, Text.c_str(), &W, &H);
	return H;
}

void Font::PutText(
		SDL_Surface* Dest,
		int X,
		int Y,
		const std::string &Text,
		int R,
		int G,
		int B)
{
	SDL_Surface * _txt = Font::Text(Text, R, G, B);
	Surface::Draw(Dest, _txt, X, Y);
	SDL_FreeSurface(_txt);
}

void Font::PutAlignedText(
		SDL_Surface *Dest,
		int X,
		int Y,
		int Width,
		const std::string & Text,
		int R,
		int G,
		int B)
{
	Font::PutText(Dest, X + ((Width - Font::TextWidth(Text)) / 2), Y, Text, R,
			G, B);
}
