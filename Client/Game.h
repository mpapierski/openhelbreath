//
// Main window initialization and game loop
//

#ifndef GAME_H
#define GAME_H

#include "Socket.h"
#include "NetMessages.h"
#include "GlobalDef.h"

#include "Window.h"
#include "Mouse.h"
#include "SpriteBank.h"
#include "SoundBank.h"
#include "Font.h"

#include "PlayGroundScene.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "ExitScene.h"
#include "SignupScene.h"
#include "SelectServerScene.h"
#include "LoginScene.h"
#include "VersionNotMatchScene.h"
#include "SelectCharScene.h"
#include "CreateNewCharScene.h"

class Game: public Event
{
	public:
		static Game &getInstance()
		{
			static Game Instance;
			return Instance;
		}

		int onExecute();
		bool onInitialize();
		void onLoop();
		void onDraw();
		void onEvent(SDL_Event *EventSource);
		void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void onExit();
		void onQuit();
		void onCleanup();
		void changeScene(Scene* newScene);
		static void drawVersion(SDL_Surface* dest);

	private:
		Game();
		Game(const Game &);
		Game& operator =(const Game&);
                bool initializeAudio();
                bool initializeFonts();

		Window mainWindow;
		Mouse mouseCursor;
		Scene* currentScene;
		Scene* previousScene;
		bool running;
};

#endif // GAME_H
