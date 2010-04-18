#include "Sprite.h"

#ifdef DEF_CACHE
std::vector<Sprite*> Sprite::Cache;
#endif

Sprite::Sprite()
{
	Image = NULL;
}

Sprite::Sprite(const std::string &FileName, int Number)
{
	Init(FileName, Number);
}

bool Sprite::Init(const std::string &FileName, int Number)
{
#ifdef DEF_CACHE
	bool OK = false;
	unsigned int i;
	for (i = 0; i < Sprite::Cache.size(); i++)
	{
		if ((Sprite::Cache[i]->Name == FileName) && (Sprite::Cache[i]->ID == Number))
		{
			printf("Cache load: %s\n", FileName.c_str());
			this->Name = Sprite::Cache[i]->Name;
			this->Image = Sprite::Cache[i]->Image;
			this->Priority = Sprite::Cache[i]->Priority;
			this->ID = Sprite::Cache[i]->ID;
			this->Locked = Sprite::Cache[i]->Locked;
			this->Transparent = Sprite::Cache[i]->Transparent;
			OK = true;
			break;
		}
	}
	if (OK)
		return true;
#endif

#ifndef DEF_CACHE
	if (!LoadFromFile(FileName, Number))
	{
		return false;
	}
#else
	setImage(0);
#endif

#ifdef DEF_CACHE
	if (!OK)
	{
		int lowest = INT_MAX;
		int lowest_id = -1;
		for (unsigned int i = 0; i < Sprite::Cache.size(); i++)
			if (!Sprite::Cache[i]->Locked)
			{
				lowest = lowest < Sprite::Cache[i]->Priority ? Sprite::Cache[i]->Priority : lowest;
				lowest_id = i;
			}

		this->ID = Number;
		this->Priority = 0;
		this->Name = FileName;
		printf("Cache add %s (lowest_id: %d)\n", FileName.c_str(), lowest_id);
		if (lowest_id > -1)
			Sprite::Cache[lowest_id] = this;
		else
			Sprite::Cache.push_back(this);
	}
#endif
	return true;
}

bool Sprite::Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int Frame)
{
#ifdef DEF_CACHE
	if (!SpriteSrc.Locked)
	{
		SpriteSrc.Locked = true;
		SpriteSrc.Priority = 0;
	}
	else
		SpriteSrc.Priority++;
	if (SpriteSrc.getImage() == 0)
	{
		if (!SpriteSrc.LoadFromFile(SpriteSrc.Name, SpriteSrc.ID))
			return false;
//		else
//			if (SpriteSrc.getTransparent())
//				SpriteSrc.SetColorKey();
	}
#endif
	return Surface::Draw(Dest, SpriteSrc.GetSurface(), X, Y, SpriteSrc.GetCord(Frame).X, SpriteSrc.GetCord(Frame).Y, SpriteSrc.GetCord(Frame).W, SpriteSrc.GetCord(Frame).H);
}

bool Sprite::Draw(SDL_Surface *Dest, Sprite &SpriteSrc, int X, int Y, int W, int H, int Frame)
{
#ifdef DEF_CACHE
	if (!SpriteSrc.Locked)
	{
		SpriteSrc.Locked = true;
		SpriteSrc.Priority = 0;
	}
	else
		SpriteSrc.Priority++;
	if (SpriteSrc.getImage() == 0)
	{
		if (!SpriteSrc.LoadFromFile(SpriteSrc.Name, SpriteSrc.ID))
			return false;
//		else
//			if (SpriteSrc.getTransparent())
//				SpriteSrc.SetColorKey();
	}
#endif
	return Surface::Draw(Dest, SpriteSrc.GetSurface(), X, Y, SpriteSrc.GetCord(Frame).X, SpriteSrc.GetCord(Frame).Y, W, H);
}

SDL_Surface *Sprite::GetSurface() const
{
	return Image;
}

Cord Sprite::GetCord(int Number) const
{
	if (!Cords.size())
	{
		Cord EmptyCord =
		{ 0, 0, 0, 0, 0, 0 };
		return EmptyCord;
	}
	else
		return Cords.at(Number);
}

