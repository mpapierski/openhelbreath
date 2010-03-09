#include "Game.h"

Game::Game()
{
    Running = true;

    MainScene = new LoadingScene;
}

int Game::OnExecute()
{
    if(!OnInitialize())
    {
        return -1;
    }

    SDL_Event EventHandle;

    while(Running)
    {
        while(SDL_PollEvent(&EventHandle))
        {
            OnEvent(&EventHandle);

            MainScene->OnEvent(&EventHandle);
        }

        OnLoop();

        OnDraw();

        MainWindow.Update();
    }

    OnCleanup();

    return 0;
}

bool Game::OnInitialize()
{
    MainWindow.Create("HelGame", 640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    MainWindow.SetKeyRepeat(100, 500);
    MainWindow.SetCursorPos(320, 240);
    MainWindow.ShowCursor(false);

    return true;
}

void Game::OnLoop()
{

}

void Game::OnDraw()
{
    MainScene->Draw(MainWindow.GetSurface());
}

void Game::OnEvent(SDL_Event *EventSource)
{
    Event::OnEvent(EventSource);
}

void Game::OnExit()
{
    Running = false;
}

void Game::OnCleanup()
{
    MainWindow.Close();
}
