#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Event.h"
#include "Timer.h"

class Window : public Event
{
	public:
		Window();
		virtual ~Window();
		void create(const std::string& title, int width, int height, int depth, int flags);
		void close();
		void update();
		SDL_Surface* getSurface() const;
		int getWidth() const;
		int getHeight() const;
		int getFps() const;
		void setFpsLimit(int limit);
		void setKeyRepeat(int delay, int interval);
		void setCursorPos(unsigned short x, unsigned short y);
		void showCursor(bool show);

	private:
		void initialize();

		SDL_Surface* windowSurface;
		bool fpsCap;
		int fpsLimit;
		int frames;
		int lastFps;
		Timer fpsTimer;
		Timer frameTimer;
};

inline SDL_Surface* Window::getSurface() const
{
	return windowSurface;
}

#endif // WINDOW_H
