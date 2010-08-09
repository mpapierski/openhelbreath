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

	fclose(pakFile);
}

void SpriteBank::draw(SDL_Surface* dest, int x, int y, int sprID, int frameID)
{
	if ((SpritesContainer.size() - 1) < static_cast<unsigned int> (sprID))
		return;

	Surface::draw(dest, SpritesContainer[sprID].getSurface(), x, y,
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

void SpriteBank::drawAnimated(SDL_Surface* dest, int x, int y, int sprID)
{
	if ((SpritesContainer.size() - 1) < static_cast<unsigned int> (sprID))
		return;

	int frame, tmpX, tmpY;

	SpritesContainer[sprID].update();

	frame = SpritesContainer[sprID].getCurrentFrame();

	tmpX = x + SpritesContainer[sprID].getFrameRect(frame).xOffset;
	tmpY = y + SpritesContainer[sprID].getFrameRect(frame).yOffset;

	Surface::draw(dest, SpritesContainer[sprID].getSurface(), tmpX, tmpY,
			SpritesContainer[sprID].getFrameRect(frame).x,
			SpritesContainer[sprID].getFrameRect(frame).y,
			SpritesContainer[sprID].getFrameRect(frame).w,
			SpritesContainer[sprID].getFrameRect(frame).h);
}

void SpriteBank::cleanUp()
{
	for (unsigned int i = 0; i < SpritesContainer.size(); i++)
	{
		SDL_FreeSurface(SpritesContainer[i].getSurface());
	}
}
