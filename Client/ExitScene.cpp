#include "ExitScene.h"
#include "App.h"

CExitScene::CExitScene()
{

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
    CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[2].GetImage(), 0, 0, CApp::GetInstance().Sprite[2].Frame[0].x, CApp::GetInstance().Sprite[2].Frame[0].y, CApp::GetInstance().Sprite[2].Frame[0].w, CApp::GetInstance().Sprite[2].Frame[0].h);
    if(exitTimer.get_ticks() > 500)
    {
        CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[2].GetImage(), 255, 123, CApp::GetInstance().Sprite[2].Frame[1].x, CApp::GetInstance().Sprite[2].Frame[1].y, CApp::GetInstance().Sprite[2].Frame[1].w, CApp::GetInstance().Sprite[2].Frame[1].h);
    }
}
