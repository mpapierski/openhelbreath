#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include "Scene.h"
#include "TextEdit.h"
#include "ConnectingWidget.h"
#include "DialogBoxButtons.h"
#include "Socket.h"

class LoginScene: public Scene
{
	public:
		LoginScene();
		~LoginScene();
		void Draw(SDL_Surface *Dest);
		void OnEvent(SDL_Event *EventSource);
		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left,
				bool Right, bool Middle);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	private:
		void _Connect();
		void _Cancel();

		void __NotExistingAccount();
		void __PasswordMismatch();

		void Disconnect();

		enum Focus
		{
			Login, Password, Connect, Cancel
		} LoginFocus;
		TextEdit LoginEdit;
		TextEdit PasswordEdit;
		ConnectingWidget ConnectingBox;
		DialogBoxButtons DlgBox;
		Socket * MLSocket;
};

#endif // LOGINSCENE_H
