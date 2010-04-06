#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include <vector>

#include "Surface.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	Sprite(const std::string &FileName, int Number);

	bool LoadFromFile(const std::string &FileName, int Number);

	static bool Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int Frame);

	static bool Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int W, int H, int Frame);

	SDL_Surface *GetSurface() const;

	SDL_Rect GetFrame(int Number) const;

private:
	SDL_Surface *Image;

	std::vector<SDL_Rect>Frames;
};

#endif // SPRITE_H
