#ifndef CREATENEWCHARSCENE_H
#define CREATENEWCHARSCENE_H

#include "Scene.h"
#include "Player.h"

class CreateNewCharScene : public Scene
{
	public:
		CreateNewCharScene();
		virtual ~CreateNewCharScene();
		void onLoop();
		void onDraw(SDL_Surface* dest);
		void onEvent(SDL_Event* eventSource);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);

	private:

		enum Focus
		{
			NONE,
			NAME,
			GENDER,
			SKIN,
			HAIR_STYLE,
			HAIR_COLOR,
			UNDERWEAR_COLOR,
			STRENGTH,
			VITALITY,
			DEXTERITY,
			INTELLIGENCE,
			MAGIC,
			CHARISMA,
			WARRIOR,
			MAGICIAN,
			MASTER,
			CREATE,
			CANCEL
		};

		Focus itemFocus;
		gui::TextEdit charNameEdit;
		int specialPoints;
		short strength, vitality, dexterity, intelligence, magic, charisma;
		char pointsLeftLabel[30];
		Player::Sex tmpSex;
		Player::Race tmpRace;
		int hairStyle;
		// TODO: make hair color change (create temp surface, copy hair style from pak, and put color)
		int underwearColor;
		Player newPlayer;
		Timer orientationTimer;
};

#endif // CREATENEWCHARSCENE_H
