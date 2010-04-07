#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

class Font
{
	public:
		static SDL_Surface
				* Text(const std::string &Text, int R, int G, int B);
		static int TextWidth(const std::string &Text);
		static int TextHeight(const std::string &Text);
		static void PutText(
				SDL_Surface* Dest,
				int X,
				int Y,
				const std::string &Text,
				int R,
				int G,
				int B);
		static void PutAlignedText(
				SDL_Surface* Dest,
				int X,
				int Y,
				int Width,
				const std::string & Text,
				int R,
				int G,
				int B);
};

#endif // FONT_H
