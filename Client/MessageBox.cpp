#include "MessageBox.h"
#include "App.h"

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
    if(sym == SDLK_ESCAPE) CApp::GetInstance().GameState = OnLogin;
    if(sym == SDLK_RETURN) CApp::GetInstance().GameState = OnSelectServer;
}
