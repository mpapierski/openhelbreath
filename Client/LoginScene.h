#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include "Scene.h"
#include "GameState.h"
#include "Sound.h"
#include "Sprite.h"

class CLoginScene : public CScene
{
public:
    CLoginScene();

    bool OnLoad();

    void OnRender(SDL_Surface *Surf_Dest);

    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);

    void OnLButtonDown(int X, int Y);

    void OnCleanup();

private:
    CSprite LoginSprite;

    enum Selection { LoginTextEdit = 0, PasswordTextEdit = 1, Connect = 2, Cancel = 3, AbbadonServer = 4, ApocalypseServer = 5 } LoginSelection;
};

#endif // LOGINSCENE_H
