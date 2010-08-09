#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include "Scene.h"
#include "TextEdit.h"
#include "ConnectingWidget.h"
#include "MessageDialog.h"
#include "Timer.h"

class LoginScene: public Scene
{
	public:
		LoginScene(const std::string& serverName = DEF_SERVER_NAME1);
		~LoginScene();
		void onLoop();
		void onDraw(SDL_Surface* dest);
		void onEvent(SDL_Event* eventSource);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void onUser(Uint8 type, int code, void* data1, void* data2);

	private:
		void connect();
		void disconnect();
		void cancel();
		void notExistingAccount();
		void passwordMismatch();
		void worldNotActivated();
		void accountBlocked(int Y, int M, int D);

		enum Focus
		{
			LOGIN, PASSWORD, CONNECT, CANCEL
		} loginFocus;

		gui::TextEdit loginEdit;
		gui::TextEdit passwordEdit;
		gui::ConnectingWidget connectingBox;
		gui::MessageDialog msgBox;

		Socket* MLSocket;
		std::string worldServerName;
		SDL_Surface* form;
		Timer formTimer;
		int alpha;
};

#endif // LOGINSCENE_H
