//
// Player definition file. Initializes currentPlayer as main character. Can and should
// be used for displaying other player characters on screen
// TODO: there are some bugs in colorkey detection for capes (see aresden hero cape)
//
#include "Player.h"

Player::Player()
{
    _sex = FEMALE;
    _race = ASIAN;
    _orientation = ORIENTATION_UP;
    _action = PLAYER_ACTION_STANDING_PEACE_MODE;

    // initial equipment
    hauberk = PLAYER_EQUIPMENT_UNEQUIPPED;
    leggings = PLAYER_EQUIPMENT_UNEQUIPPED;
    chest = PLAYER_EQUIPMENT_UNEQUIPPED;
    feet = PLAYER_EQUIPMENT_UNEQUIPPED;
    cape = PLAYER_EQUIPMENT_UNEQUIPPED;

    // just for test
    hauberk = PLAYER_EQUIPMENT_ARESDEN_HERO_HAUBERK;
    leggings = PLAYER_EQUIPMENT_CHAIN_HOSE;
    //chest = PLAYER_EQUIPMENT_SANTA_COSTUME;
    feet = PLAYER_EQUIPMENT_SHOES;
    //cape = PLAYER_EQUIPMENT_MANTLE;

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

void Player::drawEquipment(SDL_Surface* dest, int x, int y, int equip_id, int equipmentFrameToShow)
{
    unsigned int offset = equip_id + _action / 8;
    if(equip_id != PLAYER_EQUIPMENT_UNEQUIPPED)
    {
        if(_sex == MALE)
        {
            if(offset > SpriteBank::manager.male_equipment.size() - 1) return;
            SpriteBank::manager.drawSprite(dest, SpriteBank::manager.male_equipment.at(offset), equipmentFrameToShow, x, y);
        }
        else
        {
            if(offset > SpriteBank::manager.female_equipment.size() - 1) return;
            SpriteBank::manager.drawSprite(dest, SpriteBank::manager.female_equipment.at(offset), equipmentFrameToShow, x, y);
        }
    }
}

void Player::draw(SDL_Surface* dest, int x, int y)
{
    // TODO: optimize to draw on separate surface, then just blip to screen

    if(player_sprite_id > SpriteBank::manager.players.size() - 1) return;
    if(player_animation_id > SpriteBank::manager.players.at(player_sprite_id).size() - 1) return;

    if(playerTimer.getTicks() > 100)
    {
        currentFrame++;
        if (currentFrame >= framesCount) currentFrame = 0;

        playerTimer.start();
    }

    unsigned int equipmentFrameToShow = _orientation * framesCount + currentFrame;

    if(cape != PLAYER_EQUIPMENT_UNEQUIPPED &&
        (_orientation == ORIENTATION_DOWN || _orientation == ORIENTATION_RIGHT_DOWN
         || _orientation == ORIENTATION_DOWN_LEFT
         )
       )
    {
        // draw cape before model
        drawEquipment(dest, x, y, cape, equipmentFrameToShow);
    }
    SpriteBank::manager.drawSprite(dest, SpriteBank::manager.players.at(player_sprite_id).at(player_animation_id), currentFrame, x, y);

    drawEquipment(dest, x, y, leggings, equipmentFrameToShow);
    drawEquipment(dest, x, y, feet, equipmentFrameToShow);
    drawEquipment(dest, x, y, hauberk, equipmentFrameToShow);
    drawEquipment(dest, x, y, chest, equipmentFrameToShow);

    if(cape != PLAYER_EQUIPMENT_UNEQUIPPED &&
            (_orientation == ORIENTATION_UP || _orientation == ORIENTATION_UP_RIGHT
             || _orientation == ORIENTATION_RIGHT || _orientation == ORIENTATION_LEFT_UP
             || _orientation == ORIENTATION_LEFT
            )
       )
    {
        // draw cape after model
        drawEquipment(dest, x, y, cape, equipmentFrameToShow);
    }

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
