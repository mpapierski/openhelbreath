#ifndef GAMESTATE_H
#define GAMESTATE_H

enum gState { OnLoad = 0, OnMenu = 1, OnLogin = 2, OnSelectServer = 3, OnConnecting = 4, OnQuit = 5};

class CGameState
{
public:
    gState State;

    void ChangeGameState(gState cState);

    gState getGameStatus()
    {
        return State;
    }
};

#endif // GAMESTATE_H
