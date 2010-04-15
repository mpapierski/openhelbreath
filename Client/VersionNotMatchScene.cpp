#include "Game.h"
#include "VersionNotMatchScene.h"

VersionNotMatchScene::VersionNotMatchScene()
{

}

VersionNotMatchScene::~VersionNotMatchScene()
{

}

void VersionNotMatchScene::Draw(SDL_Surface *Dest)
{
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_EXIT], 0, 0, SPRID_EXIT_BACKGROUND);
	Sprite::Draw(Dest, Game::GetInstance().Sprites[SPRID_GAMEDIALOG_3], 162, 125, 2);
	Font::PutAlignedText(Dest, 168, 160, 474 - 168, "Client program version does not match with server!", 0, 0, 0);
	Font::PutAlignedText(Dest, 168, 180, 474 - 168, "Download recent version and try again.", 0, 0, 0);
	Font::PutAlignedText(Dest, 168, 250, 474 - 168, MSG_HOMEPAGE, 0, 0, 0);
}

void VersionNotMatchScene::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	Game::GetInstance().OnQuit();
}

void VersionNotMatchScene::OnLButtonDown(int X, int Y)
{
	Game::GetInstance().OnQuit();
}

