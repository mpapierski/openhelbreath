#ifndef MOUSE_H
#define MOUSE_H

#include "Event.h"
#include "SpriteBank.h"

class Mouse : public Event
{
	public:
		Mouse();
		~Mouse();
		void onDraw(SDL_Surface* dest);
		void onEvent(SDL_Event* eventSource);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);

	private:
		int cursorX;
		int cursorY;
};

#endif // MOUSE_H
