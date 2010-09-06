#include "SpriteBank.h"

SpriteBank SpriteBank::manager;

Sprite emptySprite;

SpriteBank::SpriteBank()
{

}

SpriteBank::~SpriteBank()
{

}

Sprite& SpriteBank::getSprite(int sprID)
{
	if ((SpritesContainer.size() - 1) < static_cast<unsigned int> (sprID))
	{
		return emptySprite;
	}
	else
		return SpritesContainer[sprID];
}

/*
 *  Draws sprite.
 */
void SpriteBank::drawSprite(SDL_Surface* dest, const Sprite& spr, int frame, int x, int y)
{
    int tmpX, tmpY;

    FrameSize f = spr.getFrameRect(frame);

    tmpX = x + f.xOffset;
    tmpY = y + f.yOffset;

    Surface::draw(dest, spr.getSurface(), tmpX, tmpY, f.x, f.y, f.w, f.h);
}

/*
 *  Draws animated creature on screen
 */
void SpriteBank::drawAnimatedCreature(SDL_Surface* dest, unsigned int creature_id, unsigned int animation_id, int x, int y)
{
    // TODO: maybe create separate class for creatures on screen :/
    if(creature_id > creatures.size() - 1) return;

    creatures[creature_id][animation_id].update();
    SpriteArray creature = creatures.at(creature_id);
    Sprite spr = creature.at(animation_id);
    drawSprite(dest, spr, spr.getCurrentFrame(), x, y);
}

/*
 *  Loads player weapon into weapon array
 *  Must pass both female and male model filename
 *  In order to avoid confusion with different Ids
 */
bool SpriteBank::loadPlayerWeapons(const std::string& maleModelfileName, const std::string& femaleModelfileName)
{
    SpriteArray male_sprites = getSpritesFromPakFile(maleModelfileName);
    if(male_sprites.size() == 0) return false;

    for(unsigned int i = 0; i < male_sprites.size(); i++) male_weapons.push_back(male_sprites.at(i));
    fprintf(stdout, "Equipment: %s.pak loaded. %i sprites found\r\n", maleModelfileName.c_str(), male_sprites.size());

    SpriteArray female_sprites = getSpritesFromPakFile(femaleModelfileName);
    if(female_sprites.size() == 0) return false;

    for(unsigned int i = 0; i < female_sprites.size(); i++) female_weapons.push_back(female_sprites.at(i));
    fprintf(stdout, "Equipment: %s.pak loaded. %i sprites found\r\n", femaleModelfileName.c_str(), female_sprites.size());

    return true;
}

/*
 *  Loads player equipment into equipment array
 *  Must pass both female and male model filename
 *  In order to avoid confusion with different Ids
 */
bool SpriteBank::loadPlayerEquipment(const std::string& maleModelfileName, const std::string& femaleModelfileName)
{
    SpriteArray male_sprites = getSpritesFromPakFile(maleModelfileName);
    if(male_sprites.size() == 0) return false;

    for(unsigned int i = 0; i < male_sprites.size(); i++) male_equipment.push_back(male_sprites.at(i));
    fprintf(stdout, "Equipment: %s.pak loaded. %i sprites found\r\n", maleModelfileName.c_str(), male_sprites.size());

    SpriteArray female_sprites = getSpritesFromPakFile(femaleModelfileName);
    if(female_sprites.size() == 0) return false;

    for(unsigned int i = 0; i < female_sprites.size(); i++) female_equipment.push_back(female_sprites.at(i));
    fprintf(stdout, "Equipment: %s.pak loaded. %i sprites found\r\n", femaleModelfileName.c_str(), female_sprites.size());

    return true;
}

/*
 *  Loads .PAK file sprites into players array
 */
bool SpriteBank::loadPlayerSprites(const std::string& fileName)
{
    SpriteArray player_sprites = getSpritesFromPakFile(fileName);
    if(player_sprites.size() == 0) return false;

    players.push_back(player_sprites);

    fprintf(stdout, "Players: %s.pak loaded. %i sprites found\r\n", fileName.c_str(), player_sprites.size());
    return true;
}

/*
 *  Loads .PAK file sprites into creature array
 */
bool SpriteBank::loadCreatureSprites(const std::string& fileName)
{
    SpriteArray creature_sprites = getSpritesFromPakFile(fileName);
    if(creature_sprites.size() == 0) return false;

    creatures.push_back(creature_sprites);

    fprintf(stdout, "Monster: %s.pak loaded. %i sprites found\r\n", fileName.c_str(), creature_sprites.size());
    return true;
}

/*
 *  Loads sprites from .PAK file and stores it into array so we can sort it out later
 */
