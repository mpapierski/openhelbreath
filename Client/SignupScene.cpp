#include "Game.h"

SignupScene::SignupScene()
{
	struct form
	{
			std::string label;
			int x, y;
			int max_len;
			bool password;
			std::string info[3];
	} _descr[DEF_INPUTTOTAL] =
	{
	{ "Login:", 427, 84, 11, false,
	{
			"Enter your account ID.",
			"( Only letters and numbers )",
			"and numbers, no special keywords." } },
	{ "Password:", 427, 106, 11, true,
	{ "Enter your account password.", "", "" } },
	{ "Confirm:", 427, 129, 11, true,
	{ "Confirm the password.", "", "" } },
	{ "E-mail:", 311, 215, 31, false,
	{
			"Enter your E-mail address.",
			"You should enter a correct E-mail address",
			"to confirm the account owner." } },
	{ "Quiz:", 311, 253, 44, false,
	{
			"Enter the secret question, so you can",
			"recover the password if you forget it.",
			"" } },
	{ "Answer:", 311, 291, 19, false,
	{ "Answer the question.", "", "" } } };

	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		Form[i].Label = _descr[i].label;
		Form[i].Input.SetMaxLength(_descr[i].max_len);
		Form[i].Input.SetPosition(_descr[i].x, _descr[i].y);
		Form[i].Input.SetPasswordMode(_descr[i].password);
		for (int j = 0; j < 3; j++)
			Form[i].Info[j] = _descr[i].info[j];
	}

	SetFocus(0);
}

void SignupScene::SetFocus(int NewId)
{
	if (NewId < 0)
		return;

	FormFocus = NewId;

	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		Form[i].Input.SetEnabled(false);
	}
	if (NewId >= DEF_INPUTTOTAL)
		return;
	Form[NewId].Input.SetEnabled(true);
}

SignupScene::~SignupScene()
{

}

void SignupScene::Draw(SDL_Surface * Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_LOGIN], 0, 0,
				SPRID_LOGIN_BACKGROUND);

	SDL_Surface *temp;

	for(int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		temp = Font::Text(Game::GetInstance().Font, Form[i].Label, 255, 255, 255);
		Surface::Draw(Dest, temp, Form[i].Input.X() - temp->w - 6, Form[i].Input.Y());
		SDL_FreeSurface(temp);

		Form[i].Input.Draw(Dest);
	}

	if (FormFocus < DEF_INPUTTOTAL)
	{
		for (int i = 0; i < 3; i++)
		{
			temp = Font::Text(Game::GetInstance().Font, Form[FormFocus].Info[i], 255, 255, 255);
			Surface::Draw(Dest, temp, 290, 330 + (15 * i));
			SDL_FreeSurface(temp);
		}
	}
	else
	{
		switch (FormFocus)
		{
			case 6:
				temp = Font::Text(Game::GetInstance().Font,
						"Create an account with your input.", 255, 255, 255);
				Surface::Draw(Dest, temp, 290, 330);
				SDL_FreeSurface(temp);
				break;
			case 7:
				temp = Font::Text(Game::GetInstance().Font, "Clear all.", 255, 255, 255);
				Surface::Draw(Dest, temp, 290, 330);
				SDL_FreeSurface(temp);
				break;
			case 8:
				temp = Font::Text(Game::GetInstance().Font, "Back to main menu.", 255, 255, 255);
				Surface::Draw(Dest, temp, 290, 330);
				SDL_FreeSurface(temp);
				break;
		}
	}

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			199 + 98, 398, FormFocus == 6 ? BUTTON_CREATE + 1 : BUTTON_CREATE);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			294 + 98, 398, FormFocus == 7 ? BUTTON_RESET + 1 : BUTTON_RESET);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			390 + 98, 398, FormFocus == 8 ? BUTTON_CANCEL + 1 : BUTTON_CANCEL);
}

void SignupScene::OnEvent(SDL_Event * EventSource)
{
	Event::OnEvent(EventSource);
	if (FormFocus < DEF_INPUTTOTAL)
		Form[FormFocus].Input.OnEvent(EventSource);
}

void SignupScene::OnMouseMove(
		int X,
		int Y,
		int RelX,
		int RelY,
		bool Left,
		bool Right,
		bool Middle)
{
	if ((X >= 297) && (X <= 370) && (Y >= 396) && (Y <= 417))
		SetFocus(6);
	if ((X >= 392) && (X <= 465) && (Y >= 396) && (Y <= 417))
		SetFocus(7);
	if ((X >= 488) && (X <= 561) && (Y >= 396) && (Y <= 417))
		SetFocus(8);
}

void SignupScene::OnLButtonDown(int X, int Y)
{
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		const TextEdit & _ctrl = Form[i].Input;
		if (X >= _ctrl.X() && X <= 640 && Y >= _ctrl.Y() && Y <= _ctrl.Y() + 20)
		{
			SetFocus(i);
			break;
		}
	}
	if ((X >= 297) && (X <= 370) && (Y >= 396) && (Y <= 417))
		_Ok();
	if ((X >= 392) && (X <= 465) && (Y >= 396) && (Y <= 417))
		_Reset();
	if ((X >= 488) && (X <= 561) && (Y >= 396) && (Y <= 417))
		_Cancel();
}

void SignupScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_RETURN)
	{
		if (FormFocus < DEF_INPUTTOTAL)
			SetFocus(FormFocus + 1);
		else
			switch (FormFocus)
			{
				case 6:
					_Ok();
					break;
				case 7:
					_Reset();
					break;
				case 8:
					_Cancel();
					break;
			}
	}
	if (Sym == SDLK_ESCAPE)
		_Cancel();
	if (Sym == SDLK_TAB)
		SetFocus((FormFocus + 1) % (DEF_INPUTTOTAL + 3));
}

void SignupScene::_Cancel()
{
	Game::GetInstance().ChangeScene(new MenuScene);
}

void SignupScene::_Ok()
{
	//
}

void SignupScene::_Reset()
{
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
		Form[i].Input.SetText("");
}
