#include "LoginScene.h"
#include "App.h"

CLoginScene::CLoginScene()
{
    LoginSelection = LoginTextEdit;
}

bool CLoginScene::OnLoad()
{
    if(!LoginSprite.SetImage("sprites/LoginDialog.pak", 0))
    {
        return false;
    }
    return true;
}

void CLoginScene::OnRender(SDL_Surface *Surf_Dest)
{
    CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 0, 0, 0, 0, 640, 480);
    switch(CApp::GetInstance().GameState)
    {
    case OnLogin:
        CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 39, 121, LoginSprite.Frame[2].x, LoginSprite.Frame[2].y, LoginSprite.Frame[2].w, LoginSprite.Frame[2].h);
        switch (LoginSelection)
        {
        case LoginTextEdit:
            //CSurface::OnDraw(Surf_Dest, Surf_Login, 385, 178, 133, 483, 163, 21);
            break;
        case PasswordTextEdit:
            //CSurface::OnDraw(Surf_Dest, Surf_Login, 385, 216, 300, 483, 163, 21);
            break;
        case Connect:
            CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 80, 282, LoginSprite.Frame[3].x, LoginSprite.Frame[3].y, LoginSprite.Frame[3].w, LoginSprite.Frame[3].h);
            break;
        case Cancel:
            CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 256, 282, LoginSprite.Frame[4].x, LoginSprite.Frame[4].y, LoginSprite.Frame[4].w, LoginSprite.Frame[4].h);
            break;
        }
        break;
    case OnSelectServer:
        CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 40, 121, LoginSprite.Frame[1].x, LoginSprite.Frame[1].y, LoginSprite.Frame[1].w, LoginSprite.Frame[1].h);
        switch(LoginSelection)
        {
        case AbbadonServer:
            CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 139, 176, LoginSprite.Frame[5].x, LoginSprite.Frame[5].y, LoginSprite.Frame[5].w, LoginSprite.Frame[5].h);
            break;
        case ApocalypseServer:
            CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 131, 204, LoginSprite.Frame[6].x, LoginSprite.Frame[6].y, LoginSprite.Frame[6].w, LoginSprite.Frame[6].h);
            break;
        case Cancel:
            CSurface::OnDraw(Surf_Dest, LoginSprite.GetImage(), 256, 282, LoginSprite.Frame[4].x, LoginSprite.Frame[4].y, LoginSprite.Frame[4].w, LoginSprite.Frame[4].h);
            break;
        }
        break;
    }
}

