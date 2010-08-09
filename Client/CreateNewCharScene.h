#ifndef CREATENEWCHARSCENE_H
#define CREATENEWCHARSCENE_H

#include "Scene.h"

class CreateNewCharScene : public Scene
{
	public:
		CreateNewCharScene();
		virtual ~CreateNewCharScene();
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
			MAGE,
			PRIEST,
			CREATE,
			CANCEL
		};

		Focus itemFocus;
		gui::TextEdit charNameEdit;
		int specialPoints;
		char pointsLeftLabel[30];
};

#endif // CREATENEWCHARSCENE_H
