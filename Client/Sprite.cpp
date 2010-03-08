#include "Sprite.h"

CSprite::CSprite()
{
    Image = NULL;
}

CSprite::CSprite(const std::string &FileName, int Number)
{
    SetImage(FileName, Number);
}

bool CSprite::SetImage(const std::string &FileName, int Number)
{
    FILE *pakFile;
    int tmp, tmp2;
    int TotalFrame;
    int BitmapFileStartLoc;
    int BmpSize;
    char *BmpFile;

    pakFile = fopen(FileName.c_str(), "r+b");
    if(pakFile == NULL)
    {
        printf("Unable to load: %s\n", FileName.c_str());
        return false;
    }

    fseek(pakFile, (24+(Number*8)), SEEK_SET);
    fread(&tmp, 1, 4, pakFile);

    fseek(pakFile, tmp+100, SEEK_SET);
    fread(&TotalFrame, 1, 4, pakFile);

    Frame.resize(TotalFrame);

    for(int i = 0; i < TotalFrame; i++)
    {
        tmp2 = (tmp+104+(i*12));
        fseek(pakFile, tmp2, SEEK_SET);
        fread(&Frame[i].x, 1, 2, pakFile);

        fseek(pakFile, tmp2+2, SEEK_SET);
        fread(&Frame[i].y, 1, 2, pakFile);

        fseek(pakFile, tmp2+4, SEEK_SET);
        fread(&Frame[i].w, 1, 2, pakFile);

        fseek(pakFile, tmp2+6, SEEK_SET);
        fread(&Frame[i].h, 1, 2, pakFile);
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

SDL_Surface *CSprite::GetImage()
{
    if(Image == NULL)
    {
        return NULL;
    }
    return Image;
}

CSprite::~CSprite()
{
}
