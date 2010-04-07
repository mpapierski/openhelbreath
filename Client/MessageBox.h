#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <sstream>

#include "Widget.h"
#include "Font.h"
#include "Timer.h"

class MessageBox: public Widget
{
	public:
		MessageBox();
		~MessageBox();

		void Draw(SDL_Surface *Dest);

		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

		void SetEnabled(bool Enable);

	private:
		Timer MessageTimer;

		bool Enabled;
};

#endif // MESSAGEBOX_H
