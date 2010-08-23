//
// Player definition file. Initializes currentPlayer as main character. Can and should
// be used for displaying other player characters on screen
//

#ifndef PLAYER_H
#define PLAYER_H

#include "SpriteBank.h"
#include "Timer.h"

class Player
{
	public:
		Player();
		void draw(SDL_Surface* dest, int x, int y);

		enum Sex
		{
			MALE, FEMALE
		};
		enum Race
		{
			BLACK, WHITE, ASIAN
		};

		Sex sex();
		void setSex(Sex s);
		Race race();
		void setRace(Race r);
		int hairStyle();
		void setHairStyle(int hairStyle);
		int underwearColor();
		void setUnderwearColor(int underwear);
		int orientation();
		void setOrientation(int o);
		int action();
		void setAction(int a);

		// equipment
		int hauberk;
		int leggings;
		int chest;
		int feet;
		int cape;
		int head;
		int primary_weapon;
		int secondary_weapon; // shield

	private:
		void drawEquipment(SDL_Surface* dest, int x, int y, int equip_id, int equipmentFrameToShow);
		void drawWeapon(SDL_Surface* dest, int x, int y, int equip_id, int weaponFrameToShow);

		Sex _sex;
		Race _race;
		int _hairStyle;
		int _underwearColor;
		int _orientation;
		int _action; // running, standing, etc

		unsigned int player_sprite_id;
		unsigned int player_animation_id;

		void resetTimerAndFrames();
		Timer playerTimer;
		int currentFrame;
		int framesCount;
};

#endif // PLAYER_H
