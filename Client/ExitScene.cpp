#include "ExitScene.h"

CExitScene::CExitScene()
{

}

bool CExitScene::OnLoad()
{
    if(!ExitSprite.SetImage("sprites/New-Dialog.pak", 2))
    {
        return false;
    }
    return true;
}

void CExitScene::OnLoop()
{
    if(!exitTimer.is_started())
    {
        exitTimer.start();
    }
}

void CExitScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, ExitSprite.GetImage(), 0, 0, ExitSprite.Frame[0].x, ExitSprite.Frame[0].y, ExitSprite.Frame[0].w, ExitSprite.Frame[0].h);
    if(exitTimer.get_ticks() > 500)
    {
        CSurface::OnDraw(Surf_Dest, ExitSprite.GetImage(), 255, 123, ExitSprite.Frame[1].x, ExitSprite.Frame[1].y, ExitSprite.Frame[1].w, ExitSprite.Frame[1].h);
    }
}

void CExitScene::OnCleanup()
{

}
