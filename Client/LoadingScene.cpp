#include "Game.h"

LoadingScene::LoadingScene()
{
	percent = 0;
}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::onLoop()
{
	switch(percent)
	{
		case 0:
			SpriteBank::manager.load("GameDialog");
			SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).setColorKey();
			SpriteBank::manager.load("item-equipM");
			SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_M_MODELS).setColorKey();
			SpriteBank::manager.load("item-equipW");
			SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_W_MODELS).setColorKey();
			break;
		case 100:
			Game::getInstance().changeScene(new MenuScene);
			break;
	}

	if (percent <= 100)
	{
		percent++;
	}
}

void LoadingScene::onDraw(SDL_Surface* dest)
{
	SpriteBank::manager.draw(dest, 1, 1, SPRID_NEWDIALOG_LOADING, 0);
	SpriteBank::manager.draw(dest, 473, 443, percent+17, 17, SPRID_NEWDIALOG_LOADING, 1);
}
