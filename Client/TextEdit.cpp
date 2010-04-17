#include "TextEdit.h"
#include "Game.h"

namespace gui
{

	TextEdit::TextEdit()
	{
		Create();
	}

	TextEdit::TextEdit(const std::string &Text)
	{
		Create();
		SetText(Text);
	}

	void TextEdit::Create()
	{
		MaxLength = 255;
		Enabled = true;
		PasswordMode = false;
		CursorVisible = true;
		CursorPosition = CursorPositionX = 0;
		CursorSurface = Font::TextShaded("_", 255, 255, 255);
		BlinkTimer.Start();
	}

	void TextEdit::Draw(SDL_Surface *Dest)
	{
		Surface::Draw(Dest, GetSurface(), this->X(), this->Y());
		if (CursorVisible)
		{
			if (BlinkTimer.GetTicks() > 500)
			{
				Surface::Draw(Dest, CursorSurface, (this->X() + CursorPositionX), this->Y());

				if (BlinkTimer.GetTicks() > 1000)
					BlinkTimer.Start();
			}
		}
	}

	const std::string &TextEdit::GetText()
	{
		return WidgetText;
	}

	void TextEdit::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
	{

	}

	void TextEdit::OnLButtonDown(int X, int Y)
	{

	}

	void TextEdit::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
	{
		switch (Sym)
		{
			case SDLK_BACKSPACE:
				if (!WidgetText.empty() && CursorPosition > 0)
					WidgetText.erase(--CursorPosition, 1);
				break;
			case SDLK_DELETE:
				if (!WidgetText.empty() && CursorPosition != (int) WidgetText.length())
					WidgetText.erase(CursorPosition, 1);
				break;
			case SDLK_LEFT:
				CursorPosition = max(CursorPosition - 1, 0);
				break;
			case SDLK_RIGHT:
				CursorPosition = (CursorPosition + 1 > (int) WidgetText.length()) ? WidgetText.length() : CursorPosition + 1;
				break;
			case SDLK_END:
				CursorPosition = (int) WidgetText.length();
				break;
			case SDLK_HOME:
				CursorPosition = 0;
				break;

			default:
			{
				if (Sym < 32 || WidgetText.length() >= MaxLength)
					return;
				const int INTERNATIONAL_MASK = 0xFF80, UNICODE_MASK = 0x7F;
				if (Unicode == 0)
					return;
				else if ((Unicode & INTERNATIONAL_MASK) == 0)
				{
					char Key = static_cast<char> (Unicode & UNICODE_MASK);
					WidgetText = WidgetText.substr(0, CursorPosition) + Key + WidgetText.substr(CursorPosition, WidgetText.length() - CursorPosition);
					CursorPosition = CursorPosition + 1 > (int) WidgetText.length() ? WidgetText.length() : CursorPosition + 1;
				}
				else
					return;
			}
				break;
		}
		Update();
	}

	void TextEdit::SetEnabled(bool Enable)
	{
		Enabled = Enable;
		CursorVisible = Enabled;
		Update();
	}

	void TextEdit::SetCursorVisible(bool Visible)
	{
		CursorVisible = Visible;
		Update();
	}

	void TextEdit::SetCursorPosition(int Position)
	{
		CursorPosition = Position;
	}

	void TextEdit::SetMaxLength(int Length)
	{
		MaxLength = Length;
	}

	void TextEdit::SetPasswordMode(bool Visible)
	{
		PasswordMode = Visible;
	}

	void TextEdit::SetText(const std::string &Text)
	{
		WidgetText.assign(Text);
		Update();
	}

	void TextEdit::Update()
	{
		SDL_FreeSurface(GetSurface());
		std::string Temp;
		if (PasswordMode)
			Temp.append(WidgetText.size(), '*');
		else
			Temp.assign(WidgetText);

		if (!Enabled)
			SetSurface(Font::Text(Temp, 102, 102, 102));
		else
			SetSurface(Font::TextShaded(Temp, 255, 255, 255));

		CursorPositionX = CursorPosition > 0 ? Font::TextWidth(Temp.substr(0, CursorPosition)) : 0;
	}

	TextEdit::~TextEdit()
	{
		SDL_FreeSurface(CursorSurface);
	}

} //namespace gui
