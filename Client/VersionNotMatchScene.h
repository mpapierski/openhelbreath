#ifndef VERSIONNOTMATCHSCENE_H_
#define VERSIONNOTMATCHSCENE_H_

#include "ExitScene.h"
#include "Scene.h"
#include "Timer.h"

class VersionNotMatchScene: public Scene
{
	public:
		VersionNotMatchScene();
		virtual ~VersionNotMatchScene();
		void Draw(SDL_Surface *Dest);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
};

#endif /* VERSIONNOTMATCHSCENE_H_ */
