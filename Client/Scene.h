#ifndef SCENE_H
#define SCENE_H

#include "Event.h"
#include "Font.h"
#include "GlobalDef.h"


class Scene : public Event
{
public:
	Scene();

	virtual void OnLoop();

	virtual void Draw(SDL_Surface *Dest);

	static void DrawVersion(SDL_Surface *Dest);
};

#endif // SCENE_H
