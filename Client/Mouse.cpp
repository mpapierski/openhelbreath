#include "Mouse.h"

Mouse::Mouse()
{
	cursorX = 0;
	cursorY = 0;
}

Mouse::~Mouse()
{

}

void Mouse::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, cursorX, cursorY, SPRID_INTERFACE_CURSOR, INTERFACE_CURSOR_ARROW);
}

void Mouse::onEvent(SDL_Event* eventSource)
{
	Event::onEvent(eventSource);
}

void Mouse::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	cursorX = x;
	cursorY = y;
}
