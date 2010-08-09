#ifndef SELECTSERVERSCENE_H
#define SELECTSERVERSCENE_H

#include "Scene.h"

class SelectServerScene : public Scene
{
	public:
		SelectServerScene();
		~SelectServerScene();
		void onDraw(SDL_Surface* dest);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
		void onExit();

	private:
		void cancel();
		void server1();
		void server2();
		enum Focus { ABADDON, APOCALYPSE, CANCEL } selectServerFocus;
};

#endif // SELECTSERVERSCENE_H
