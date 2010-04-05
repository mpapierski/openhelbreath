#include "Game.h"

SignupScene::SignupScene()
{
	const std::string _descr[DEF_INPUTTOTAL] =
	{ "Login:", "Password:", "Confirm:", "E-mail:", "Quiz:", "Answer:" };
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		Form[i].Label = _descr[i];
		Form[i].Input.SetMaxLength(10);
		Form[i].Input.SetPosition(400, 85 + (25 * i));
	}
	SetFocus(0);
	MainFont.LoadFont("font/VeraSe.ttf", 12);
	MainFont.SetColor(255, 255, 255);
}

void SignupScene::SetFocus(int NewId)
{
	if (NewId < 0 && NewId > DEF_INPUTTOTAL)
		return;
	FormFocus = NewId;
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		Form[i].Input.SetColor(102, 102, 102);
		Form[i].Input.SetCursorVisible(false);
	}
	Form[NewId].Input.SetColor(255, 255, 255);
	Form[NewId].Input.SetCursorVisible(true);

}

SignupScene::~SignupScene()
{

}

void SignupScene::Draw(SDL_Surface * Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_EXIT], 0, 0,
			SPRID_EXIT_BACKGROUND);
	SDL_Surface * txt_surface;
	for (int i = 0; i < DEF_INPUTTOTAL; i++)
	{
		txt_surface = Font::Draw(MainFont, Form[i].Label);
		Surface::Draw(Dest, txt_surface,
				Form[i].Input.X() - txt_surface->w - 6, Form[i].Input.Y());
		Form[i].Input.Draw(Dest);
	}
}

void SignupScene::OnEvent(SDL_Event * EventSource)
{
	Event::OnEvent(EventSource);
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
}
void SignupScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
		_Cancel();
	if (Sym == SDLK_TAB)
		SetFocus((FormFocus + 1) % DEF_INPUTTOTAL);
}

void SignupScene::_Cancel()
{
	Game::GetInstance().ChangeScene(new MenuScene);
}

void SignupScene::_Ok()
{
	//
}

