#ifndef EXITSCENE_H
#define EXITSCENE_H

#include "Scene.h"
#include "Sprite.h"
#include "Timer.h"

class CExitScene : public CScene
{
public:
    CExitScene();

    bool OnLoad();

    void OnLoop();

    void OnRender(SDL_Surface *Surf_Dest);

    void OnCleanup();

private:
    CSprite ExitSprite;

    CTimer exitTimer;
};

#endif // EXITSCENE_H
