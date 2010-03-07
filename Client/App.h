#ifndef APP_H
#define APP_H

#include <string>

#include <SDL.h>

#include "Event.h"
#include "ExitScene.h"
#include "Font.h"
#include "GameState.h"
#include "LoadScene.h"
#include "LoginScene.h"
#include "MenuScene.h"
//#include "MessageBox.h"
#include "Mouse.h"
#include "Timer.h"
#include "Sound.h"
#include "Surface.h"

class CApp : public CEvent
{
private:
	int ScreenWidth;
    int ScreenHeight;
    int ScreenDepth;
    int ScreenFlags;
    int FRAMES_PER_SECOND;
    int frame;

    bool Running;
    bool cap;

    std::string AppName;
    std::string TestString;

    CTimer fps;
    CTimer fpsCounter;
    CTimer quitTimer;

    CFont Font;

    CMouse Mouse;

    CMenuScene MenuScene;

    CLoadScene LoadScene;

    CLoginScene LoginScene;

    CExitScene ExitScene;

    //CMessageBox MessageBox;

    SDL_Surface *Surf_Display;
    SDL_Surface *Surf_Test;

public:
    CApp();

    int OnExecute();

    bool OnInit();

    void OnEvent(SDL_Event *Event);

    void OnExit();

    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnLoop();

    void OnRender();

    void OnCleanup();
};

#endif // APP_H
