#ifndef PLAYGROUNDSCENE_H
#define PLAYGROUNDSCENE_H

#include "Scene.h"
#include "Widget.h"

class PlayGroundScene : public Scene
{
    public:
        PlayGroundScene();
        ~PlayGroundScene();
        void onDraw(SDL_Surface* dest);
        void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void onExit();
    private:
        int monster_id;
        int orientation;
};

#endif // PLAYGROUNDSCENE_H
