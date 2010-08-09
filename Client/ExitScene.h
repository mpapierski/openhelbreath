#ifndef EXITSCENE_H
#define EXITSCENE_H

#include "Scene.h"
#include "Timer.h"

class ExitScene : public Scene
{
	public:
		ExitScene();
		~ExitScene();
		void onLoop();
		void onDraw(SDL_Surface* dest);
		void onLButtonDown(int x, int y);

	private:
		Timer exitTimer;
};

#endif // EXITSCENE_H
