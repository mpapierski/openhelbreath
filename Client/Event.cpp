#include "Event.h"

Event::Event()
{

}

Event::~Event()
{

}

void Event::OnEvent(SDL_Event* EventSource)
{
    switch (EventSource->type)
    {
    case SDL_ACTIVEEVENT:
    {
        switch (EventSource->active.state)
        {
        case SDL_APPMOUSEFOCUS:
        {
            if(EventSource->active.gain) OnMouseFocus();
            else OnMouseBlur();
            break;
        }
        case SDL_APPINPUTFOCUS:
        {
            if(EventSource->active.gain) OnInputFocus();
            else OnInputBlur();
            break;
        }
        case SDL_APPACTIVE:
        {
            if(EventSource->active.gain) OnRestore();
            else OnMinimize();
            break;
        }
        }
        break;
    }

    case SDL_KEYDOWN:
    {
        OnKeyDown(EventSource->key.keysym.sym, EventSource->key.keysym.mod, EventSource->key.keysym.unicode);
        break;
    }

    case SDL_KEYUP:
    {
        OnKeyUp(EventSource->key.keysym.sym, EventSource->key.keysym.mod, EventSource->key.keysym.unicode);
        break;
    }

    case SDL_MOUSEMOTION:
    {
        OnMouseMove(EventSource->motion.x, EventSource->motion.y, EventSource->motion.xrel, EventSource->motion.yrel, (EventSource->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0, (EventSource->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0, (EventSource->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
        break;
    }

    case SDL_MOUSEBUTTONDOWN:
    {
        switch(EventSource->button.button)
        {
        case SDL_BUTTON_LEFT:
        {
            OnLButtonDown(EventSource->button.x, EventSource->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            OnRButtonDown(EventSource->button.x, EventSource->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            OnMButtonDown(EventSource->button.x, EventSource->button.y);
            break;
        }
        }
        break;
    }

    case SDL_MOUSEBUTTONUP:
    {
        switch (EventSource->button.button)
        {
        case SDL_BUTTON_LEFT:
        {
            OnLButtonUp(EventSource->button.x, EventSource->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            OnRButtonUp(EventSource->button.x, EventSource->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            OnMButtonUp(EventSource->button.x, EventSource->button.y);
            break;
        }
        }
        break;
    }

    case SDL_JOYAXISMOTION:
    {
        OnJoyAxis(EventSource->jaxis.which, EventSource->jaxis.axis, EventSource->jaxis.value);
        break;
    }

    case SDL_JOYBALLMOTION:
    {
        OnJoyBall(EventSource->jball.which, EventSource->jball.ball, EventSource->jball.xrel, EventSource->jball.yrel);
        break;
    }

    case SDL_JOYHATMOTION:
    {
        OnJoyHat(EventSource->jhat.which, EventSource->jhat.hat, EventSource->jhat.value);
        break;
    }
    case SDL_JOYBUTTONDOWN:
    {
        OnJoyButtonDown(EventSource->jbutton.which, EventSource->jbutton.button);
        break;
    }

    case SDL_JOYBUTTONUP:
    {
        OnJoyButtonUp(EventSource->jbutton.which, EventSource->jbutton.button);
        break;
    }

    case SDL_QUIT:
    {
        OnExit();
        break;
    }

    case SDL_SYSWMEVENT:
    {
        //Ignore
        break;
    }

    case SDL_VIDEORESIZE:
    {
        OnResize(EventSource->resize.w, EventSource->resize.h);
        break;
    }

    case SDL_VIDEOEXPOSE:
    {
        OnExpose();
        break;
    }

    default:
    {
        OnUser(EventSource->user.type, EventSource->user.code, EventSource->user.data1, EventSource->user.data2);
        break;
    }
    }
}

void Event::OnInputFocus()
{
    // pure virtual
}

void Event::OnInputBlur()
{
    // pure virtual
}

void Event::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
    // pure virtual
}

void Event::OnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
    // pure virtual
}

void Event::OnMouseFocus()
{
    // pure virtual
}

void Event::OnMouseBlur()
{
    // pure virtual
}

void Event::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
{
    // pure virtual
}

void Event::OnMouseWheel(bool Up, bool Down)
{
    // pure virtual
}

void Event::OnLButtonDown(int X, int Y)
{
    // pure virtual
}

void Event::OnLButtonUp(int X, int Y)
{
    // pure virtual
}

void Event::OnRButtonDown(int X, int Y)
{
    // pure virtual
}

void Event::OnRButtonUp(int mX, int mY)
{
    // pure virtual
}

void Event::OnMButtonDown(int X, int Y)
{
    // pure virtual
}

void Event::OnMButtonUp(int X, int Y)
{
    // pure virtual
}

void Event::OnJoyAxis(Uint8 Which, Uint8 Axis, Sint16 Value)
{
    // pure virtual
}

void Event::OnJoyButtonDown(Uint8 Which, Uint8 Button)
{
    // pure virtual
}

void Event::OnJoyButtonUp(Uint8 Which, Uint8 Button)
{
    // pure virtual
}

void Event::OnJoyHat(Uint8 Which, Uint8 Hat, Uint8 Value)
{
    // pure virtual
}

void Event::OnJoyBall(Uint8 Which, Uint8 Ball, Sint16 RelX, Sint16 RelY)
{
    // pure virtual
}

void Event::OnMinimize()
{
    // pure virtual
}

void Event::OnRestore()
{
    // pure virtual
}

void Event::OnResize(int W, int H)
{
    // pure virtual
}

void Event::OnExpose()
{
    // pure virtual
}

void Event::OnExit()
{
    // pure virtual
}

void Event::OnUser(Uint8 Type, int Code, void* Data1, void* Data2)
{
    // pure virtual
}
