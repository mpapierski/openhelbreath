#include "LoadScene.h"
#include "App.h"

CLoadScene::CLoadScene()
{
    procent = 0;
}

void CLoadScene::OnLoop()
{
    procent++;
    if(procent > 100)
    {
        CApp::GetInstance().GameState = OnMenu;
    }
}

void CLoadScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[0].GetImage(), 0, 0, 0, 0, 640, 480);
    CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[0].GetImage(), 473, 443, 268, 484, (procent + 17), 17);
}
