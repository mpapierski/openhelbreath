#include "MessageDialog.h"
#include "SpriteBank.h"
#include "SoundBank.h"

namespace gui
{

	MessageDialog::MessageDialog()
	{
		buttonsFocus = NONE;
	}

	MessageDialog::MessageDialog(const std::string& title, const std::string& message, ButtonsMode buttons)
	{
		this->title = title;
		this->message = message;
		this->buttons = buttons;
		buttonsFocus = NONE;
	}

	MessageDialog::~MessageDialog()
	{

	}

	void MessageDialog::draw(SDL_Surface* dest)
	{
		if (isVisible())
		{

			SpriteBank::manager.draw(dest, x(), y(), SPRID_GAMEDIALOG_3,
					INTERFACE_DIALOG_MESSAGEBOX);

			if (!title.empty())
				Font::putAlignedSprText(dest, x(), y() + 20, 315, title);

			if (!message.empty())
			{
				int prevNewLineCharPos;
				int nextNewLineCharPos;

				prevNewLineCharPos = message.find('\n', 0);

				if (prevNewLineCharPos > 0)
				{
					Font::putAlignedText(dest, x(), y() + 60, 315,
							message.substr(0, prevNewLineCharPos), Font::NORMAL, 0, 0, 0);

					int i = 1;
					do
					{
						nextNewLineCharPos = message.find('\n', (prevNewLineCharPos + 1));
						if (nextNewLineCharPos > prevNewLineCharPos)
						{
							Font::putAlignedText(dest, x(), (y() + 60 + (i * 14)), 315, message.substr(
									(prevNewLineCharPos + 1), (nextNewLineCharPos
											- prevNewLineCharPos - 1)), Font::NORMAL, 0, 0, 0);
						}
						else
							Font::putAlignedText(dest, x(), (y() + 60 + (i * 14)), 315, message.substr(
									(prevNewLineCharPos + 1), (message.size() - 1)), Font::NORMAL, 0, 0, 0);

						prevNewLineCharPos = nextNewLineCharPos;
						i++;
					} while (nextNewLineCharPos != -1);
				}
				else
					Font::putAlignedText(dest, x(), y() + 60, 315, message, Font::NORMAL, 0, 0, 0);
			}

			if (buttons == OK)
			{
				if (buttonsFocus == OK)
					SpriteBank::manager.draw(dest, x() + 120, y() + 125, SPRID_DIALOGTEXT_BUTTONS,
							1);
				else
					SpriteBank::manager.draw(dest, x() + 120, y() + 125, SPRID_DIALOGTEXT_BUTTONS,
							0);
			}
		}
	}

	void MessageDialog::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
	{
		if ((x > (this->x() + 120) && x < (this->x() + 194)) && (y > (this->y() + 125) && y
				< (this->y() + 145)))
			buttonsFocus = OK;
		else
			buttonsFocus = NONE;
	}

	void MessageDialog::onLButtonDown(int x, int y)
	{
		if ((x > (this->x() + 120) && x < (this->x() + 194)) && (y > (this->y() + 125) && y
				< (this->y() + 145)))
		{
			SoundBank::manager.play("E14");
			setVisible(false);
			setEnabled(false);
		}
	}

	void MessageDialog::setTitle(const std::string& title)
	{
		this->title = title;
	}

	void MessageDialog::setMessage(const std::string& message)
	{
		this->message = message;
	}

	void MessageDialog::setButtons(ButtonsMode buttons)
	{
		this->buttons = buttons;
	}

}
