#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Event.h"
#include "Timer.h"

class Window : public Event
{
public:
	Window();

	virtual ~Window();

	void Create(const std::string &Title, int Width, int Height, int Depth, int Flags);

	void Close();

	void Update();

	SDL_Surface *GetSurface() const;

	int GetWidth() const;

	int GetHeight() const;

	void SetFpsLimit(int Limit);

	void SetKeyRepeat(int Delay, int Interval);

	void SetCursorPos(unsigned short X, unsigned short Y);

	void ShowCursor(bool Show);

private:
	void Initialize();

	SDL_Surface *WindowSurface;

	bool FpsCap;

	int FpsLimit;
	int Frames;

	Timer FpsTimer;

	Timer FrameTimer;
};

inline SDL_Surface *Window::GetSurface() const
{
	return WindowSurface;
}

#endif // WINDOW_H
