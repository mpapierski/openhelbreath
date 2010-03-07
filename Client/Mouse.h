#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

#include "Event.h"
#include "Sprite.h"
#include "Surface.h"

class CMouse : public CEvent
{
public:
    CMouse();

    bool OnLoad(const std::string &FileName);

    void OnEvent(SDL_Event *Event);

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

    void OnRender(SDL_Surface *Surf_Dest);

    void OnCleanup();

private:
    CSprite MouseSprite;
    int x;
    int y;
};

#endif // MOUSE_H
