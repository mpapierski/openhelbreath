#include "MessageBox.h"
#include "Game.h"

MessageBox::MessageBox()
{
	SetSurface(Surface::CreateSurface(640, 480, 0, 0, 0, 128));

	Enabled = false;
}

void MessageBox::Draw(SDL_Surface *Dest)
{
	if (Enabled)
	{
		Surface::Draw(Dest, GetSurface(), 0, 0);

		int X = 320 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
						INTERFACE_DIALOG_MESSAGEBOX).w / 2);
		int Y = 240 - (Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3].GetFrame(
						INTERFACE_DIALOG_MESSAGEBOX).h / 2);

		Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3], X,
				Y, INTERFACE_DIALOG_MESSAGEBOX);

		std::stringstream TimeLabel;
		TimeLabel << "Connecting to Server... " << (MessageTimer.GetTicks()
				/ 1000) << " Sec.";

		Font::PutSprText(Dest, 207, 190, TimeLabel.str());

		if (MessageTimer.GetTicks() > 7000)
		{
			Font::PutText(Dest, 205, 225,
					"Press ESC key during long time of no", 0, 0, 0);
			Font::PutText(Dest, 195, 240,
					"connection and return to the main menu.", 0, 0, 0);
		}
		else
			Font::PutText(Dest, 205, 225,
					"Connecting to server. Please wait...", 0, 0, 0);

	}
}

void MessageBox::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{

}

void MessageBox::SetEnabled(bool Enable)
{
	Enabled = Enable;

	if (Enabled)
	{
		MessageTimer.Start();
	}
}

MessageBox::~MessageBox()
{

}
