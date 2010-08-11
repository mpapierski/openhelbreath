#ifndef SPRITEBANK_H
#define SPRITEBANK_H

#include <cstdio>
#include <string>
#include <vector>

#include <SDL.h>

#include "Sprite.h"
#include "SpriteID.h"

#define SpriteArray std::vector<Sprite>

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

                void drawAnimatedCreature(SDL_Surface* dest, unsigned int creature_id, unsigned int animation_id, int x, int y);
                bool loadCreature(const std::string& fileName);
                std::vector<Sprite> getSpritesFromPakFile(const std::string& fileName);

		static SpriteBank manager;

                std::vector<SpriteArray> creatures;

	private:
                std::vector<Sprite> SpritesContainer;
};

#endif // SPRITEBANK_H
