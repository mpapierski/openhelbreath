#include "Mouse.h"

CMouse::CMouse()
{
    x = 0;
    y = 0;
}

bool CMouse::OnLoad(const std::string &FileName)
{
    if(!MouseSprite.SetImage(FileName, 0))
    {
        return false;
    }
    CSurface::Transparent(MouseSprite.GetImage(), 255, 132, 66);
    return true;
}

void CMouse::OnEvent(SDL_Event *Event)
{
    CEvent::OnEvent(Event);
}

void CMouse::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    x = mX;
    y = mY;
}

void CMouse::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, MouseSprite.GetImage(), x, y, MouseSprite.Frame[0].x, MouseSprite.Frame[0].y, MouseSprite.Frame[0].w, MouseSprite.Frame[0].h);
}

void CMouse::OnCleanup()
{

}
