#include "Game.h"

SelectCharScene::SelectCharScene(Buffer * P)
{
	SlotSelect = 0;
	UpdateCharList(P, 12); // Skip 12 bytes (Dates)
}

void SelectCharScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_8], 0, 0, 0);

	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 230, 7, INTERFACE_BUTTON_CHARLIST);

	switch (SlotSelect)
	{
		case 0:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 103, 54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 1:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 212, 54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 2:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 321, 54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 3:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 430, 54, INTERFACE_BUTTON_SLOTSELECTED);
			break;
	}

	switch (ButtonFocus)
	{
		case Start:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364, 288, INTERFACE_BUTTON_START);
			Font::PutAlignedText(Dest, 98, 305, 259, "Log in with the selected character.", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 320, 259, "You can log in by clicking the button", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 335, 259, "or pressing the enter after selecting", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 350, 259, "character.", 0, 0, 0);
			break;
		case CreateNewChar:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364, 318, INTERFACE_BUTTON_CREATENEWCHAR);
			Font::PutAlignedText(Dest, 98, 320, 259, "Make a new character.", 0, 0, 0);
			break;
		case DelChar:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364, 348, INTERFACE_BUTTON_DELCHAR);
			Font::PutAlignedText(Dest, 98, 290, 259, "Delete the selected character. Deleted", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 305, 259, "characters cannot be recovered. You", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 320, 259, "also cannot delete a character above", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 335, 259, "level 50. If you want to delete a ", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 350, 259, "character above level 50, please send", 0, 0, 0);
			Font::PutAlignedText(Dest, 98, 365, 259, "an e-mail to the game master.", 0, 0, 0);
			break;
		case ChangePasswd:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364, 378, INTERFACE_BUTTON_CHANGEPASSWD);
			Font::PutAlignedText(Dest, 98, 320, 259, "Change the account password.", 0, 0, 0);
			break;
		case Logout:
			Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_DIALOGTEXT_BUTTONS], 364, 408, INTERFACE_BUTTON_LOGOUTBIG);
			Font::PutAlignedText(Dest, 98, 320, 259, "Back to the main menu.", 0, 0, 0);
			break;
		default:
			;
	}
	for (int i = 0; i < CharCount; i++)
	{
		char Txt[11];
		memset(&Txt, 0, 11);
		memcpy(&Txt, &CharList[i].Name, 10);
		Font::PutText(Dest, 112 + i*109, 179, Txt, 51, 0, 51);
		memset(&Txt, 0, 11);
		sprintf(Txt, "%d", CharList[i].Level);
		Font::PutText(Dest, 138 + i*109, 195, Txt, 51, 0, 51);
		memset(&Txt, 0, 11);
		sprintf(Txt, "%d", CharList[i].Experience);
		Font::PutText(Dest, 138 + i*109, 210, Txt, 51, 0, 51);
	}

	if (strlen(CharList[SlotSelect].Name) > 0)
	{
		char LogOut[30];
		sprintf(LogOut, "Last Logout : %04d/%02d/%02d  %02d:%02d:%02d", CharList[SlotSelect].Year, CharList[SlotSelect].Month, CharList[SlotSelect].Day, CharList[SlotSelect].Hour, CharList[SlotSelect].Minute, CharList[SlotSelect].Second);
		Font::PutAlignedText(Dest, 98, 425, 357-98, LogOut, 0, 0, 0);
	}

	Font::PutAlignedText(Dest, 122, 456, 315-122, "Test Server", 0, 0, 0);
}

void SelectCharScene::OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
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
	if (Y > 54 && Y < 240)
	{
		if (X > 103 && X < 210)
		{
			Game::GetInstance().Audio->Play("E14");
			SlotSelect = 0;
		}
		if (X > 211 && X < 319)
		{
			Game::GetInstance().Audio->Play("E14");
			SlotSelect = 1;
		}
		if (X > 321 && X < 427)
		{
			Game::GetInstance().Audio->Play("E14");
			SlotSelect = 2;
		}
		if (X > 430 && X < 536)
		{
			Game::GetInstance().Audio->Play("E14");
			SlotSelect = 3;
		}
	}

	if ((X > 363 && X < 540) && (Y > 407 && Y < 432))
	{
		Game::GetInstance().Audio->Play("E14");
		Game::GetInstance().ChangeScene(new MenuScene);
	}
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

void SelectCharScene::UpdateCharList(Buffer * B, int Skip)
{
	if (Skip > 0)
		B->seek(Skip);

	CharCount = static_cast<int>(B->next<char>());
	if (CharCount == 0)
		return;

	memset(&CharList, 0, sizeof(CCharList));
	memcpy(&CharList, B->data(), sizeof(CCharList));
#ifdef DEBUG
	for (int i = 0; i < CharCount; i++)
	{
		char Name[11];
		memset(Name, 0, 11);
		memcpy(&Name, &CharList[i].Name, 10);
		printf(
						"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s\n",
						Name, CharList[i]._Unused, CharList[i].Appr1, CharList[i].Appr2,
						CharList[i].Appr3, CharList[i].Appr4, CharList[i].Gender,
						CharList[i].Skin, CharList[i].Level, CharList[i].Experience,
						CharList[i].Strength, CharList[i].Vitality,
						CharList[i].Dexterity, CharList[i].Intelligence,
						CharList[i].Magic, CharList[i].Agility, CharList[i].Year,
						CharList[i].Month, CharList[i].Day, CharList[i].Hour,
						CharList[i].Minute, CharList[i].Second, CharList[i].MapLoc);
	}
#endif
}


