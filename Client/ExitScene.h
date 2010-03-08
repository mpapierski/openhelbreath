#ifndef EXITSCENE_H
#define EXITSCENE_H

#include "Scene.h"
#include "Sprite.h"
#include "Timer.h"

class CExitScene : public CScene
{
public:
    CExitScene();

    void OnLoop();

    void OnRender(SDL_Surface *Surf_Dest);

private:

    CTimer exitTimer;
};

#endif // EXITSCENE_H
