#include "Game.h"

PlayGroundScene::PlayGroundScene()
{
    monster_id = CREATURE_DEMON;
    orientation = CREATURE_ACTION_WALKING + ORIENTATION_LEFT;
}

PlayGroundScene::~PlayGroundScene()
{

}

void PlayGroundScene::onDraw(SDL_Surface* dest)
{
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = 640;
    r.h = 480;
    SDL_FillRect(dest, &r, 0);

    SpriteBank::manager.drawAnimatedCreature(dest, monster_id, orientation, 100, 150);
    currentPlayer.draw(dest, 200, 150);

    char txt[80];
    snprintf(txt, 80, "creature_id: %d orientation: %d", monster_id, orientation);
    Font::putTextShaded(dest, 0, 450, txt, Font::NORMAL, 255, 255, 255);

}

void PlayGroundScene::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
        case SDLK_ESCAPE:
            onExit();
            break;
        case SDLK_RIGHT:
            monster_id++;
            if(monster_id > 65) monster_id = 0;
            break;
        case SDLK_LEFT:
            monster_id--;
            if(monster_id < 0) monster_id = 65;
            break;
        case SDLK_UP:
            orientation++;
            if(orientation > 39) orientation = 0;
            break;
        case SDLK_DOWN:
            orientation--;
            if(orientation < 0) orientation = 39;
            break;
        case SDLK_1:
            if(currentPlayer.sex() == Player::MALE)
                currentPlayer.setSex(Player::FEMALE);
            else
                currentPlayer.setSex(Player::MALE);
            break;
        case SDLK_2:
            if(currentPlayer.race ()== Player::ASIAN) currentPlayer.setRace(Player::BLACK);
            else if(currentPlayer.race() == Player::BLACK) currentPlayer.setRace(Player::WHITE);
            else currentPlayer.setRace(Player::ASIAN);
            break;
        case SDLK_3:
            currentPlayer.setOrientation(currentPlayer.orientation() + 1);
            break;
        case SDLK_4:
            currentPlayer.setAction(currentPlayer.action() + 8);
            break;
        default:
            break;
    }
}

void PlayGroundScene::onExit()
{
    SoundBank::manager.play("E14");
    Game::getInstance().changeScene(new ExitScene);
}
