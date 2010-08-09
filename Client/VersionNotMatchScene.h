#ifndef VERSIONNOTMATCHSCENE_H
#define VERSIONNOTMATCHSCENE_H

#include "Scene.h"
#include "Timer.h"

class VersionNotMatchScene: public Scene
{
	public:
		VersionNotMatchScene();
		virtual ~VersionNotMatchScene();
		void onLoop();
		void onDraw(SDL_Surface* dest);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

	private:
		Timer exitTimer;
};

#endif // VERSIONNOTMATCHSCENE_H
