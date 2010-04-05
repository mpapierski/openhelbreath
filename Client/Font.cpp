#include "Font.h"

SDL_Surface *DrawText(TTF_Font *Font, const std::string &Text, int R, int G, int B)
{
	if(Text.empty())
	{
		return NULL;
	}

	SDL_Surface *ReturnSurface = NULL;

	SDL_Color Color;
	Color.r = R;
	Color.g = G;
	Color.b = B;

	ReturnSurface = TTF_RenderUTF8_Solid(Font, Text.c_str(), Color);

	return ReturnSurface;
}
