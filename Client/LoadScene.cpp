#include "LoadScene.h"

extern CGameState GameState;

CLoadScene::CLoadScene()
{
    procent = 0;
}

bool CLoadScene::OnLoad()
{
    if(!LoadSprite.SetImage("sprites/New-Dialog.pak", 0))
    {
        return false;
    }
    return true;
}

void CLoadScene::OnLoop()
{
    procent++;
    if(procent > 100)
    {
        GameState.ChangeGameState(OnMenu);
    }
}

void CLoadScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, LoadSprite.GetImage(), 0, 0, 0, 0, 640, 480);
    CSurface::OnDraw(Surf_Dest, LoadSprite.GetImage(), 473, 443, 268, 484, (procent + 17), 17);
}

void CLoadScene::OnCleanup()
{

}
