#include "MenuScene.h"
#include "App.h"

CMenuScene::CMenuScene()
{
    Focus_Menu = Login;
}

void CMenuScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[1].GetImage(), 0, 0, 0, 0, 640, 480);
    switch(Focus_Menu)
    {
    case Login:
        CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[1].GetImage(), 385, 178, CApp::GetInstance().Sprite[1].Frame[1].x, CApp::GetInstance().Sprite[1].Frame[1].y, CApp::GetInstance().Sprite[1].Frame[1].w, CApp::GetInstance().Sprite[1].Frame[1].h);
        break;
    case NewAccount:
        CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[1].GetImage(), 385, 216, CApp::GetInstance().Sprite[1].Frame[2].x, CApp::GetInstance().Sprite[1].Frame[2].y, CApp::GetInstance().Sprite[1].Frame[2].w, CApp::GetInstance().Sprite[1].Frame[2].h);
        break;
    case Exit:
        CSurface::OnDraw(Surf_Dest, CApp::GetInstance().Sprite[1].GetImage(), 385, 255, CApp::GetInstance().Sprite[1].Frame[3].x, CApp::GetInstance().Sprite[1].Frame[3].y, CApp::GetInstance().Sprite[1].Frame[3].w, CApp::GetInstance().Sprite[1].Frame[3].h);
        break;
    }
}

void CMenuScene::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_ESCAPE:
        CApp::GetInstance().GameState = OnQuit;
        break;
    case SDLK_RETURN:
        CSound::SoundControl.Play(0);
        switch(Focus_Menu)
        {
        case Login:
            CApp::GetInstance().GameState = OnLogin;
            break;
        case NewAccount:
            break;
        case Exit:
            CApp::GetInstance().GameState = OnQuit;
            break;
        }
        break;
	case SDLK_TAB:
    case SDLK_DOWN:
        switch(Focus_Menu)
        {
        case Login:
			Focus_Menu = NewAccount;
            break;
        case NewAccount:
			Focus_Menu = Exit;
            break;
        case Exit:
			Focus_Menu = Login;
            break;
        }
        break;
    case SDLK_UP:
		switch(Focus_Menu)
        {
        case Login:
			Focus_Menu = Exit;
            break;
        case NewAccount:
			Focus_Menu = Login;
            break;
        case Exit:
			Focus_Menu = NewAccount;
            break;
        }
        break;
    default: ;
    }
}

void CMenuScene::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
    if((mX > 385 && mX < 548) && (mY > 178 && mY < 199)) Focus_Menu = Login;
    if((mX > 385 && mX < 548) && (mY > 216 && mY < 237)) Focus_Menu = NewAccount;
    if((mX > 385 && mX < 548) && (mY > 255 && mY < 276)) Focus_Menu = Exit;
}

void CMenuScene::OnLButtonDown(int X, int Y)
{
    if(X > 385 && X < 548)
    {
        if(Y > 178 && Y < 199)
        {
            CSound::SoundControl.Play(0);
            CApp::GetInstance().GameState = OnLogin;
        }
        if(Y > 216 && Y < 237)
        {
            CSound::SoundControl.Play(0);
        }
        if(Y > 255 && Y < 276)
        {
            CSound::SoundControl.Play(0);
            CApp::GetInstance().GameState = OnQuit;
        }
    }
}

void CMenuScene::OnCleanup()
{

}
