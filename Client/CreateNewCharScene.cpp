#include "Game.h"

CreateNewCharScene::CreateNewCharScene()
{
	itemFocus = NONE;
	charNameEdit.setPosition(195, 110);
	specialPoints = 10;
	snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);

	strength = 10;
	vitality = 10;
	dexterity = 10;
	intelligence = 10;
	magic = 10;
	charisma = 10;

	newPlayer.setSex(Player::FEMALE);
	newPlayer.setRace(Player::BLACK);
	newPlayer.setHairStyle(PLAYER_HAIRSTYLE_0);
	newPlayer.setUnderwearColor(PLAYER_UNDERWEAR_COLOR_0);
	newPlayer.setOrientation(ORIENTATION_RIGHT_DOWN);
	newPlayer.setAction(PLAYER_ACTION_WALKING_PEACE_MODE);

	orientationTimer.start();

	underwearColor = 0;
	hairStyle = 0;
}

CreateNewCharScene::~CreateNewCharScene()
{

}

void CreateNewCharScene::onLoop()
{
	if (orientationTimer.getTicks() > 2500)
	{
		int tmp = newPlayer.orientation();
		tmp++;
		if(tmp > 7)
			tmp = 0;

		newPlayer.setOrientation(tmp);
		orientationTimer.start();
	}
}

void CreateNewCharScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 0, 0, SPRID_GAMEDIALOG_9, 0);
	SpriteBank::manager.draw(dest, 2, -2, SPRID_DIALOGTEXT_BUTTONS, 69);

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

	char tmp[8];
	snprintf(tmp, 8, "%d", strength);
	Font::putText(dest, 203, 275, tmp, Font::NORMAL, 0, 0, 0);
	snprintf(tmp, 8, "%d", vitality);
	Font::putText(dest, 203, 291, tmp, Font::NORMAL, 0, 0, 0);
	snprintf(tmp, 8, "%d", dexterity);
	Font::putText(dest, 203, 307, tmp, Font::NORMAL, 0, 0, 0);
	snprintf(tmp, 8, "%d", intelligence);
	Font::putText(dest, 203, 323, tmp, Font::NORMAL, 0, 0, 0);
	snprintf(tmp, 8, "%d", magic);
	Font::putText(dest, 203, 339, tmp, Font::NORMAL, 0, 0, 0);
	snprintf(tmp, 8, "%d", charisma);
	Font::putText(dest, 203, 355, tmp, Font::NORMAL, 0, 0, 0);

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
			Font::putAlignedText(dest, 370, 405, 214, "You can equip heavier weapons and shields.", Font::SMALL, 0, 0,
					0);
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
			Font::putAlignedText(dest, 370, 391, 214, "(defense ratio) and hit probability increases.", Font::SMALL, 0,
					0, 0);
			break;
		case INTELLIGENCE:
			Font::putAlignedText(dest, 370, 349, 214, "Determine your character's initial", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 363, 214, "intelligence assigned. As INT is", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "increased, more magic can be learned,", Font::SMALL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 391, 214, "casting probability and maximum MP increases.", Font::SMALL, 0,
					0, 0);
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
		case MAGICIAN:
			break;
		case MASTER:
			break;
		case CREATE:
			Font::putAlignedText(dest, 370, 363, 214, "Create with the character", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, 370, 377, 214, "with the above settings.", Font::NORMAL, 0, 0, 0);
			break;
		case CANCEL:
			Font::putAlignedText(dest, 370, 377, 214, "Return to the main selecting menu.", Font::NORMAL, 0, 0, 0);
			break;
	}
	switch (newPlayer.sex())
	{
		case Player::FEMALE:
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_W_MODELS, newPlayer.race());
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_W_HAIR_STYLES, hairStyle);
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_W_UNDERWEAR, underwearColor);
			break;
		case Player::MALE:
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_M_MODELS, newPlayer.race());
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_M_HAIR_STYLES, hairStyle);
			SpriteBank::manager.draw(dest, 510, 265, SPRID_ITEM_EQUIP_M_UNDERWEAR, underwearColor);
			break;
	}

	SpriteBank::manager.draw(dest, 60, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == WARRIOR ? INTERFACE_BUTTON_WARRIOR
			+ 1 : INTERFACE_BUTTON_WARRIOR);

	SpriteBank::manager.draw(dest, 145, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == MAGICIAN ? INTERFACE_BUTTON_MAGICIAN
			+ 1 : INTERFACE_BUTTON_MAGICIAN);

	SpriteBank::manager.draw(dest, 230, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == MASTER ? INTERFACE_BUTTON_MASTER
			+ 1 : INTERFACE_BUTTON_MASTER);

	SpriteBank::manager.draw(dest, 385, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == CREATE ? INTERFACE_BUTTON_CREATE
			+ 1 : INTERFACE_BUTTON_CREATE);

	SpriteBank::manager.draw(dest, 500, 445, SPRID_DIALOGTEXT_BUTTONS, itemFocus == CANCEL ? INTERFACE_BUTTON_CANCEL
			+ 1 : INTERFACE_BUTTON_CANCEL);

	charNameEdit.draw(dest);
	newPlayer.draw(dest, 500, 165);
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
	else if ((x > 100 && x < 280) && (y > 275 && y < 290))
		itemFocus = STRENGTH;
	else if ((x > 100 && x < 280) && (y > 291 && y < 306))
		itemFocus = VITALITY;
	else if ((x > 100 && x < 280) && (y > 307 && y < 323))
		itemFocus = DEXTERITY;
	else if ((x > 100 && x < 280) && (y > 324 && y < 339))
		itemFocus = INTELLIGENCE;
	else if ((x > 100 && x < 280) && (y > 340 && y < 355))
		itemFocus = MAGIC;
	else if ((x > 100 && x < 280) && (y > 356 && y < 371))
		itemFocus = CHARISMA;
	else if ((x > 60 && x < 134) && (y > 445 && y < 465))
		itemFocus = WARRIOR;
	else if ((x > 145 && x < 219) && (y > 445 && y < 465))
		itemFocus = MAGICIAN;
	else if ((x > 230 && x < 304) && (y > 445 && y < 465))
		itemFocus = MASTER;
	else if ((x > 385 && x < 459) && (y > 445 && y < 465))
		itemFocus = CREATE;
	else if ((x > 500 && x < 574) && (y > 445 && y < 465))
		itemFocus = CANCEL;
	else
		itemFocus = NONE;
}

