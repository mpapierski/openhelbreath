#ifndef SCENE_H
#define SCENE_H

#include "Event.h"

class Scene: public Event
{
	public:
		Scene();
		virtual ~Scene();
		virtual void onLoop();
		virtual void onDraw(SDL_Surface* dest);
};

#endif // SCENE_H
