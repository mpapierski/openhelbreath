#ifndef SPRITEBANK_H
#define SPRITEBANK_H

#include <cstdio>
#include <string>
#include <vector>

#include <SDL.h>

#include "Sprite.h"
#include "SpriteID.h"
#include "Player.h"

typedef std::vector<Sprite> SpriteArray;

class SpriteBank
{
	public:
		SpriteBank();
		virtual ~SpriteBank();
		Sprite& getSprite(int sprID);
		void load(const std::string& fileName);
		void draw(SDL_Surface* dest, int x, int y, int sprID, int frameID);
		void draw(SDL_Surface* dest, int x, int y, int w, int h, int sprID, int frameID);
		void cleanUp();

		void drawSprite(SDL_Surface* dest, const Sprite& spr, int frame, int x, int y);
		void drawAnimatedCreature(SDL_Surface* dest, unsigned int creature_id, unsigned int animation_id, int x, int y);
		bool loadCreatureSprites(const std::string& fileName);
		bool loadPlayerSprites(const std::string& fileName);
		bool loadPlayerEquipment(const std::string& maleModelfileName, const std::string& femaleModelfileName);
		bool loadPlayerWeapons(const std::string& maleModelfileName, const std::string& femaleModelfileName);
		SpriteArray getSpritesFromPakFile(const std::string& fileName);

		static SpriteBank manager;

		std::vector<SpriteArray> players;
		SpriteArray male_equipment;
		SpriteArray female_equipment;
		SpriteArray male_weapons;
		SpriteArray female_weapons;

	private:
		std::vector<Sprite> SpritesContainer;
		std::vector<SpriteArray> creatures;
};

#endif // SPRITEBANK_H
