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

	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		Font::PutTextShaded(Dest, Form[i].Input.X() - Font::TextWidth(Form[i].Label)
				- 6, Form[i].Input.Y(), Form[i].Label, 255, 255, 255);
				
		Form[i].Input.Draw(Dest);
	}

	if (FormFocus < DEF_INPUTTOTAL)
	{
		for (int i = 0; i < 3; i++)
			Font::PutAlignedText(Dest, 290, 330 + (15 * i), 285, Form[FormFocus].Info[i], 255, 255, 255);
	}
	else
	{
		switch (FormFocus)
		{
			case 6:
				Font::PutAlignedText(Dest, 290, 330, 285, "Create an account with your input.", 255, 255, 255);
				break;
			case 7:
				Font::PutAlignedText(Dest, 290, 330, 285, "Clear all.", 255,255, 255);
				break;
			case 8:
				Font::PutAlignedText(Dest, 290, 330, 285, "Back to main menu.", 255, 255, 255);
				break;
		}
	}

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			199 + 98, 398, FormFocus == 6 ? INTERFACE_BUTTON_CREATE + 1 : INTERFACE_BUTTON_CREATE);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			294 + 98, 398, FormFocus == 7 ? INTERFACE_BUTTON_RESET + 1 : INTERFACE_BUTTON_RESET);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTON],
			390 + 98, 398, FormFocus == 8 ? INTERFACE_BUTTON_CANCEL + 1 : INTERFACE_BUTTON_CANCEL);
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

	if (Sym == SDLK_TAB || Sym == SDLK_DOWN)
		SetFocus((FormFocus + 1) % (DEF_INPUTTOTAL + 3));

	if(Sym == SDLK_UP)
		SetFocus((FormFocus - 1) % (DEF_INPUTTOTAL + 3));
}

void SignupScene::_Cancel()
{
	Game::GetInstance().Audio->Play("E14");
	Game::GetInstance().ChangeScene(new MenuScene);
}

void SignupScene::_Ok()
{
	Game::GetInstance().Audio->Play("E14");
}

void SignupScene::_Reset()
{
	Game::GetInstance().Audio->Play("E14");
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
		Form[i].Input.SetText("");
}
