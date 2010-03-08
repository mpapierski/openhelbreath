#ifndef LOADSCENE_H
#define LOADSCENE_H

#include "Scene.h"
#include "GameState.h"
#include "Sprite.h"

class CLoadScene : public CScene
{
public:
    CLoadScene();

    void OnLoop();

    void OnRender(SDL_Surface *Surf_Dest);

    int procent;
};

#endif // LOADSCENE_H
