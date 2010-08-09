#include "TextEdit.h"
#include "SpriteBank.h"

namespace gui
{

	TextEdit::TextEdit()
	{
		create();
	}

	TextEdit::TextEdit(const std::string& text)
	{
		create();
		setText(text);
	}

	TextEdit::~TextEdit()
	{
		SDL_FreeSurface(cursorSurface);
	}

	void TextEdit::create()
	{
		maxLength = 255;
		setEnabled(true);
		passwordMode = false;
		cursorVisible = true;
		cursorPosition = cursorPositionX = 0;
		cursorSurface = Font::textShaded("_", Font::NORMAL, 255, 255, 255);
		blinkTimer.start();
	}

	void TextEdit::draw(SDL_Surface* dest)
	{
		Surface::draw(dest, getSurface(), this->x(), this->y());
		if (cursorVisible)
		{
			if (blinkTimer.getTicks() > 500)
			{
				Surface::draw(dest, cursorSurface,
						(this->x() + cursorPositionX), this->y());

				if (blinkTimer.getTicks() > 1000)
					blinkTimer.start();
			}
		}
	}

	void TextEdit::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
	{
		switch (sym)
		{
			case SDLK_BACKSPACE:
				if (!widgetText.empty() && cursorPosition > 0)
				{
					widgetText.erase(--cursorPosition, 1);
				}
				break;
			case SDLK_DELETE:
				if (!widgetText.empty() && cursorPosition
						!= (int) widgetText.length())
					widgetText.erase(cursorPosition, 1);
				break;
			case SDLK_LEFT:
				cursorPosition = std::max(cursorPosition - 1, 0);
				break;
			case SDLK_RIGHT:
				cursorPosition = (cursorPosition + 1
						> (int) widgetText.length()) ? widgetText.length()
						: cursorPosition + 1;
				break;
			case SDLK_END:
				cursorPosition = (int) widgetText.length();
				break;
			case SDLK_HOME:
				cursorPosition = 0;
				break;

			default:
			{
				if (sym < 32 || widgetText.length() >= maxLength)
					return;
				const int INTERNATIONAL_MASK = 0xFF80, UNICODE_MASK = 0x7F;
				if (unicode == 0)
					return;
				else if ((unicode & INTERNATIONAL_MASK) == 0)
				{
					char Key = static_cast<char> (unicode & UNICODE_MASK);
					widgetText.insert(cursorPosition, 1, Key);
					cursorPosition = cursorPosition + 1
							> (int) widgetText.length() ? widgetText.length()
							: cursorPosition + 1;
				}
				else
					return;
			}
				break;
		}
		update();
	}

	void TextEdit::setText(const std::string& text)
	{
		widgetText.assign(text);
		update();
	}

	const std::string& TextEdit::getText()
	{
		return widgetText;
	}

	void TextEdit::setEnabled(bool enabled)
	{
		Widget::setEnabled(enabled);
		cursorVisible = enabled;
		update();
	}

	void TextEdit::setCursorVisible(bool visible)
	{
		cursorVisible = visible;
		update();
	}

	void TextEdit::setCursorPosition(int position)
	{
		cursorPosition = position;
	}

	void TextEdit::setMaxLength(int length)
	{
		maxLength = length;
	}

	void TextEdit::setPasswordMode(bool visible)
	{
		passwordMode = visible;
	}

	void TextEdit::clear()
	{
		widgetText.clear();
		cursorPosition = 0;
		update();
	}

	void TextEdit::update()
	{
		SDL_FreeSurface(getSurface());
		std::string temp;
		if (passwordMode)
			temp.append(widgetText.size(), '*');
		else
			temp = widgetText;

		if (!isEnabled())
			setSurface(Font::textShaded(temp, Font::NORMAL, 160, 160, 160));
		else
			setSurface(Font::textShaded(temp, Font::NORMAL, 255, 255, 255));

		cursorPositionX = cursorPosition > 0 ? Font::textWidth(temp.substr(0, cursorPosition), Font::NORMAL) : 0;
	}

} //namespace gui
