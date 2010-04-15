#ifndef SELECTCHARSCENE_H
#define SELECTCHARSCENE_H

#include "Scene.h"

class SelectCharScene: public Scene
{
	public:
		SelectCharScene();
		~SelectCharScene();

		void Draw(SDL_Surface *Dest);

		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);

		void OnLButtonDown(int X, int Y);

		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	private:
		enum Focus
		{
			Start, CreateNewChar, DelChar, ChangePasswd, Logout
		} ButtonFocus;

		int SlotSelect;
};

#endif // SELECTCHARSCENE_H
