#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H

#include "Game.h"
#include "Font.h"

class DebugScene : public Scene
{
	public:
		DebugScene();
		~DebugScene();
		void Draw(SDL_Surface *Dest);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
		inline void Print(std::string txt);
		std::vector<std::string> backlog;
	private:
		SDL_Surface * rect;
		Font MainFont;
		bool _connected;
		
};

#endif