void CreateNewCharScene::onLButtonDown(int x, int y)
{
	// Name TextEdit
	if ((x > 195 && x < 295) && (y > 110 && y < 130))
	{
		SoundBank::manager.play("E14");
		charNameEdit.setEnabled(true);
	}

	// Gender
	if ((x > 236 && x < 278) && (y > 156 && y < 170))
	{
		SoundBank::manager.play("E14");

		switch (newPlayer.sex())
		{
			case Player::FEMALE:
				newPlayer.setSex(Player::MALE);
				break;
			case Player::MALE:
				newPlayer.setSex(Player::FEMALE);
				break;
		}
	}

	// Race
	if ((x > 235 && x < 255) && (y > 172 && y < 186))
	{
		SoundBank::manager.play("E14");

		switch (newPlayer.race())
		{
			case Player::BLACK:
				newPlayer.setRace(Player::ASIAN);
				break;
			case Player::WHITE:
				newPlayer.setRace(Player::BLACK);
				break;
			case Player::ASIAN:
				newPlayer.setRace(Player::WHITE);
				break;
		}
	}
	if ((x > 258 && x < 278) && (y > 172 && y < 186))
	{
		SoundBank::manager.play("E14");

		switch (newPlayer.race())
		{
			case Player::BLACK:
				newPlayer.setRace(Player::WHITE);
				break;
			case Player::WHITE:
				newPlayer.setRace(Player::ASIAN);
				break;
			case Player::ASIAN:
				newPlayer.setRace(Player::BLACK);
				break;
		}
	}
	// Hair style change buttons
	if ((x > 235 && x < 255) && (y > 188 && y < 202))
	{
		SoundBank::manager.play("E14");
		hairStyle--;
		if(hairStyle < 0)
			hairStyle = 7;
		newPlayer.setHairStyle((hairStyle*12));
	}

	if ((x > 258 && x < 278) && (y > 188 && y < 202))
	{
		SoundBank::manager.play("E14");
		hairStyle++;
		if(hairStyle > 7)
			hairStyle = 0;
		newPlayer.setHairStyle((hairStyle*12));
	}

	// Underwear change buttons
	if ((x > 235 && x < 256) && (y > 220 && y < 234))
	{
		SoundBank::manager.play("E14");
		underwearColor--;
		if(underwearColor < 0)
			underwearColor = 7;
		newPlayer.setUnderwearColor((96 + (underwearColor*12)));
	}

	if ((x > 258 && x < 278) && (y > 220 && y < 234))
	{
		SoundBank::manager.play("E14");
		underwearColor++;
		if(underwearColor > 7)
			underwearColor = 0;
		newPlayer.setUnderwearColor((96 + (underwearColor*12)));
	}

	// strength points
	if ((x > 235 && x < 256) && (y > 274 && y < 288))
	{
		SoundBank::manager.play("E14");
		if((strength < 14) && (specialPoints > 0))
		{
			strength++;
			specialPoints--;
			snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);
		}
	}
	if ((x > 258 && x < 278) && (y > 274 && y < 288))
	{
		SoundBank::manager.play("E14");
		if((strength > 10) && (specialPoints < 10))
		{
			strength--;
			specialPoints++;
			snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);
		}
	}

	// vitality points
	if ((x > 235 && x < 256) && (y > 290 && y < 304))
	{
		SoundBank::manager.play("E14");
		if((vitality < 14) && (specialPoints > 0))
		{
			vitality++;
			specialPoints--;
			snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);
		}
	}
	if ((x > 258 && x < 278) && (y > 290 && y < 304))
	{
		SoundBank::manager.play("E14");
		if((vitality > 10) && (specialPoints < 10))
		{
			vitality--;
			specialPoints++;
			snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);
		}
	}

	// dexterity points
	if ((x > 235 && x < 256) && (y > 306 && y < 320))
	{
		SoundBank::manager.play("E14");
		if((dexterity < 14) && (specialPoints > 0))
		{
			dexterity++;
			specialPoints--;
		}
	}
	if ((x > 258 && x < 278) && (y > 306 && y < 320))
	{
		SoundBank::manager.play("E14");
		if((dexterity > 10) && (specialPoints < 10))
		{
			dexterity--;
			specialPoints++;
		}
	}

	// intelligence points
	if ((x > 235 && x < 256) && (y > 322 && y < 336))
	{
		SoundBank::manager.play("E14");
		if((intelligence < 14) && (specialPoints > 0))
		{
			intelligence++;
			specialPoints--;
		}
	}
	if ((x > 258 && x < 278) && (y > 322 && y < 336))
	{
		SoundBank::manager.play("E14");
		if((intelligence > 10) && (specialPoints < 10))
		{
			intelligence--;
			specialPoints++;
		}
	}

	// magic points
	if ((x > 235 && x < 256) && (y > 336 && y < 350))
	{
		SoundBank::manager.play("E14");
		if((magic < 14) && (specialPoints > 0))
		{
			magic++;
			specialPoints--;
		}
	}
	if ((x > 258 && x < 278) && (y > 336 && y < 350))
	{
		SoundBank::manager.play("E14");
		if((magic > 10) && (specialPoints < 10))
		{
			magic--;
			specialPoints++;
		}
	}

	// charisma points
	if ((x > 235 && x < 256) && (y > 356 && y < 370))
	{
		SoundBank::manager.play("E14");
		if((charisma < 14) && (specialPoints > 0))
		{
			charisma++;
			specialPoints--;
		}
	}
	if ((x > 258 && x < 278) && (y > 356 && y < 370))
	{
		SoundBank::manager.play("E14");
		if((charisma > 10) && (specialPoints < 10))
		{
			charisma--;
			specialPoints++;
		}
	}

	// Warrior button
	if ((x > 60 && x < 134) && (y > 445 && y < 465))
	{
		SoundBank::manager.play("E14");
		strength = 14;
		vitality = 12;
		dexterity = 14;
		intelligence = 10;
		magic = 10;
		charisma = 10;
		specialPoints = 0;
	}

	// Magician button
	if ((x > 145 && x < 219) && (y > 445 && y < 465))
	{
		SoundBank::manager.play("E14");
		strength = 10;
		vitality = 12;
		dexterity = 10;
		intelligence = 14;
		magic = 14;
		charisma = 10;
		specialPoints = 0;
	}

	// Master button
	if ((x > 230 && x < 304) && (y > 445 && y < 465))
	{
		SoundBank::manager.play("E14");
		strength = 14;
		vitality = 10;
		dexterity = 10;
		intelligence = 10;
		magic = 12;
		charisma = 14;
		specialPoints = 0;
	}

	// Update special points label
	snprintf(pointsLeftLabel, 30, "Special stat points left: %d", specialPoints);

	// Cancel button
	if ((x > 500 && x < 574) && (y > 445 && y < 465))
	{
		SoundBank::manager.play("E14");
		Game::getInstance().changeScene(new SelectCharScene);
	}
}
