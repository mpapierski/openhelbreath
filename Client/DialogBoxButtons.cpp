#include "Game.h"
#include "DialogBoxButtons.h"

DialogBoxButtons::DialogBoxButtons()
{
	SetSurface(Surface::CreateSurface(640, 480, 0, 0, 0, 128));
	Enabled = false;
	Focus = 0;
	_X = 320 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
			INTERFACE_DIALOG_MESSAGEBOX).w / 2);
	_Y = 240 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
			INTERFACE_DIALOG_MESSAGEBOX).h / 2);
	Focus = -1;
}

DialogBoxButtons::~DialogBoxButtons()
{

}

void DialogBoxButtons::Draw(SDL_Surface *Dest)
{
	if (!Enabled)
		return;

	Surface::Draw(Dest, GetSurface(), 0, 0);

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3], _X, _Y,
			INTERFACE_DIALOG_MESSAGEBOX);

	if (RightButton > -1)
		Sprite::Draw(Dest,
				Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS],
				_X + 210, _Y + 120, RightButton + (Focus == 0 ? 1 : 0));

	if (LeftButton > -1)
		Sprite::Draw(Dest,
				Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], _X + 40,
				_Y + 120, LeftButton + (Focus == 1 ? 1 : 0));

	if (Title != "")
		Font::PutAlignedSprText(Dest, _X, _Y + 40, 313, Title);
	for (unsigned int i = 0; i < Text.size(); i++)
	{
		Font::PutAlignedText(Dest, _X, _Y + 70 + (i * 15), 313, Text[i], 0, 0, 0);
	}
}

void DialogBoxButtons::OnLButtonDown(int X, int Y)
{
	if (Focus == -1)
		return;

	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = Focus == 1 ? SDL_CLICKED_LEFT : SDL_CLICKED_RIGHT;
	Ev.user.data1 = Ev.user.data2 = 0;
	SDL_PushEvent(&Ev);
}

void DialogBoxButtons::SetEnabled(bool Enable)
{
	Enabled = Enable;
}

void DialogBoxButtons::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE || Sym == SDLK_RETURN)
	{
		SDL_Event Ev;
		Ev.type = SDL_USEREVENT;
		Ev.user.code = SDL_CLICKED_RIGHT;
		Ev.user.data1 = Ev.user.data2 = 0;
		SDL_PushEvent(&Ev);
	}
}

bool DialogBoxButtons::IsEnabled() const
{
	return this->Enabled;
}

void DialogBoxButtons::SetMode(int LeftButton, int RightButton)
{
	this->LeftButton = LeftButton;
	this->RightButton = RightButton;
}

void DialogBoxButtons::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left,
		bool Right, bool Middle)
{
	Focus = -1;
	if (Y > _Y + 120 && Y < _Y + 120 + 25)
	{
		if (X > _X + 40 && X < _X + 40 + 75)
			Focus = 1;
		if (X > _X + 210 && X < _X + 210 + 75)
			Focus = 0;
	}
}

void DialogBoxButtons::ClearText()
{
	Text.clear();
}

void DialogBoxButtons::SetTitle(std::string NewTitle)
{
	Title = NewTitle;
}

void DialogBoxButtons::AddText(std::string Txt)
{
	Text.push_back(Txt);
}

