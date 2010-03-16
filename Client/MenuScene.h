#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public Scene
{
public:
    MenuScene();

    void OnLoop();

    void Draw(SDL_Surface *Dest);
	
	void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);
	
	void OnLButtonDown(int X, int Y);
	
	void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

private:
	enum Focus { Login, NewAccount, Exit } MenuFocus;
};

#endif // MENUSCENE_H