int Sprite::GetTotalFrames() const
{
	return TotalFrames;
}

int Sprite::GetMaxFrameH() const
{
	return MaxFrameH;
}

inline bool Sprite::LoadFromFile(const std::string & FileName, int Number)
{
	FILE *pakFile;

	std::string path = "SPRITES/";

	path.append(FileName);

	int tmp, tmp2;

	int BitmapFileStartLoc;
	int BmpSize;
	char *BmpFile;

	pakFile = fopen(path.c_str(), "rb");

	if (pakFile == NULL)
	{
		printf("Unable to load: %s\n", path.c_str());
		return false;
	}

	fseek(pakFile, (24 + (Number * 8)), SEEK_SET);
	fread(&tmp, 1, 4, pakFile);

	fseek(pakFile, tmp + 100, SEEK_SET);
	fread(&TotalFrames, 1, 4, pakFile);

	Cords.resize(TotalFrames);

	for (int i = 0; i < TotalFrames; i++)
	{
		tmp2 = (tmp + 104 + (i * 12));
		fseek(pakFile, tmp2, SEEK_SET);
		fread(&Cords[i].X, 1, 2, pakFile);

		fseek(pakFile, tmp2 + 2, SEEK_SET);
		fread(&Cords[i].Y, 1, 2, pakFile);

		fseek(pakFile, tmp2 + 4, SEEK_SET);
		fread(&Cords[i].W, 1, 2, pakFile);

		fseek(pakFile, tmp2 + 6, SEEK_SET);
		fread(&Cords[i].H, 1, 2, pakFile);

		fseek(pakFile, tmp2 + 8, SEEK_SET);
		fread(&Cords[i].Vx, 1, 2, pakFile);

		fseek(pakFile, tmp2 + 10, SEEK_SET);
		fread(&Cords[i].Vy, 1, 2, pakFile);
	}

	int max = 0;
	for (int i = 0; i < TotalFrames; i++)
	{
		if (Cords[i].H > Cords[max].H)
			max = i;
	}
	MaxFrameH = Cords[max].H;

	BitmapFileStartLoc = tmp + (108 + (12 * TotalFrames));

	fseek(pakFile, BitmapFileStartLoc + 2, SEEK_SET);
	fread(&BmpSize, 1, 4, pakFile);

	fseek(pakFile, BitmapFileStartLoc, SEEK_SET);

	BmpFile = new char[BmpSize];

	fread(BmpFile, 1, BmpSize, pakFile);

	SDL_RWops *rw = SDL_RWFromMem(BmpFile, BmpSize);
	Image = SDL_LoadBMP_RW(rw, 1);

	delete[] BmpFile;

	fclose(pakFile);
/*#ifdef DEF_CACHE
	if (getTransparent())
	{
		printf("Restore color key (%s:%d)\n", Name.c_str(), Number);
		SetColorKey();
	}
#endif*/
	return true;
}

void Sprite::SetColorKey()
{
#ifdef DEF_CACHE
	if (Image == 0)
	{
		if (!LoadFromFile(Name, ID))
		{
			printf("SetColorKey(%s, %d) failed reload sprite.\n", Name.c_str(), ID);
			return;
		}
	}
	//setTransparent(true);
#endif
	SDL_Color color;
	Uint8 index;
	index = *((Uint8*) Image->pixels);
	color = Image->format->palette->colors[index];
	Surface::SetTransparent(Image, color.r, color.g, color.b);
}

Sprite::~Sprite()
{
	SDL_FreeSurface(Image);
}
#ifdef DEF_CACHE

void Sprite::ReleaseUnused()
{
	for (unsigned int i = 0; i < Sprite::Cache.size(); i++)
		if (!Sprite::Cache[i]->Locked)
		{
#ifdef DEBUG
			printf("Releasing: %s (ID: %d)\n", Sprite::Cache[i]->Name.c_str(), Sprite::Cache[i]->ID);
#endif
			SDL_FreeSurface(Sprite::Cache[i]->getImage());
			Sprite::Cache[i]->setImage(0);
		}
}
#endif
