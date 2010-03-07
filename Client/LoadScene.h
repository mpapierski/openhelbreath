#ifndef LOADSCENE_H
#define LOADSCENE_H

#include "Scene.h"
#include "GameState.h"
#include "Sprite.h"

class CLoadScene : public CScene
{
public:
    CLoadScene();

    bool OnLoad();

    void OnLoop();

    void OnRender(SDL_Surface *Surf_Dest);

    void OnCleanup();

    int procent;

private:
    CSprite LoadSprite;
};

#endif // LOADSCENE_H
