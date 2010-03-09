#ifndef SCENE_H
#define SCENE_H

#include "Event.h"
#include "Surface.h"

class Scene : public Event
{
public:
    Scene();

    virtual void OnLoop();

    virtual void Draw(SDL_Surface* Dest);

    void OnEvent(SDL_Event* EventSource);
};

#endif // SCENE_H
