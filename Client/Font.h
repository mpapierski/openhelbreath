//
// Font container and common font routines
//

#ifndef FONT_H
#define FONT_H

#include <string>
#include <SDL_ttf.h>
#include "Surface.h"

class Font
{
	public:
		enum FontSize
		{
			SMALL, NORMAL, LARGE
		};

		static SDL_Surface* text(const std::string& text, FontSize size, int r, int g, int b);
		static SDL_Surface* textShaded(const std::string &Text, FontSize, int R, int G, int B);
		static SDL_Surface* sprText(const std::string& text);
		static int textWidth(const std::string& text, FontSize size);
		static int textHeight(const std::string& text, FontSize size);
		static void putText(SDL_Surface* dest, int x, int y, const std::string& text, FontSize size, int r, int g, int b);
		static void putTextShaded(SDL_Surface* dest, int x, int y, const std::string& text, FontSize size, int r, int g, int b);
		static void putAlignedText(SDL_Surface* dest, int x, int y, int width, const std::string& text, FontSize size, int r, int g, int b);
		static void putSprText(SDL_Surface* dest, int x, int y, const std::string& text);
		static void putAlignedSprText(SDL_Surface* dest, int x, int y, int width, const std::string& text);
		static void putTextSprF(SDL_Surface* dest, int x, int y, const std::string& text);

		static TTF_Font* smallFont;
		static TTF_Font* normalFont;
};

#endif // FONT_H
