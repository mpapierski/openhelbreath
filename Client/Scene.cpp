#include "Scene.h"

CScene::CScene()
{

}
bool CScene::OnLoad()
{
    return true;
}

void CScene::OnLoop()
{

}

void CScene::OnRender(SDL_Surface *Surf_Dest)
{

}

void CScene::OnCleanup()
{

}

void CScene::OnEvent(SDL_Event *Event)
{
    CEvent::OnEvent(Event);
}
