#ifndef SIGNUPSCENE_H
#define SIGNUPSCENE_H

#include "Scene.h"
#include "Label.h"
#include "TextEdit.h"
#include "ConnectingWidget.h"
#include "MessageDialog.h"

struct FormItem
{
		gui::Label name;
		gui::Label tip;
		gui::TextEdit input;
};

class SignupScene : public Scene
{
	public:
		SignupScene();
		virtual ~SignupScene();
		void onDraw(SDL_Surface* dest);
		void onEvent(SDL_Event* eventSource);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void onLButtonDown(int x, int y);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void onUser(Uint8 Type, int Code, void* Data1, void* Data2);

	private:
		void setFocus(int newId);
		void connect();
		void disconnect();
		void cancel();
		void reset();

		FormItem form[6];
		int formFocus;

		Socket* MLSocket;
		gui::ConnectingWidget connectingBox;
		gui::MessageDialog dlgBox;
};

#endif // SIGNUPSCENE_H
