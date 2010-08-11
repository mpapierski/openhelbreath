//
// Player definition file. Initializes currentPlayer as main character. Can and should
// be used for displaying other player characters on screen
//
#include "Player.h"

Player::Player()
{
    _sex = FEMALE;
    _race = ASIAN;
    _orientation = ORIENTATION_DOWN;
    _action = PLAYER_ACTION_STANDING_PEACE_MODE;
    hauberk = PLAYER_EQUIPMENT_HAUBERK;

    framesCount = 0;
    resetTimerAndFrames();
}

void Player::resetTimerAndFrames()
{
    if(_sex == MALE)
    {
        if(_race == ASIAN) player_sprite_id = PLAYER_YELLOW_MALE;
        else if(_race == BLACK) player_sprite_id = PLAYER_BLACK_MALE;
        else player_sprite_id = PLAYER_WHITE_MALE;
    }
    else
    {
        if(_race == ASIAN) player_sprite_id = PLAYER_YELLOW_FEMALE;
        else if(_race == BLACK) player_sprite_id = PLAYER_BLACK_FEMALE;
        else player_sprite_id = PLAYER_WHITE_FEMALE;
    }

    if(!playerTimer.isStarted()) playerTimer.start();
    currentFrame = 0;

    player_animation_id = _action + _orientation;
    if(player_animation_id <= SpriteBank::manager.players.at(player_sprite_id).size() - 1) framesCount = SpriteBank::manager.players.at(player_sprite_id).at(player_animation_id).getFramesCount();
}

void Player::draw(SDL_Surface* dest, int x, int y)
{
    if(player_sprite_id > SpriteBank::manager.players.size() - 1) return;
    if(player_animation_id > SpriteBank::manager.players.at(player_sprite_id).size() - 1) return;

    if(playerTimer.getTicks() > 100)
    {
        currentFrame++;
        if (currentFrame >= framesCount) currentFrame = 0;

        playerTimer.start();
    }

    SpriteBank::manager.drawSprite(dest, SpriteBank::manager.players.at(player_sprite_id).at(player_animation_id), currentFrame, x, y);

    /*

    // draw hauberk
    if(player.hauberk != PLAYER_EQUIPMENT_HAUBERK_NONE)
    {
        int offset = player.hauberk + player.action / 8;
        if(player.sex == Player::MALE)
        {
            //male_equipment[offset].update(player.orientation * 8, player.orientation * 8 + 8);
            //drawAnimatedSprite(dest, male_equipment.at(offset), x, y);
        }
        else
        {
            //female_equipment[offset].update(player.orientation * 8, player.orientation * 8 + 8);
            //drawAnimatedSprite(dest, female_equipment.at(offset), x, y);
        }
    }    */

}

int Player::action()
{
    return _action;
}

void Player::setAction(int a)
{
    _action = a;
    if(_action < 0 || _action > PLAYER_ACTION_DYING) _action = 0;

    resetTimerAndFrames();
}


int Player::orientation()
{
    return _orientation;
}

void Player::setOrientation(int o)
{
    _orientation = o;
    if(_orientation < 0) _orientation = 7;
    else if(_orientation > 7) _orientation = 0;

    resetTimerAndFrames();
}

Player::Sex Player::sex()
{
    return _sex;
}
void Player::setSex(Sex s)
{
    _sex = s;

    resetTimerAndFrames();
}
Player::Race Player::race()
{
    return _race;
}

void Player::setRace(Race r)
{
    _race = r;

    resetTimerAndFrames();
}
