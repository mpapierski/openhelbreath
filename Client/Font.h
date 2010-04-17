#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

#include "Surface.h"

class Font
{
	public:
		static SDL_Surface *Text(const std::string &Text, int R, int G, int B);

		static SDL_Surface *TextShaded(const std::string &Text, int R, int G, int B);

		static SDL_Surface *SprText(const std::string &Text);

		static int TextWidth(const std::string &Text);

		static int TextHeight(const std::string &Text);

		static void PutText(SDL_Surface *Dest, int X, int Y, const std::string &Text, int R, int G, int B);

		static void PutTextShaded(SDL_Surface *Dest, int X, int Y, const std::string &Text, int R, int G, int B);

		static void PutAlignedText(SDL_Surface *Dest, int X, int Y, int Width, const std::string &Text, int R, int G, int B);

		static void PutSprText(SDL_Surface *Dest, int X, int Y, const std::string &Text);

		static void PutAlignedSprText(SDL_Surface *Dest, int X, int Y, int Width, const std::string &Text);

		static void PutTextSprF(SDL_Surface *Dest, int X, int Y, const std::string &Text);
};

#endif // FONT_H
