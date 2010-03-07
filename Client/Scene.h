#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

#include "Event.h"
#include "Surface.h"

class CScene : public CEvent
{
public:
    CScene();

    virtual bool OnLoad() = 0;

    virtual void OnLoop();

    virtual void OnRender(SDL_Surface *Surf_Dest);

    virtual void OnCleanup();

    void OnEvent(SDL_Event *Event);
};

#endif // SCENE_H
