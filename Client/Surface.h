#ifndef SURFACE_H
#define SURFACE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Surface
{
	public:
		Surface();
		static SDL_Surface* loadFromImage(const std::string& fileName);
		static SDL_Surface* createSurface(int w, int h, int r, int g, int b, int alpha);
		static bool draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
		static bool draw(SDL_Surface* dest, SDL_Surface* Src, int x, int y, int x2, int y2, int w, int h);
		static bool setColorKey(SDL_Surface* dest, int r, int g, int b);
		static Uint32 getPixel32(SDL_Surface* src, int x, int y);
		static void replaceColor(SDL_Surface* dest, Uint32 a, Uint32 b);
};

#endif // SURFACE_H
