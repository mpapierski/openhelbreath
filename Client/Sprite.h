#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include <vector>

#include "Surface.h"

struct Cord
{
	short X;
	short Y;
	short W;
	short H;
	short Vx;
	short Vy;
};

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

	Cord GetCord(int Number) const;

	int GetTotalFrames() const;

	int GetMaxFrameH() const;

	void SetColorKey();

private:
	SDL_Surface *Image;

	std::vector<Cord>Cords;

	int TotalFrames;

	int MaxFrameH;
};

#endif // SPRITE_H
