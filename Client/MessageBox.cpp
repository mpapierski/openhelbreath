#include "MessageBox.h"

extern CGameState GameState;

CMessageBox::CMessageBox()
{
    //ctor
}

void CMessageBox::OnRender(SDL_Surface *Surf_Dest)
{
//    CSurface::OnDraw(Surf_Dest, Surf_Dialog, 0, 0, 10, 271, 315, 171);
}

void CMessageBox::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_ESCAPE:
        GameState.ChangeGameState(OnLogin);
        break;
    case SDLK_RETURN:
        GameState.ChangeGameState(OnSelectServer);
        break;
    }
}
