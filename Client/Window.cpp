#include "Window.h"

Window::Window()
{
	windowSurface = NULL;

	fpsCap = false;

	fpsLimit = 1;
	frames = 0;
}

Window::~Window()
{

}

void Window::create(const std::string& title, int width, int height, int depth, int flags)
{
	initialize();

	if((windowSurface = SDL_SetVideoMode(width, height, depth, flags)) == NULL)
	{
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
		exit(1);
	}

	fpsTimer.start();

	frameTimer.start();

	SDL_WM_SetCaption(title.c_str(), NULL);
}

void Window::close()
{
	TTF_Quit();

	SDL_Quit();
}

void Window::update()
{
	SDL_Flip(windowSurface);

	frames++;

	if(frameTimer.getTicks() > 1000)
	{
		lastFps = frames;

		frames = 0;

		frameTimer.start();
	}

	if((fpsCap == true) && (fpsTimer.getTicks() < 1000 / fpsLimit))
	{
		SDL_Delay((1000 / fpsLimit) - fpsTimer.getTicks());
	}

	fpsTimer.start();
}

void Window::initialize()
{
    fprintf(stdout, "Initializing SDL system\r\n");
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    fprintf(stdout, "Initializing font system\r\n");
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Unable to init SDL_ttf: %s\n", TTF_GetError());
        exit(2);
    }
}

int Window::getWidth() const
{
	return windowSurface->w;
}

int Window::getHeight() const
{
	return windowSurface->h;
}

int Window::getFps() const
{
	return lastFps;
}

void Window::setFpsLimit(int limit)
{
	if(limit)
	{
		fpsCap = true;
		fpsLimit = limit;
	}
}

void Window::setKeyRepeat(int delay, int interval)
{
	SDL_EnableKeyRepeat(delay, interval);
}

void Window::setCursorPos(unsigned short x, unsigned short y)
{
	SDL_WarpMouse(x, y);
}

void Window::showCursor(bool show)
{
	if(!show)
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
		SDL_ShowCursor(SDL_ENABLE);
}
