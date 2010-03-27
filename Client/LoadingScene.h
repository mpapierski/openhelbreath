#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include "Scene.h"

class LoadingScene : public Scene
{
public:
	LoadingScene();

	void OnLoop();

	void Draw(SDL_Surface *Dest);

private:
	int Percent;
};

#endif // LOADINGSCENE_H
