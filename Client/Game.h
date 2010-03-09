#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Scene.h"
#include "LoadingScene.h"

class Game : public Event
{
public:
    static Game& GetInstance()
    {
        static Game Instance;
        return Instance;
    }

    int OnExecute();

    bool OnInitialize();

    void OnLoop();

    void OnDraw();

    void OnEvent(SDL_Event *EventSource);

    void OnExit();

    void OnCleanup();

private:
    Game();
    Game(const Game &);
    Game& operator = (const Game&);

    Window MainWindow;

    Scene* MainScene;

    bool Running;
};

#endif // GAME_H
