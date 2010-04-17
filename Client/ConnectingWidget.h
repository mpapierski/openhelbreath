#ifndef CONNECTINGWIDGET_H
#define CONNECTINGWIDGET_H

#include "Widget.h"
#include "Font.h"
#include "Timer.h"

class ConnectingWidget: public gui::Widget
{
	public:
		ConnectingWidget();
		~ConnectingWidget();

		void Draw(SDL_Surface *Dest);

		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

		void SetEnabled(bool Enable);

		void SetState(int State);

		int GetState() const;

		bool IsEnabled() const;

	private:
		Timer MessageTimer;

		bool Enabled;

		int State;
};

#endif // CONNECTINGWIDGET_H
