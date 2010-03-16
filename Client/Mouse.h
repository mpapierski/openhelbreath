#ifndef MOUSE_H
#define MOUSE_H

#include "Event.h"

class Mouse : public Event
{
public:
	Mouse();

	void Draw(SDL_Surface *Dest);

	void OnEvent(SDL_Event *EventSource);

	void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);

private:
	int Mx;
	int My;
};

#endif // MOUSE_H
