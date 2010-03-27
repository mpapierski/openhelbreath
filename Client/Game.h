#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Sprite.h"
#include "SpriteID.h"
#include "Mouse.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "ExitScene.h"
#include "LoginScene.h"
#include "SelectServerScene.h"

class Game : public Event
{
public:
	static Game &GetInstance()
	{
		static Game Instance;
		return Instance;
	}

	int OnExecute();

	bool OnInitialize();

	void OnLoop();

	void OnDraw();

	void OnEvent(SDL_Event *EventSource);

	void OnExit();

	void OnCleanup();

	void ChangeScene(Scene *NewScene);

	std::vector<Sprite> Sprites;

private:
	Game();
	Game(const Game &);
	Game& operator = (const Game&);

	Window MainWindow;

	Mouse MouseCursor;

	Scene *CurrentScene;

	bool Running;
};

#endif // GAME_H
