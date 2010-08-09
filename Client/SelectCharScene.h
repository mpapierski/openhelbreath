#ifndef SELECTCHARSCENE_H
#define SELECTCHARSCENE_H

#include "Scene.h"
#include "Buffers.h"
#include "Character.h"

typedef CCharacter CCharList[4];

class SelectCharScene : public Scene
{
	public:
		SelectCharScene();
		SelectCharScene(Buffer* data);
		~SelectCharScene();
		void onDraw(SDL_Surface* dest);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

	private:
		void updateCharList(Buffer* data, int skip = 0);

		enum Focus
		{
			START, CREATE_NEW_CHAR, DELETE_CHAR, CHANGE_PASSWD, LOGOUT
		} buttonFocus;

		int slotSelect;
		int charCount;
		CCharList charList;
};

#endif // SELECTCHARSCENE_H
