#include "MenuScene.h"

extern CGameState GameState;

CMenuScene::CMenuScene()
{
    Focus_Menu = Login;
}

bool CMenuScene::OnLoad()
{
    if(!MenuSprite.SetImage("sprites/New-Dialog.pak", 1))
    {
        return false;
    }
    return true;
}

void CMenuScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, MenuSprite.GetImage(), 0, 0, 0, 0, 640, 480);
    switch(Focus_Menu)
    {
    case Login:
        CSurface::OnDraw(Surf_Dest, MenuSprite.GetImage(), 385, 178, MenuSprite.Frame[1].x, MenuSprite.Frame[1].y, MenuSprite.Frame[1].w, MenuSprite.Frame[1].h);
        break;
    case NewAccount:
        CSurface::OnDraw(Surf_Dest, MenuSprite.GetImage(), 385, 216, MenuSprite.Frame[2].x, MenuSprite.Frame[2].y, MenuSprite.Frame[2].w, MenuSprite.Frame[2].h);
        break;
    case Exit:
        CSurface::OnDraw(Surf_Dest, MenuSprite.GetImage(), 385, 255, MenuSprite.Frame[3].x, MenuSprite.Frame[3].y, MenuSprite.Frame[3].w, MenuSprite.Frame[3].h);
        break;
    }
}

void CMenuScene::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_ESCAPE:
        GameState.ChangeGameState(OnQuit);
        break;
    case SDLK_RETURN:
        switch(Focus_Menu)
        {
        case Login:
            CSound::SoundControl.Play(0);
            GameState.ChangeGameState(OnLogin);
            break;
        case NewAccount:
            CSound::SoundControl.Play(0);
            break;
        case Exit:
            CSound::SoundControl.Play(0);
            GameState.ChangeGameState(OnQuit);
            break;
        }
        break;
    case SDLK_DOWN:
        if(Focus_Menu == Login)
        {
            Focus_Menu = NewAccount;
            return;
        }
        if(Focus_Menu == NewAccount)
        {
            Focus_Menu = Exit;
            return;
        }
        if(Focus_Menu == Exit)
        {
            Focus_Menu = Login;
            return;
        }
        break;
    case SDLK_UP:
        if(Focus_Menu == Login)
        {
            Focus_Menu = Exit;
            return;
        }
        if(Focus_Menu == NewAccount)
        {
            Focus_Menu = Login;
            return;
        }
        if(Focus_Menu == Exit)
        {
            Focus_Menu = NewAccount;
            return;
        }
        break;

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
            GameState.ChangeGameState(OnLogin);
        }
        if(Y > 216 && Y < 237)
        {
            CSound::SoundControl.Play(0);
        }
        if(Y > 255 && Y < 276)
        {
            CSound::SoundControl.Play(0);
            GameState.ChangeGameState(OnQuit);
        }
    }
}

void CMenuScene::OnCleanup()
{

}
