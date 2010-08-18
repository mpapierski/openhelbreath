#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include "Scene.h"

class LoadingScene: public Scene
{
	public:
		LoadingScene();
		virtual ~LoadingScene();
		void onLoop();
		void onDraw(SDL_Surface* dest);

	private:
		int percent;
};

#endif // LOADINGSCENE_H
