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

	inline void DrawVersion(SDL_Surface * Dest) const;
};

#endif // SCENE_H
