#include "Game.h"

SelectCharScene::SelectCharScene()
{
	slotSelect = 0;

	buttonFocus = START;
}

SelectCharScene::SelectCharScene(Buffer* data)
{
	slotSelect = 0;

	buttonFocus = START;

	updateCharList(data, 12); // Skip 12 bytes (Dates)
}

SelectCharScene::~SelectCharScene()
{

}

void SelectCharScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_GAMEDIALOG_8, 0);
	SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_CHARLIST);

	switch (slotSelect)
	{
		case 0:
			SpriteBank::manager.draw(dest, 103, 54, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 1:
			SpriteBank::manager.draw(dest, 212, 54, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 2:
			SpriteBank::manager.draw(dest, 321, 54, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_SLOTSELECTED);
			break;
		case 3:
			SpriteBank::manager.draw(dest, 430, 54, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_SLOTSELECTED);
			break;
	}

	switch (buttonFocus)
	{
		case START:
			SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_START);
			Font::putAlignedText(dest, 98, 305, 259, "Log in with the selected character.", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 320, 259, "You can log in by clicking the button", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 335, 259, "or pressing the enter after selecting", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 350, 259, "character.", Font::NORMAL, 0, 0, 0);
			break;
		case CREATE_NEW_CHAR:
			SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_CREATENEWCHAR);
			Font::putAlignedText(dest, 98, 320, 259, "Make a new character.", Font::NORMAL, 0, 0, 0);
			break;
		case DELETE_CHAR:
			SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_DELCHAR);
			Font::putAlignedText(dest, 98, 290, 259, "Delete the selected character. Deleted", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 305, 259, "characters cannot be recovered. You", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 320, 259, "also cannot delete a character above", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 335, 259, "level 50. If you want to delete a ", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 350, 259, "character above level 50, please send", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 98, 365, 259, "an e-mail to the game master.", Font::NORMAL, 0, 0, 0);
			break;
		case CHANGE_PASSWD:
			SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_CHANGEPASSWD);
			Font::putAlignedText(dest, 98, 320, 259, "Change the account password.", Font::NORMAL, 0, 0, 0);
			break;
		case LOGOUT:
			SpriteBank::manager.draw(dest, 0, 0, SPRID_DIALOGTEXT_BUTTONS, INTERFACE_BUTTON_LOGOUTBIG);
			Font::putAlignedText(dest, 98, 320, 259, "Back to the main menu.", Font::NORMAL, 0, 0, 0);
			break;
		default:
			;
	}

	/*for (int i = 0; i < charCount; i++)
	{
		char Txt[11];
		memset(&Txt, 0, 11);
		memcpy(&Txt, &charList[i].Name, 10);
		Font::putText(dest, 112 + i*109, 179, Txt, Font::NORMAL, 51, 0, 51);
		memset(&Txt, 0, 11);
		snprintf(Txt, 11,"%d", charList[i].Level);
		Font::putText(dest, 138 + i*109, 195, Txt, Font::NORMAL, 51, 0, 51);
		memset(&Txt, 0, 11);
		snprintf(Txt, 11, "%d", charList[i].Experience);
		Font::putText(dest, 138 + i*109, 210, Txt, Font::NORMAL, 51, 0, 51);
	}

	if (strlen(charList[slotSelect].Name) > 0)
	{
		char LogOut[30];
		snprintf(LogOut, 30, "Last Logout : %04d/%02d/%02d  %02d:%02d:%02d", charList[slotSelect].Year, charList[slotSelect].Month, charList[slotSelect].Day, charList[slotSelect].Hour, charList[slotSelect].Minute, charList[slotSelect].Second);
		Font::putAlignedText(dest, 98, 425, 357-98, LogOut, Font::NORMAL, 0, 0, 0);
	}*/

	Font::putAlignedText(dest, 122, 456, 315-122, "Test Server", Font::NORMAL, 0, 0, 0);

	Game::drawVersion(dest);
}

void SelectCharScene::onMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle)
{
	if ((X > 363 && X < 540) && (Y > 287 && Y < 312))
		buttonFocus = START;
	if ((X > 363 && X < 540) && (Y > 317 && Y < 342))
		buttonFocus = CREATE_NEW_CHAR;
	if ((X > 363 && X < 540) && (Y > 347 && Y < 372))
		buttonFocus = DELETE_CHAR;
	if ((X > 363 && X < 540) && (Y > 377 && Y < 402))
		buttonFocus = CHANGE_PASSWD;
	if ((X > 363 && X < 540) && (Y > 407 && Y < 432))
		buttonFocus = LOGOUT;
}

void SelectCharScene::onLButtonDown(int X, int Y)
{
	if (Y > 54 && Y < 240)
	{
		if (X > 103 && X < 210)
		{
			SoundBank::manager.play("E14");
			slotSelect = 0;
		}
		if (X > 211 && X < 319)
		{
			SoundBank::manager.play("E14");
			slotSelect = 1;
		}
		if (X > 321 && X < 427)
		{
			SoundBank::manager.play("E14");
			slotSelect = 2;
		}
		if (X > 430 && X < 536)
		{
			SoundBank::manager.play("E14");
			slotSelect = 3;
		}
	}

	if ((X > 363 && X < 540) && (Y > 317 && Y < 342))
	{
		SoundBank::manager.play("E14");
		Game::getInstance().changeScene(new CreateNewCharScene);
	}

	if ((X > 363 && X < 540) && (Y > 407 && Y < 432))
	{
		SoundBank::manager.play("E14");
		Game::getInstance().changeScene(new MenuScene);
	}
}

void SelectCharScene::onKeyDown(SDLKey sym, SDLMod Mod, Uint16 Unicode)
{
	if (sym == SDLK_ESCAPE)
	{
		Game::getInstance().changeScene(new MenuScene);
	}
}

void SelectCharScene::updateCharList(Buffer* data, int skip)
{
	if (skip > 0)
		data->seek(skip);

	charCount = static_cast<int>(data->next<char>());
	if (charCount == 0)
		return;

	memset(&charList, 0, sizeof(CCharList));
	memcpy(&charList, data->data(), sizeof(CCharList));
#ifdef DEBUG
	for (int i = 0; i < charCount; i++)
	{
		char Name[11];
		memset(Name, 0, 11);
		memcpy(&Name, &charList[i].Name, 10);
		printf(
						"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s\n",
						Name, charList[i]._Unused, charList[i].Appr1, charList[i].Appr2,
						charList[i].Appr3, charList[i].Appr4, charList[i].Gender,
						charList[i].Skin, charList[i].Level, charList[i].Experience,
						charList[i].Strength, charList[i].Vitality,
						charList[i].Dexterity, charList[i].Intelligence,
						charList[i].Magic, charList[i].Agility, charList[i].Year,
						charList[i].Month, charList[i].Day, charList[i].Hour,
						charList[i].Minute, charList[i].Second, charList[i].MapLoc);
	}
#endif
}

