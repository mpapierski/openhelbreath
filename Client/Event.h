#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>

class Event
{
	public:
		Event();
		virtual ~Event();
		virtual void onEvent(SDL_Event* eventSource);
		virtual void onInputFocus();
		virtual void onInputBlur();
		virtual void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		virtual void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
		virtual void onMouseFocus();
		virtual void onMouseBlur();
		virtual void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		virtual void onMouseWheel(bool up, bool down); //Not implemented
		virtual void onLButtonDown(int x, int y);
		virtual void onLButtonUp(int x, int y);
		virtual void onRButtonDown(int x, int y);
		virtual void onRButtonUp(int mX, int mY);
		virtual void onMButtonDown(int x, int y);
		virtual void onMButtonUp(int x, int y);
		virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
		virtual void onJoyButtonDown(Uint8 which, Uint8 button);
		virtual void onJoyButtonUp(Uint8 which, Uint8 button);
		virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);
		virtual void onJoyBall(Uint8 which, Uint8 ball, Sint16 relX, Sint16 relY);
		virtual void onMinimize();
		virtual void onRestore();
		virtual void onResize(int w, int h);
		virtual void onExpose();
		virtual void onExit();
		virtual void onUser(Uint8 type, int code, void* data1, void* data2);
};

#endif // EVENT_H
