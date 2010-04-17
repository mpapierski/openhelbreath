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
		LoginScene(const std::string &WS = DEF_SERVER_NAME1);
		~LoginScene();
		void Draw(SDL_Surface *Dest);
		void OnEvent(SDL_Event *EventSource);
		void OnUser(Uint8 Type, int Code, void *Data1, void *Data2);
		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	private:
		void _Connect();
		void _Cancel();

		void __NotExistingAccount();
		void __PasswordMismatch();
		void __WorldNotActivated();
		void __AccountBlocked(int Y, int M, int D);
		void Disconnect();

		enum Focus
		{
			Login, Password, Connect, Cancel
		} LoginFocus;

		gui::TextEdit LoginEdit;
		gui::TextEdit PasswordEdit;
		ConnectingWidget ConnectingBox;
		DialogBoxButtons DlgBox;
		Socket *MLSocket;
		std::string WorldServerName;
};

#endif // LOGINSCENE_H
