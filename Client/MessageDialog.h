#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "Widget.h"
#include "Font.h"

namespace gui
{

	class MessageDialog : public gui::Widget
	{
		public:
			enum ButtonsMode
			{
				NONE, OK, YES, NO, CANCEL
			};

			MessageDialog();
			MessageDialog(const std::string& title, const std::string& message, ButtonsMode buttons = NONE);
			virtual ~MessageDialog();
			void draw(SDL_Surface* dest);
			void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
			void onLButtonDown(int x, int y);
			void setTitle(const std::string& title);
			void setMessage(const std::string& message);
			void setButtons(ButtonsMode buttons);

		private:
			std::string title;
			std::string message;
			ButtonsMode buttons;
			ButtonsMode buttonsFocus;
	};

} // namespace gui

#endif // MESSAGEDIALOG_H