SpriteArray SpriteBank::getSpritesFromPakFile(const std::string& fileName)
{
    FILE* pakFile;
    int spritesCount;
    int framesCount;
    std::vector<Sprite> sprites;

    if (fileName.empty())
    {
        fprintf(stderr, "SpriteBank::getSpritesFromPakFile was passed empty filename\r\n");
        return sprites;
    }

    std::string path = "SPRITES/" + fileName + ".pak";

    pakFile = fopen(path.c_str(), "rb");
    if (pakFile == NULL)
    {
            //fclose(pakFile);
            path = "SPRITES/" + fileName + ".PAK";
            pakFile = fopen(path.c_str(), "rb");
            if (pakFile == NULL)
            {
                    fprintf(stderr, "Unable to load: %s\r\n", path.c_str());
                    return sprites;
            }
    }

    /*char pakHeader[20];
     fread(&pakHeader, 1, 20, pakFile);
     printf("%s\n", pakHeader);

     if (strcmp(pakHeader, "<Pak file header>") != 0)
     {
     }*/

    fseek(pakFile, 20, SEEK_SET);
    fread(&spritesCount, 1, 4, pakFile);

    struct
    {
        int offset;
        int size;
    } spriteInfo[spritesCount];

    fread(&spriteInfo, 8, spritesCount, pakFile);

    for (int i = 0; i < spritesCount; i++)
    {
        Sprite tempSprite;
        SDL_Surface* tempSurface;
        int bitmapFileLoc;
        int bitmapFileSize;
        char* bitmapFile;

        fseek(pakFile, spriteInfo[i].offset + 100, SEEK_SET);

        /*char spriteHeader[100];
         fread(&spriteHeader, 1, 100, pakFile);
         printf("%s\n", spriteHeader);

         if (strcmp(spriteHeader, "<Sprite File Header>") != 0)
         {
         }*/

        fread(&framesCount, 4, 1, pakFile);

        tempSprite.setFramesCount(framesCount);

        for (int y = 0; y < framesCount; y++)
        {
            FrameSize tempFrameRect;

            fread(&tempFrameRect, 2, 6, pakFile);
            tempSprite.setFrameRect(tempFrameRect.x, tempFrameRect.y, tempFrameRect.w, tempFrameRect.h, tempFrameRect.xOffset, tempFrameRect.yOffset);
        }

        int max = 0;
        for (int z = 0; z < framesCount; z++)
        {
            if (tempSprite.getFrameRect(z).h > tempSprite.getFrameRect(max).h) max = z;
        }
        tempSprite.setMaxFrameH(tempSprite.getFrameRect(max).h);

        max = 0;
		for (int z = 0; z < framesCount; z++)
		{
			if (tempSprite.getFrameRect(z).w > tempSprite.getFrameRect(max).w)
				max = z;
		}
		tempSprite.setMaxFrameW(tempSprite.getFrameRect(max).w);

        bitmapFileLoc = spriteInfo[i].offset + (108 + (12 * framesCount));
        bitmapFileSize = spriteInfo[i].size - (108 + (12 * framesCount));

        bitmapFile = new char[bitmapFileSize];

        fseek(pakFile, bitmapFileLoc, SEEK_SET);
        fread(bitmapFile, 1, bitmapFileSize, pakFile);

        SDL_RWops *rw = SDL_RWFromMem(bitmapFile, bitmapFileSize);
        tempSurface = SDL_LoadBMP_RW(rw, 1);

        SDL_Surface* tmp = NULL;
        tmp = SDL_DisplayFormat(tempSurface);
        SDL_FreeSurface(tempSurface);

        tempSprite.setSurface(tmp);
        tempSprite.setColorKey();

        sprites.push_back(tempSprite);

        delete[] bitmapFile;
    }

    fclose(pakFile);
    return sprites;
}

