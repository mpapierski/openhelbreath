#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "Scene.h"
#include "GameState.h"

class CMessageBox : public CScene
{
public:
    CMessageBox();

    void OnRender(SDL_Surface *Surf_Dest);

    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif // MESSAGEBOX_H
