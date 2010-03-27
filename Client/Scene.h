#ifndef SCENE_H
#define SCENE_H

#include "Event.h"

class Scene : public Event
{
public:
	Scene();

	virtual void OnLoop();

	virtual void Draw(SDL_Surface *Dest);
};

#endif // SCENE_H
