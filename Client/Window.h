#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

#include "Event.h"

class Window : public Event
{
public:
    Window();

    virtual ~Window();

    void Create(const std::string& Title, int Width, int Height, int Depth, int Flags);

    void Close();

    void Update();

    SDL_Surface *GetSurface() const;

    int GetWidth() const;

    int GetHeight() const;

    void SetKeyRepeat(int Delay, int Interval);

    void SetCursorPos(unsigned short X, unsigned short Y);

    void ShowCursor(bool Show);

private:
    void Initialize();

    SDL_Surface *WindowSurface;
};

#endif // WINDOW_H
