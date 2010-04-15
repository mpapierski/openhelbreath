#ifndef DIALOGBOXBUTTONS_H_
#define DIALOGBOXBUTTONS_H_

#include "SpriteID.h"
#include "GlobalDef.h"
#include "Widget.h"
#include "Font.h"

class DialogBoxButtons: public Widget
{
	private:
		int _X, _Y;
		bool Enabled;
		int LeftButton;
		int RightButton;
		int Focus;
		std::string Title;
		std::vector<std::string> Text;
	public:
		DialogBoxButtons();
		virtual ~DialogBoxButtons();
		void Draw(SDL_Surface *Dest);
		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);
		void OnLButtonDown(int X, int Y);
		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
		void SetEnabled(bool Enable);
		bool IsEnabled() const;
		void SetMode(int LeftButton, int RightButton);
		void SetTitle(const std::string &NewTitle);
		void ClearText();
		void AddText(const std::string &Txt);
};

#endif /* DIALOGBOXBUTTONS_H_ */
