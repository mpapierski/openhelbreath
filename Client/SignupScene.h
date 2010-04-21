#ifndef SIGNUPSCENE_H
#define SIGNUPSCENE_H

#include "Scene.h"
#include "TextEdit.h"
#include "Buffers.h"

#define DEF_INPUTTOTAL 6

struct FormItem
{
		std::string Label;
		gui::TextEdit Input;
		std::string Info[3];
};

class SignupScene: public Scene
{
	public:
		SignupScene();
		virtual ~SignupScene();
		void Draw(SDL_Surface *Dest);
		void OnEvent(SDL_Event *EventSource);
		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
		void OnUser(Uint8 Type, int Code, void *Data1, void *Data2);
	private:
		void Disconnect();
		void SetFocus(int NewId);
		void _Cancel();
		void _Ok();
		void _Reset();

		FormItem Form[DEF_INPUTTOTAL];
		int FormFocus;

		Socket * MLSocket;
		ConnectingWidget ConnectingBox;
		DialogBoxButtons DlgBox;
};

#endif
