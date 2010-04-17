#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "Widget.h"
#include "Font.h"
#include "Timer.h"

namespace gui
{

	class TextEdit: public Widget
	{
		public:
			TextEdit();
			~TextEdit();
			TextEdit(const std::string &Text);
			void Draw(SDL_Surface *Dest);
			void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);
			void OnLButtonDown(int X, int Y);
			void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
			const std::string &GetText();
			void SetEnabled(bool Enable);
			void SetCursorVisible(bool Visible);
			void SetCursorPosition(int Position);
			void SetMaxLength(int Length);
			void SetPasswordMode(bool Visible);
			void SetText(const std::string &Text);
			void Update();

		private:
			void Create();

			SDL_Surface *CursorSurface;
			std::string WidgetText;
			bool Enabled;
			bool PasswordMode;
			bool CursorVisible;
			int CursorPosition;
			int CursorPositionX;
			unsigned int MaxLength;
			Timer BlinkTimer;
	};

} //namespace gui

#endif // TEXTEDIT_H
