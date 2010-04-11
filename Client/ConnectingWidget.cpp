#include "ConnectingWidget.h"
#include "Game.h"

ConnectingWidget::ConnectingWidget()
{
	SetSurface(Surface::CreateSurface(640, 480, 0, 0, 0, 128));
	Enabled = false;
	SetState(0);
}

void ConnectingWidget::Draw(SDL_Surface *Dest)
{
	if (!Enabled)
		return;
	Surface::Draw(Dest, GetSurface(), 0, 0);

	int X = 320 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
			INTERFACE_DIALOG_MESSAGEBOX).w / 2);
	int Y = 240 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
			INTERFACE_DIALOG_MESSAGEBOX).h / 2);

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3], X, Y,
			INTERFACE_DIALOG_MESSAGEBOX);

	char Descr[100];
	switch (State)
	{
		case 0:
			sprintf(Descr, "Connecting to server... %dsec.",
					MessageTimer.GetTicks() / 1000);
			Font::PutSprText(Dest, 172 + 35, 190, Descr);
			break;
		case 1:
			sprintf(Descr, "Waiting for response... %dsec.",
					MessageTimer.GetTicks() / 1000);
			Font::PutSprText(Dest, 172 + 44, 190, Descr);
			break;
	}

	if (MessageTimer.GetTicks() > 7000)
	{
		Font::PutAlignedText(Dest, 180, 225, 283,
				"Press ESC key during long time of no", 0, 0, 0);
		Font::PutAlignedText(Dest, 180, 240, 283,
				"connection and return to the main menu.", 0, 0, 0);
	}
	else
		Font::PutAlignedText(Dest, 180, 225, 283,
				"Connecting to server. Please wait...", 0, 0, 0);
}

void ConnectingWidget::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{

}

void ConnectingWidget::SetEnabled(bool Enable)
{
	Enabled = Enable;

	if (Enabled)
	{
		MessageTimer.Start();
	}
}

void ConnectingWidget::SetState(int State)
{
	this->State = State;
	MessageTimer.Start();
}

int ConnectingWidget::GetState() const
{
	return this->State;
}

inline bool ConnectingWidget::IsEnabled() const
{
	return Enabled;
}

ConnectingWidget::~ConnectingWidget()
{

}



