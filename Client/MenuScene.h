#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SDL.h>

#include "Scene.h"
#include "GameState.h"
#include "Sound.h"
#include "Sprite.h"

class CMenuScene : public CScene
{
public:
    CMenuScene();

    void OnRender(SDL_Surface *Surf_Dest);

    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);

    void OnLButtonDown(int X, int Y);

    void OnCleanup();

private:
    enum Selection { Login = 0, NewAccount = 2, Exit = 3} Focus_Menu;
};

#endif // MENUSCENE_H
