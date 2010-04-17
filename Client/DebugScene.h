#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H

#include "Font.h"

#include "Socket.h"

class DebugScene: public Scene
{
	public:
		DebugScene();
		~DebugScene();

		void Draw(SDL_Surface *Dest);

		void OnEvent(SDL_Event *EventSource);

		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

		inline void Print(std::string txt);

		std::vector<std::string> backlog;

	private:
		SDL_Surface *rect;

		SDL_Surface *TextSurface;

		int state;

		bool _connected;

		Socket * MLSocket;
};

#endif
