#ifndef SIGNUPSCENE_H
#define SIGNUPSCENE_h

#include "Scene.h"
#include "TextEdit.h"

#define DEF_INPUTTOTAL 6

struct FormItem
{
	std::string Label;
	TextEdit Input;
	std::string Info[3];
};

class SignupScene: public Scene
{
	public:
		SignupScene();
		~SignupScene();
		void Draw(SDL_Surface * Dest);
		void OnEvent(SDL_Event * EventSource);
		void OnMouseMove(
				int X,
				int Y,
				int RelX,
				int RelY,
				bool Left,
				bool Right,
				bool Middle);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	private:
		void _Cancel();
		void _Ok();
		void _Reset();

		FormItem Form[DEF_INPUTTOTAL];
		int FormFocus;

		void SetFocus(int NewId);

};

#endif
