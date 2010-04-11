#include "Game.h"

SelectCharScene::SelectCharScene()
{
	SlotSelect = 0;
}

void SelectCharScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_8], 0, 0, 0);

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS],
			230, 7, INTERFACE_BUTTON_CHARLIST);

	switch (SlotSelect)
	{
		case 0:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 103,
					54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 1:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 212,
					54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 2:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 321,
					54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 3:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 430,
					54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
	}

	switch (ButtonFocus)
	{
		case Start:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364,
					288, INTERFACE_BUTTON_START);
			break;
		case CreateNewChar:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364,
					318, INTERFACE_BUTTON_CREATENEWCHAR);
			break;
		case DelChar:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364,
					348, INTERFACE_BUTTON_DELCHAR);
			break;
		case ChangePasswd:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364,
					378, INTERFACE_BUTTON_CHANGEPASSWD);
			break;
		case Logout:
			Sprite::Draw(Dest,
					Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364,
					408, INTERFACE_BUTTON_LOGOUTBIG);
			break;
		default:
			;
	}
}

void SelectCharScene::OnMouseMove(
		int X,
		int Y,
		int RelX,
		int RelY,
		bool Left,
		bool Right,
		bool Middle)
{
	if ((X > 363 && X < 540) && (Y > 287 && Y < 312))
		ButtonFocus = Start;
	if ((X > 363 && X < 540) && (Y > 317 && Y < 342))
		ButtonFocus = CreateNewChar;
	if ((X > 363 && X < 540) && (Y > 347 && Y < 372))
		ButtonFocus = DelChar;
	if ((X > 363 && X < 540) && (Y > 377 && Y < 402))
		ButtonFocus = ChangePasswd;
	if ((X > 363 && X < 540) && (Y > 407 && Y < 432))
		ButtonFocus = Logout;
}

void SelectCharScene::OnLButtonDown(int X, int Y)
{
	if ((X > 103 && X < 210) && (Y > 54 && Y < 240))
		SlotSelect = 0;
	if ((X > 211 && X < 319) && (Y > 54 && Y < 240))
		SlotSelect = 1;
	if ((X > 321 && X < 427) && (Y > 54 && Y < 240))
		SlotSelect = 2;
	if ((X > 430 && X < 536) && (Y > 54 && Y < 240))
		SlotSelect = 3;
}

void SelectCharScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	if (Sym == SDLK_ESCAPE)
	{
		Game::GetInstance().ChangeScene(new MenuScene);
	}
}

SelectCharScene::~SelectCharScene()
{

}
