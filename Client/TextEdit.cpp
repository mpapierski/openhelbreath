#include "TextEdit.h"
#include "Game.h"

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

	CursorPosition = 0;

	CursorShadow = Font::Text(Game::GetInstance().Font, "_", 0, 0, 0);

	CursorSurface = Font::Text(Game::GetInstance().Font, "_", 255, 255, 255);

	TextShadow = NULL;

	Blink = 0;
}


void TextEdit::Draw(SDL_Surface *Dest)
{
	if(Enabled)
	{
		Surface::Draw(Dest, TextShadow, this->X()+1, this->Y()+1);
	}
	Surface::Draw(Dest, GetSurface(), this->X(), this->Y());

	if(CursorVisible)
	{
		Blink++;
		if (Blink >= 50)
		{
			Surface::Draw(Dest, CursorShadow, (this->X() + CursorPosition)+1, this->Y()+1);
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

void TextEdit::SetEnabled(bool Enable)
{
	Enabled = Enable;

	if(Enabled)
	{
		CursorVisible = true;
	}
	else
		CursorVisible = false;

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
	if(Visible)
	{
		PasswordMode = true;
	}
	else
		PasswordMode = false;
}

void TextEdit::SetText(const std::string &Text)
{
	WidgetText.assign(Text);

	Update();
}

void TextEdit::Update()
{
	SDL_FreeSurface(GetSurface());

	if(PasswordMode)
	{
		std::string Temp;
		Temp.append(WidgetText.size() , '*');

		if(!Enabled)
		{
			SetSurface(Font::Text(Game::GetInstance().Font, Temp, 102, 102, 102));
		}
		else
		{
			TextShadow = Font::Text(Game::GetInstance().Font, Temp, 0, 0, 0);
			SetSurface(Font::Text(Game::GetInstance().Font, Temp, 255, 255, 255));
		}
	}
	else
	{
		if(!Enabled)
		{
			SetSurface(Font::Text(Game::GetInstance().Font, WidgetText, 102, 102, 102));
		}
		else
		{
			TextShadow = Font::Text(Game::GetInstance().Font, WidgetText, 0, 0, 0);
			SetSurface(Font::Text(Game::GetInstance().Font, WidgetText, 255, 255, 255));
		}
	}

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

	SDL_FreeSurface(CursorShadow);

	SDL_FreeSurface(TextShadow);
}
