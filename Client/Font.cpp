#include "Font.h"

CFont::CFont()
{
    Font = NULL;

    TextColor.r = 0;
    TextColor.g = 0;
    TextColor.b = 0;
}

bool CFont::OnLoad(const std::string &FileName, int Size )
{
    if(TTF_Init() == -1)
    {
        printf("Unable to init Font\n");
        return false;
    }
    if((Font = TTF_OpenFont(FileName.c_str(), Size)) == NULL )
    {
        printf("Unable to load: %s\n", FileName.c_str());
        return false;
    }

    return true;
}

void CFont::SetColor(int R, int G, int B)
{
    TextColor.r = R;
    TextColor.g = G;
    TextColor.b = B;
}

SDL_Surface *CFont::OnRender(const std::string &Text)
{
    SDL_Surface *Surf_Return = NULL;

    Surf_Return = TTF_RenderText_Solid( Font, Text.c_str(), TextColor);

    if(Surf_Return == NULL)
    {
        return NULL;
    }

    return Surf_Return;
}

void CFont::OnCleanup()
{
    TTF_CloseFont(Font);

    TTF_Quit();
}
