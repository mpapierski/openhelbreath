#include "TextEdit.h"

TextEdit::TextEdit()
{
	WidgetFont.LoadFont("font/VeraSe.ttf", 12);

	SetMaxLength(255);

	SetPasswordMode(false);

	CursorVisible = true;

	CursorSurface = Font::Draw(WidgetFont, "_");

	CursorPosition = 0;

	Blink = 0;
}

TextEdit::TextEdit(const std::string &Text)
{
	WidgetFont.LoadFont("font/VersSe.ttf", 12);

	SetMaxLength(255);

	SetPasswordMode(false);

	CursorVisible = true;

	CursorSurface = Font::Draw(WidgetFont, "_");

	CursorPosition = 0;

	SetText(Text);

	Blink = 0;

}


void TextEdit::Draw(SDL_Surface *Dest)
{
	Surface::Draw(Dest, GetSurface(), this->X(), this->Y());

	if(CursorVisible)
	{
		Blink++;
		if (Blink >= 50)
		{
			Surface::Draw(Dest, CursorSurface, (this->X() + CursorPosition), this->Y());
		}
		if (Blink > 100)
		{
			Blink = 0;
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
	if(Sym == SDLK_BACKSPACE)
	{
		if(WidgetText.size())
			WidgetText.erase((WidgetText.size() - 1), 1);
	}
	if(WidgetText.size() < MaxLength)
	{


		if(Sym > 31 && Sym < 127)
		{
			if(Mod == KMOD_LSHIFT || Mod == KMOD_RSHIFT)
			{
				if(Sym > 96 && Sym < 123)
					WidgetText.push_back(static_cast<char>(Sym-32));
			}
			else
				WidgetText.push_back(static_cast<char>(Sym));
		}
	}
	Update();
}

void TextEdit::SetColor(int R, int G, int B)
{
	WidgetFont.SetColor(R, G, B);

	Update();
}

void TextEdit::SetCursorVisible(bool Visible)
{
	if(Visible)
	{
		CursorVisible = true;
	}
	else
		CursorVisible = false;
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
	if(Visible)
	{
		PasswordMode = true;
	}
	else
		PasswordMode = false;
}

void TextEdit::SetText(const std::string &Text)
{
	WidgetText.append(Text);

	Update();
}

void TextEdit::Update()
{
	SDL_FreeSurface(GetSurface());

	if(PasswordMode)
	{
		std::string Temp;
		Temp.append(WidgetText.size() , '*');
		SetSurface(Font::Draw(WidgetFont, Temp));
	}
	else
		SetSurface(Font::Draw(WidgetFont, WidgetText));

	if(WidgetText.size())
	{
		CursorPosition = GetSurface()->w;
	}
	else
		CursorPosition = 0;
}

TextEdit::~TextEdit()
{
	SDL_FreeSurface(CursorSurface);
}
