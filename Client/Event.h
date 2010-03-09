#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>

class Event
{
public:
    Event();

    virtual ~Event();

    virtual void OnEvent(SDL_Event* EventSource);

    virtual void OnInputFocus();

    virtual void OnInputBlur();

    virtual void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

    virtual void OnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

    virtual void OnMouseFocus();

    virtual void OnMouseBlur();

    virtual void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);

    virtual void OnMouseWheel(bool Up, bool Down);  //Not implemented

    virtual void OnLButtonDown(int X, int Y);

    virtual void OnLButtonUp(int X, int Y);

    virtual void OnRButtonDown(int X, int Y);

    virtual void OnRButtonUp(int mX, int mY);

    virtual void OnMButtonDown(int X, int Y);

    virtual void OnMButtonUp(int X, int Y);

    virtual void OnJoyAxis(Uint8 Which, Uint8 Axis, Sint16 Value);

    virtual void OnJoyButtonDown(Uint8 Which, Uint8 Button);

    virtual void OnJoyButtonUp(Uint8 Which, Uint8 Button);

    virtual void OnJoyHat(Uint8 Which, Uint8 Hat, Uint8 Value);

    virtual void OnJoyBall(Uint8 Which, Uint8 Ball, Sint16 RelX, Sint16 RelY);

    virtual void OnMinimize();

    virtual void OnRestore();

    virtual void OnResize(int W, int H);

    virtual void OnExpose();

    virtual void OnExit();

    virtual void OnUser(Uint8 Type, int Code, void* Data1, void* Data2);
};

#endif // EVENT_H
