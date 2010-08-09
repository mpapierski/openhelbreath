#ifndef SPRITEBANK_H
#define SPRITEBANK_H

#include <cstdio>
#include <string>
#include <vector>

#include <SDL.h>

#include "Sprite.h"
#include "SpriteID.h"

class SpriteBank
{
	public:
		SpriteBank();
		virtual ~SpriteBank();
		Sprite& getSprite(int sprID);
		void load(const std::string& fileName);
		void draw(SDL_Surface* dest, int x, int y, int sprID, int frameID);
		void draw(SDL_Surface* dest, int x, int y, int w, int h, int sprID, int frameID);
		void drawAnimated(SDL_Surface* dest, int x, int y, int sprID);
		void cleanUp();

		static SpriteBank manager;

	private:
		std::vector<Sprite> SpritesContainer;
};

#endif // SPRITEBANK_H
