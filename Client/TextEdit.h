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
			TextEdit(const std::string& text);
			void draw(SDL_Surface* dest);
			void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
			void setEnabled(bool enabled);
			void setText(const std::string& text);
			const std::string& getText();
			void setCursorVisible(bool visible);
			void setCursorPosition(int position);
			void setMaxLength(int length);
			void setPasswordMode(bool visible);
			void clear();
			void update();

		private:
			void create();

			SDL_Surface* cursorSurface;
			std::string widgetText;
			bool passwordMode;
			bool cursorVisible;
			int cursorPosition;
			int cursorPositionX;
			unsigned int maxLength;
			Timer blinkTimer;
	};

} // namespace gui

#endif // TEXTEDIT_H
