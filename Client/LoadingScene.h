#ifndef LOADSCENE_H
#define LOADSCENE_H

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

#endif // LOADSCENE_H
