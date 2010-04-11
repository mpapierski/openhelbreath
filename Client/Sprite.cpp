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

	std::string path = "SPRITES/";

	path.append(FileName);

	int tmp, tmp2;

	int TotalFrames;
	int BitmapFileStartLoc;
	int BmpSize;
	char *BmpFile;

	pakFile = fopen(path.c_str(), "rb");

	if(pakFile == NULL)
	{
		printf("Unable to load: %s\n", path.c_str());
		return false;
	}

	fseek(pakFile, (24+(Number*8)), SEEK_SET);
	fread(&tmp, 1, 4, pakFile);

	fseek(pakFile, tmp+100, SEEK_SET);
	fread(&TotalFrames, 1, 4, pakFile);

	Frames.resize(TotalFrames);

	for(int i = 0; i < TotalFrames; i++)
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

	int max = 0;
	for (int i = 0; i < TotalFrames; i++)
	{
		if (Frames[i].h > Frames[max].h)
	         max = i;
	}
	MaxFrameH = Frames[max].h;

	BitmapFileStartLoc = tmp  + (108 + (12*TotalFrames));

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
	SDL_Rect Empty = { 0, 0, 0, 0};

	if(Frames.size() != 0)
	{
		return Frames.at(Number);
	}
	else
		return Empty;
}

int Sprite::GetMaxFrameH() const
{
	return MaxFrameH;
}

Sprite::~Sprite()
{
	SDL_FreeSurface(Image);
}
