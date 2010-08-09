#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Widget.h"

class MenuScene: public Scene
{
	public:
		MenuScene();
		~MenuScene();
		void onDraw(SDL_Surface* dest);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void onExit();

	private:
		void login();
		void newAccount();

		enum Focus
		{
			LOGIN, NEW_ACCOUNT, EXIT
		} menuFocus;
};

#endif // MENUSCENE_H
