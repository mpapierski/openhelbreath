#ifndef EXITSCENE_H
#define EXITSCENE_H

#include "Scene.h"

class ExitScene : public Scene
{
public:
	ExitScene();

	void OnLoop();

	void Draw(SDL_Surface *Dest);

	void OnLButtonDown(int X, int Y);

private:
	Timer ExitTimer;
};

#endif // EXITSCENE_H
