#include "Window.h"

Window::Window()
{
    WindowSurface = NULL;

    FpsCap = false;

    FpsLimit = 1;
    Frames = 0;
}

Window::~Window()
{

}

void Window::Create(const std::string &Title, int Width, int Height, int Depth, int Flags)
{
    Initialize();

    if((WindowSurface = SDL_SetVideoMode(Width, Height, Depth, Flags)) == NULL)
    {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    FpsTimer.Start();

    SDL_WM_SetCaption(Title.c_str(), NULL);
}

void Window::Close()
{
    SDL_Quit();
}

void Window::Update()
{
    SDL_Flip(WindowSurface);

    Frames++;

    if((FpsCap == true) && (FpsTimer.GetTicks() < 1000 / FpsLimit))
    {
        SDL_Delay((1000 / FpsLimit) - FpsTimer.GetTicks());
    }

    FpsTimer.Start();
}

void Window::Initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Surface *Window::GetSurface() const
{
    return WindowSurface;
}

int Window::GetWidth() const
{
    return WindowSurface->w;
}

int Window::GetHeight() const
{
    return WindowSurface->h;
}

void Window::SetFpsLimit(int Limit)
{
    if(Limit)
    {
        FpsCap = true;
        FpsLimit = Limit;
    }
}

void Window::SetKeyRepeat(int Delay, int Interval)
{
    SDL_EnableKeyRepeat(Delay, Interval);
}

void Window::SetCursorPos(unsigned short X, unsigned short Y)
{
    SDL_WarpMouse(X, Y);
}

void Window::ShowCursor(bool Show)
{
    if(!Show)
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
    else
        SDL_ShowCursor(SDL_ENABLE);
}
