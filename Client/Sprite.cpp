#include "Sprite.h"

Sprite::Sprite()
{
	Image = NULL;
}

Sprite::Sprite(const std::string &FileName, int Number)
{
	LoadFromFile(FileName, Number);
}

bool Sprite::LoadFromFile(const std::string &FileName, int Number)
{
	FILE *pakFile;

	int tmp, tmp2;

	int TotalFrame;
	int BitmapFileStartLoc;
	int BmpSize;
	char *BmpFile;

	pakFile = fopen(FileName.c_str(), "rb");

	if(pakFile == NULL)
	{
		printf("Unable to load: %s\n", FileName.c_str());
		return false;
	}

	fseek(pakFile, (24+(Number*8)), SEEK_SET);
	fread(&tmp, 1, 4, pakFile);

	fseek(pakFile, tmp+100, SEEK_SET);
	fread(&TotalFrame, 1, 4, pakFile);

	Frames.resize(TotalFrame);

	for(int i = 0; i < TotalFrame; i++)
	{
		tmp2 = (tmp+104+(i*12));
		fseek(pakFile, tmp2, SEEK_SET);
		fread(&Frames[i].x, 1, 2, pakFile);

		fseek(pakFile, tmp2+2, SEEK_SET);
		fread(&Frames[i].y, 1, 2, pakFile);

		fseek(pakFile, tmp2+4, SEEK_SET);
		fread(&Frames[i].w, 1, 2, pakFile);

		fseek(pakFile, tmp2+6, SEEK_SET);
		fread(&Frames[i].h, 1, 2, pakFile);
	}

	BitmapFileStartLoc = tmp  + (108 + (12*TotalFrame));

	fseek(pakFile, BitmapFileStartLoc+2, SEEK_SET);
	fread(&BmpSize, 1, 4, pakFile);

	fseek(pakFile, BitmapFileStartLoc, SEEK_SET);

	BmpFile = new char[BmpSize];

	fread(BmpFile, 1, BmpSize, pakFile);

	SDL_RWops *rw = SDL_RWFromMem(BmpFile, BmpSize);
	Image = SDL_LoadBMP_RW(rw, 1);

	delete [] BmpFile;

	fclose(pakFile);

	return true;
}

bool Sprite::Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int Frame)
{
	return Surface::Draw(Dest, SpriteSrc.GetSurface(), X, Y, SpriteSrc.GetFrame(Frame).x, SpriteSrc.GetFrame(Frame).y, SpriteSrc.GetFrame(Frame).w, SpriteSrc.GetFrame(Frame).h);
}

bool Sprite::Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int W, int H, int Frame)
{
	return Surface::Draw(Dest, SpriteSrc.GetSurface(), X, Y, SpriteSrc.GetFrame(Frame).x, SpriteSrc.GetFrame(Frame).y, W, H);
}

SDL_Surface *Sprite::GetSurface() const
{
	return Image;
}

SDL_Rect Sprite::GetFrame(int Number) const
{
	return Frames.at(Number);
}

Sprite::~Sprite()
{

}
