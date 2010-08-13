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
    chest = PLAYER_EQUIPMENT_ELVINE_HERO_ROBE;
    feet = PLAYER_EQUIPMENT_UNEQUIPPED;
    cape = PLAYER_EQUIPMENT_UNEQUIPPED;
    head = PLAYER_EQUIPMENT_UNEQUIPPED;
    primary_weapon = PLAYER_EQUIPMENT_UNEQUIPPED;
    secondary_weapon = PLAYER_EQUIPMENT_UNEQUIPPED;

    // just for test
    hauberk = PLAYER_EQUIPMENT_ARESDEN_HERO_HAUBERK;
    leggings = PLAYER_EQUIPMENT_CHAIN_HOSE;
    chest = PLAYER_EQUIPMENT_ELVINE_HERO_ROBE;
    feet = PLAYER_EQUIPMENT_SHOES;
    //cape = PLAYER_EQUIPMENT_MANTLE;
    //head = PLAYER_EQUIPMENT_HORNS_HELM;
    primary_weapon = PLAYER_WEAPON_STORM_BRINGER;

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

void Player::drawWeapon(SDL_Surface* dest, int x, int y, int equip_id, int weaponFrameToShow)
{
    unsigned int offset = equip_id + _orientation;

    // weapon offsets are different for each type of weapon
    // hence the following code
    if(equip_id == PLAYER_WEAPON_DOUBLE_AXE
       || equip_id == PLAYER_WEAPON_WAR_AXE
       || equip_id == PLAYER_WEAPON_LIGHT_AXE
       || equip_id == PLAYER_WEAPON_TOMAHOC
       || equip_id == PLAYER_WEAPON_SAXON_AXE
       || equip_id == PLAYER_WEAPON_GOLDEN_AXE
       || equip_id == PLAYER_WEAPON_BATTLE_AXE
       || equip_id == PLAYER_WEAPON_DARK_EXECUTIONER
       || equip_id == PLAYER_WEAPON_LIGHTNING_BLADE
       || equip_id == PLAYER_WEAPON_BLACK_SHADOW_SWORD
       || equip_id == PLAYER_WEAPON_PICK_AXE
       || equip_id == PLAYER_WEAPON_STORM_BRINGER
       )
    {
        switch(_action)
        {
            case PLAYER_ACTION_STANDING_PEACE_MODE:
                offset += 0;
                break;
            case PLAYER_ACTION_STANDING_ATTACK_MODE:
                offset += 8;
                break;
            case PLAYER_ACTION_WALKING_PEACE_MODE:
                offset += 16;
                break;
            case PLAYER_ACTION_WALKING_ATTACK_MODE:
                offset += 24;
                break;
            case PLAYER_ACTION_RUNNING:
                offset += 48;
                break;
            case PLAYER_ACTION_BOW:
                return;
                break;
            case PLAYER_ACTION_ATTACKING:
                offset += 32;
                break;
            case PLAYER_ACTION_BOW_ATTACK:
                return;
                break;
            case PLAYER_ACTION_CASTING:
                return;
                break;
            case PLAYER_ACTION_PICKING_UP:
                return;
                break;
            case PLAYER_ACTION_TAKING_DAMAGE:
                offset += 40;
                break;
            case PLAYER_ACTION_DYING:
                return;
                break;
        }
    }
    //fprintf(stdout, "%d\r\n", offset);
    if(equip_id != PLAYER_EQUIPMENT_UNEQUIPPED)
    {
        if(_sex == MALE)
        {
            if(offset > SpriteBank::manager.male_weapons.size() - 1) return;
            SpriteBank::manager.drawSprite(dest, SpriteBank::manager.male_weapons.at(offset), weaponFrameToShow, x, y);
        }
        else
        {
            if(offset > SpriteBank::manager.female_weapons.size() - 1) return;
            SpriteBank::manager.drawSprite(dest, SpriteBank::manager.female_weapons.at(offset), weaponFrameToShow, x, y);
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

    if(_orientation == ORIENTATION_UP || _orientation == ORIENTATION_UP_RIGHT
             || _orientation == ORIENTATION_RIGHT || _orientation == ORIENTATION_LEFT_UP
             || _orientation == ORIENTATION_LEFT )
    {
        // draw before model
        drawEquipment(dest, x, y, cape, equipmentFrameToShow);
    }
    SpriteBank::manager.drawSprite(dest, SpriteBank::manager.players.at(player_sprite_id).at(player_animation_id), currentFrame, x, y);

    drawEquipment(dest, x, y, leggings, equipmentFrameToShow);
    drawEquipment(dest, x, y, feet, equipmentFrameToShow);
    drawEquipment(dest, x, y, hauberk, equipmentFrameToShow);
    drawEquipment(dest, x, y, chest, equipmentFrameToShow);
    drawEquipment(dest, x, y, head, equipmentFrameToShow);
    drawWeapon(dest, x, y, primary_weapon, currentFrame);

    if(_orientation == ORIENTATION_UP || _orientation == ORIENTATION_UP_RIGHT
             || _orientation == ORIENTATION_RIGHT || _orientation == ORIENTATION_LEFT_UP
             || _orientation == ORIENTATION_LEFT )
    {
        // draw after model
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