void SpriteBank::load(const std::string& fileName)
{
	if (fileName.empty())
		return;

	FILE* pakFile;
	int spritesCount;
	int framesCount;

	std::string path = "SPRITES/" + fileName + ".pak";

	pakFile = fopen(path.c_str(), "rb");
	if (pakFile == NULL)
	{
		//fclose(pakFile);
		path = "SPRITES/" + fileName + ".PAK";
		pakFile = fopen(path.c_str(), "rb");
		if (pakFile == NULL)
		{
			fprintf(stderr, "Unable to load: %s\n", path.c_str());
			return;
		}
	}
	/*char pakHeader[20];
	 fread(&pakHeader, 1, 20, pakFile);
	 printf("%s\n", pakHeader);

	 if (strcmp(pakHeader, "<Pak file header>") != 0)
	 {
	 }*/

	fseek(pakFile, 20, SEEK_SET);
	fread(&spritesCount, 1, 4, pakFile);

	struct
	{
			int offset;
			int size;
	} spriteInfo[spritesCount];

	fread(&spriteInfo, 8, spritesCount, pakFile);

	for (int i = 0; i < spritesCount; i++)
	{
		Sprite tempSprite;
		SDL_Surface* tempSurface;
		int bitmapFileLoc;
		int bitmapFileSize;
		char* bitmapFile;

		fseek(pakFile, spriteInfo[i].offset + 100, SEEK_SET);

		/*char spriteHeader[100];
		 fread(&spriteHeader, 1, 100, pakFile);
		 printf("%s\n", spriteHeader);

		 if (strcmp(spriteHeader, "<Sprite File Header>") != 0)
		 {
		 }*/

		fread(&framesCount, 4, 1, pakFile);

		tempSprite.setFramesCount(framesCount);

		for (int y = 0; y < framesCount; y++)
		{
			FrameSize tempFrameRect;

			fread(&tempFrameRect, 2, 6, pakFile);
			tempSprite.setFrameRect(tempFrameRect.x, tempFrameRect.y,
					tempFrameRect.w, tempFrameRect.h, tempFrameRect.xOffset,
					tempFrameRect.yOffset);
		}

		int max = 0;
		for (int z = 0; z < framesCount; z++)
		{
			if (tempSprite.getFrameRect(z).h > tempSprite.getFrameRect(max).h)
				max = z;
		}
		tempSprite.setMaxFrameH(tempSprite.getFrameRect(max).h);

		max = 0;
		for (int z = 0; z < framesCount; z++)
		{
			if (tempSprite.getFrameRect(z).w > tempSprite.getFrameRect(max).w)
				max = z;
		}
		tempSprite.setMaxFrameW(tempSprite.getFrameRect(max).w);

		bitmapFileLoc = spriteInfo[i].offset + (108 + (12 * framesCount));
		bitmapFileSize = spriteInfo[i].size - (108 + (12 * framesCount));

		bitmapFile = new char[bitmapFileSize];

		fseek(pakFile, bitmapFileLoc, SEEK_SET);
		fread(bitmapFile, 1, bitmapFileSize, pakFile);

		SDL_RWops *rw = SDL_RWFromMem(bitmapFile, bitmapFileSize);
		tempSurface = SDL_LoadBMP_RW(rw, 1);

		SDL_Surface* tmp = NULL;
		tmp = SDL_DisplayFormat(tempSurface);
		SDL_FreeSurface(tempSurface);

		tempSprite.setSurface(tmp);

		SpritesContainer.push_back(tempSprite);

		delete[] bitmapFile;
	}

	printf("Not animated: %s.pak loaded. %i sprites found\r\n", fileName.c_str(), spritesCount);
	fclose(pakFile);
}

void SpriteBank::draw(SDL_Surface* dest, int x, int y, int sprID, int frameID)
{
	if ((SpritesContainer.size() - 1) < static_cast<unsigned int> (sprID))
		return;

	int tmpX = x + SpritesContainer[sprID].getFrameRect(frameID).xOffset;
	int tmpY = y + SpritesContainer[sprID].getFrameRect(frameID).yOffset;

	Surface::draw(dest, SpritesContainer[sprID].getSurface(), tmpX, tmpY,
			SpritesContainer[sprID].getFrameRect(frameID).x,
			SpritesContainer[sprID].getFrameRect(frameID).y,
			SpritesContainer[sprID].getFrameRect(frameID).w,
			SpritesContainer[sprID].getFrameRect(frameID).h);
}

void SpriteBank::draw(SDL_Surface* dest, int x, int y, int w, int h, int sprID, int frameID)
{
	if ((SpritesContainer.size() - 1) < static_cast<unsigned int> (sprID))
		return;

	Surface::draw(dest, SpritesContainer[sprID].getSurface(), x, y,
			SpritesContainer[sprID].getFrameRect(frameID).x,
			SpritesContainer[sprID].getFrameRect(frameID).y, w, h);
}

void SpriteBank::cleanUp()
{
    for (unsigned int i = 0; i < SpritesContainer.size(); i++)
    {
    	SpritesContainer[i].releaseSurface();
    }
    SpritesContainer.clear();

    for (unsigned int i = 0 ; i < creatures.size(); i++)
    {
        SpriteArray arr = creatures[i];
        for(unsigned int j = 0; j < arr.size(); j++)
			arr[j].releaseSurface();

        arr.clear();
    }
    creatures.clear();

    for (unsigned int i = 0 ; i < players.size(); i++)
    {
        SpriteArray arr = players[i];
        for(unsigned int j = 0; j < arr.size(); j++)
			arr[j].releaseSurface();

        arr.clear();
    }
    players.clear();

    for(unsigned int i = 0; i < male_equipment.size(); i++) SDL_FreeSurface(male_equipment[i].getSurface());
    male_equipment.clear();
    for(unsigned int i = 0; i < female_equipment.size(); i++) SDL_FreeSurface(female_equipment[i].getSurface());
    female_equipment.clear();
    for(unsigned int i = 0; i < male_weapons.size(); i++) SDL_FreeSurface(male_weapons[i].getSurface());
    male_weapons.clear();
    for(unsigned int i = 0; i < female_weapons.size(); i++) SDL_FreeSurface(female_weapons[i].getSurface());
    female_weapons.clear();
}
