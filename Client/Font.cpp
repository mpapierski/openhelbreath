#include "Font.h"

Font::Font()
{

}

Font::Font(const std::string &FileName, int Size)
{
	LoadFont(FileName, Size);
}

SDL_Surface *Font::Draw(Font &SrcFont, const std::string &Text)
{
	if(Text.empty())
	{
		return NULL;
	}

	SDL_Surface *ReturnSurface = NULL;

	ReturnSurface = TTF_RenderUTF8_Solid(SrcFont.GetFont(), Text.c_str(), SrcFont.GetColor());

	return ReturnSurface;
}

SDL_Color Font::GetColor() const
{
	return Color;
}

TTF_Font *Font::GetFont() const
{
	return FontHandle;
}

void Font::LoadFont(const std::string &FileName, int Size)
{
	FontHandle = TTF_OpenFont(FileName.c_str(), Size);
	
	if(!FontHandle)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(3);
	}

	SetColor(0, 0, 0);
}

void Font::SetColor(int R, int G, int B)
{
	Color.r = R;
	Color.g = G;
	Color.b = B;
}

Font::~Font()
{
	TTF_CloseFont(FontHandle);
}