void CLoginScene::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_ESCAPE:
        switch(CApp::GetInstance().GameState)
        {
        case OnLogin:
            LoginSelection = LoginTextEdit;
            CApp::GetInstance().GameState = OnMenu;
            break;
        case OnSelectServer:
            CApp::GetInstance().GameState = OnLogin;
            LoginSelection = LoginTextEdit;
            break;
        }
        break;
    case SDLK_RETURN:
        switch(CApp::GetInstance().GameState)
        {
        case OnLogin:
            switch(LoginSelection)
            {
            case Cancel:
                CSound::SoundControl.Play(0);
                CApp::GetInstance().GameState = OnMenu;
                LoginSelection = LoginTextEdit;
                break;
            case Connect:
                CSound::SoundControl.Play(0);
                CApp::GetInstance().GameState = OnConnecting;
                LoginSelection = LoginTextEdit;
                break;
            }
            break;
        case OnSelectServer:
            switch(LoginSelection)
            {
            case AbbadonServer:
                CSound::SoundControl.Play(0);
                break;
            case ApocalypseServer:
                CSound::SoundControl.Play(0);
                break;
            case Cancel:
                CSound::SoundControl.Play(0);
                CApp::GetInstance().GameState = OnLogin;
                LoginSelection = LoginTextEdit;
                break;
            }
            break;
        }
        break;
    case SDLK_TAB:
    case SDLK_DOWN:
        switch(CApp::GetInstance().GameState)
        {
        case OnLogin:
            switch(LoginSelection)
            {
            case LoginTextEdit:
                LoginSelection = PasswordTextEdit;
                break;
            case PasswordTextEdit:
                LoginSelection = Connect;
                break;
            case Connect:
                LoginSelection = Cancel;
                break;
            case Cancel:
                LoginSelection = LoginTextEdit;
                break;
            }
            break;
        case OnSelectServer:
            switch(LoginSelection)
            {
            case AbbadonServer:
                LoginSelection = ApocalypseServer;
                break;
            case ApocalypseServer:
                LoginSelection = Cancel;
                break;
            case Cancel:
                LoginSelection =AbbadonServer;
                break;
            }
            break;
        }
        break;
    case SDLK_UP:
        switch(CApp::GetInstance().GameState)
        {
        case OnLogin:
            switch(LoginSelection)
            {
            case LoginTextEdit:
                LoginSelection = Cancel;
                break;
            case PasswordTextEdit:
                LoginSelection = LoginTextEdit;
                break;
            case Connect:
                LoginSelection = PasswordTextEdit;
                break;
            case Cancel:
                LoginSelection = Connect;
                break;
            }
            break;
        case OnSelectServer:
            switch(LoginSelection)
            {
            case AbbadonServer:
                LoginSelection = Cancel;
                break;
            case ApocalypseServer:
                LoginSelection = AbbadonServer;
                break;
            case Cancel:
                LoginSelection = ApocalypseServer;
                break;
            }
            break;
        }
        break;
    }
}

void CLoginScene::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
    switch(CApp::GetInstance().GameState)
    {
    case OnLogin:
        if(mY > 282 && mY < 302)
        {
            // Cancel Button
            if(mX > 256 && mX < 322)
            {
                LoginSelection = Cancel;
            }
            // Connect Button
            if(mX > 80 && mX < 163)
            {
                LoginSelection = Connect;
            }
        }
        break;
    case OnSelectServer:
        if(mX > 139 && mX < 277)
        {
            if(mY > 176 && mY < 195)
            {
                LoginSelection = AbbadonServer;
            }
        }
        if(mX > 131 && mX < 288)
        {
            if(mY > 204 && mY < 223)
            {
                LoginSelection = ApocalypseServer;
            }
        }
        if(mY > 282 && mY < 302)
        {
            if(mX > 256 && mX < 322)
            {
                LoginSelection = Cancel;
            }
        }
        break;
    }
}

void CLoginScene::OnLButtonDown(int X, int Y)
{
    switch(CApp::GetInstance().GameState)
    {
    case OnLogin:
        if(Y > 282 && Y < 302)
        {
            //Connect Button
            if(X > 80 && X < 163)
            {
                CSound::SoundControl.Play(0);
                LoginSelection = AbbadonServer;
                CApp::GetInstance().GameState = OnConnecting;
            }
            //Cancel Button
            if(X > 256 && X < 322)
            {
                CSound::SoundControl.Play(0);
                LoginSelection = LoginTextEdit;
                CApp::GetInstance().GameState = OnMenu;
            }
        }
        break;
    case OnSelectServer:
        //Abbadon Server Button
        if(X > 139 && X < 277)
        {
            if(Y > 176 && Y < 195)
            {
                CSound::SoundControl.Play(0);
                LoginSelection = AbbadonServer;
            }
        }
        //Apocalypse Server Button
        if(X > 131 && X < 288)
        {
            if(Y > 204 && Y < 223)
            {
                CSound::SoundControl.Play(0);
                LoginSelection = ApocalypseServer;
            }
        }
        //Cancel Button
        if(Y > 282 && Y < 302)
        {
            if(X > 256 && X < 322)
            {
                CSound::SoundControl.Play(0);
                LoginSelection = LoginTextEdit;
                CApp::GetInstance().GameState = OnLogin;
            }
        }
        break;
    }
}

void CLoginScene::OnCleanup()
{

}
