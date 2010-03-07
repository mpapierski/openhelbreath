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

private:
	CApp();
    CApp(const CApp &);
    CApp& operator = (const CApp&);

public:
	GState GameState;

public:
    static CApp &GetInstance()
    {
		static CApp instance;
		return instance;
    }

    int OnExecute();

    bool OnInit();

    void OnEvent(SDL_Event *Event);

    void OnExit();

    void OnLoop();

    void OnRender();

    void OnCleanup();
};

#endif // APP_H
