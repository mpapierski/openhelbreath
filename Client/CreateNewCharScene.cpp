#include "Game.h"

CreateNewCharScene::CreateNewCharScene()
{
	itemFocus = NONE;
	charNameEdit.setPosition(195, 110);
	specialPoints = 14;
	snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);
}

CreateNewCharScene::~CreateNewCharScene()
{

}

void CreateNewCharScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_GAMEDIALOG_9, 0);
	SpriteBank::manager.draw(dest, 194, 6, SPRID_DIALOGTEXT_BUTTONS, 69);

	Font::putText(dest, 70, 110, "Character Name", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 157, "Gender", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 173, "Skin Color", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 189, "Hair Style", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 205, "Hair Color", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 221, "Underwear Color", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 255, pointsLeftLabel, Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 275, "Strength", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 291, "Vitality", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 307, "Dexterity", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 323, "Intelligence", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 339, "Magic", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 100, 355, "Charisma", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 56, 376, "You can have each value between 10~14.", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 440, 190, "Hit Points", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 440, 206, "Mana Points", Font::NORMAL, 0, 0, 0);
	Font::putText(dest, 440, 222, "Stamina Points", Font::NORMAL, 0, 0, 0);

	switch (itemFocus)
	{
		case NONE:
			break;
		case NAME:
			Font::putAlignedText(dest, 370, 377, 214, "Enter a character name.", Font::NORMAL, 0, 0, 0);
			break;
		case GENDER:
			Font::putAlignedText(dest, 370, 377, 214, "Select character's gender.", Font::NORMAL, 0, 0, 0);
			break;
		case SKIN:
			Font::putAlignedText(dest, 370, 377, 214, "Select character's skin.", Font::NORMAL, 0, 0, 0);
			break;
		case HAIR_STYLE:
			Font::putAlignedText(dest, 370, 377, 214, "Select character's hairstyle.", Font::NORMAL, 0, 0, 0);
			break;
		case HAIR_COLOR:
			Font::putAlignedText(dest, 370, 377, 214, "Select character's hair color.", Font::NORMAL, 0, 0, 0);
			break;
		case UNDERWEAR_COLOR:
			Font::putAlignedText(dest, 370, 377, 214, "Select the color of underwear.", Font::NORMAL, 0, 0, 0);
			break;
		case STRENGTH:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "strength assigned. As STR is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, character's maximum", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "HP and maximum stamina increases.", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 405, 214, "You can equip heavier weapons and shields.", Font::SMALL, 0, 0, 0);
			break;
		case VITALITY:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "vitality assigned. As VIT is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, the max. HP greatly", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "increases as the recovery amount.", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 405, 214, "Physical damage absorption slightly increases.", Font::SMALL, 0, 0, 0);
			break;
		case DEXTERITY:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "dexterity assigned. As DEX is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, evasion from physical hits", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "(defense ratio) and hit probability increases.", Font::SMALL, 0, 0, 0);
			break;
		case INTELLIGENCE:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "intelligence assigned. As INT is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, more magic can be learned,", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "casting probability and maximum MP increases.", Font::SMALL, 0, 0, 0);
			break;
		case MAGIC:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "magic assigned. As MAG is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, magical resistance increases", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "as well as maximum MP and MP recovery.", Font::SMALL, 0, 0, 0);
			break;
		case CHARISMA:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "charisma assigned. If CHR is increased", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "to a certain amount, you can form a", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "guild. Cost of item purchase is reduced.", Font::SMALL, 0, 0, 0);
			break;
		case WARRIOR:
			break;
		case MAGE:
			break;
		case PRIEST:
			break;
		case CREATE:
			Font::putAlignedText(dest, 370, 363, 214, "Create with the character", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "with the above settings.", Font::NORMAL, 0, 0, 0);
			break;
		case CANCEL:
			Font::putAlignedText(dest, 370, 377, 214, "Return to the main selecting menu.", Font::NORMAL, 0, 0, 0);
			break;
	}

	SpriteBank::manager.draw(dest, 380, 100, SPRID_ITEM_EQUIP_W_MODELS, 0);

	SpriteBank::manager.draw(dest, 385, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == CREATE
			? INTERFACE_BUTTON_CREATE + 1 : INTERFACE_BUTTON_CREATE);

	SpriteBank::manager.draw(dest, 500, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == CANCEL
			? INTERFACE_BUTTON_CANCEL + 1 : INTERFACE_BUTTON_CANCEL);

	charNameEdit.draw(dest);
	Game::drawVersion(dest);
}

void CreateNewCharScene::onEvent(SDL_Event* eventSource)
{
	Event::onEvent(eventSource);
	charNameEdit.onEvent(eventSource);
}

void CreateNewCharScene::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	printf("x: %i y: %i\n", x, y);
	if ((x > 70 && x < 300) && (y > 110 && y < 130))
		itemFocus = NAME;
	else if ((x > 100 && x < 280) && (y > 156 && y < 170))
		itemFocus = GENDER;
	else if ((x > 100 && x < 280) && (y > 172 && y < 186))
		itemFocus = SKIN;
	else if ((x > 100 && x < 280) && (y > 188 && y < 202))
		itemFocus = HAIR_STYLE;
	else if ((x > 100 && x < 280) && (y > 204 && y < 218))
		itemFocus = HAIR_COLOR;
	else if ((x > 100 && x < 280) && (y > 220 && y < 234))
		itemFocus = UNDERWEAR_COLOR;
	else if ((x > 100 && x < 280) && (y > 274 && y < 288))
		itemFocus = STRENGTH;
	else if ((x > 100 && x < 280) && (y > 290 && y < 304))
		itemFocus = VITALITY;
	else if ((x > 100 && x < 280) && (y > 306 && y < 320))
		itemFocus = DEXTERITY;
	else if ((x > 100 && x < 280) && (y > 322 && y < 336))
		itemFocus = INTELLIGENCE;
	else if ((x > 100 && x < 280) && (y > 336 && y < 350))
		itemFocus = MAGIC;
	else if ((x > 100 && x < 280) && (y > 352 && y < 366))
		itemFocus = CHARISMA;
	else if ((x > 385 && x < 459) && (y > 445 && y < 465))
		itemFocus = CREATE;
	else if ((x > 500 && x < 574) && (y > 445 && y < 465))
		itemFocus = CANCEL;
	else
		itemFocus = NONE;
}

void CreateNewCharScene::onLButtonDown(int x, int y)
{
	if ((x > 195 && x < 295) && (y > 110 && y < 130))
		charNameEdit.setEnabled(true);

	if ((x > 500 && x < 574) && (y > 445 && y < 465))
		Game::getInstance().changeScene(new SelectCharScene);
}
