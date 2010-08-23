//
//  Game initialization
//  Loads sprites, maps, sounds, effects
//  TODO: add check if some resources fail
//

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
    // TODO: paks left to load
    // ACannon.pak - Cannon Guard Tower - 32 sprites inside
    // CBTurret.pak - Arrow Guard Tower - 32 sprites inside
    // CruEffect1.pak - crusade effects
    // CruObj1.pak - warehouse?
    // Devlin.pak - devlin npc - 16 sprites inside
    // EFFECT.pak - effects
    // EFFECT2.pak - effects
    // EFFECT3.pak - effects
    // effect4.pak - effects
    // effect5.pak - effects
    // effect6.pak - effects
    // Effect7.pak - effects
    // Effect8.pak - effects
    // effect9.pak - effects
    // effect10.pak - effects
    // Effect11.pak - effects
    // effect11s.pak - effects
    // Effect12.pak - effects
    // Effect13.pak - effects
    // effect14.pak - effects
    // effect15.pak - effects
    // face.pack - ???
    // FireWyvern.pak - Fire Wyvern - 24 sprites inside
    // Gail.pak - gail npc - 8 sprites inside
    // Gandlf.pak - gandalf npc - 8 sprites inside
    // Gate.pak - gate some broken images inside?
    // HBTank.pak - heavy battle tank - 32 sprites inside
    // Howard.pak - howard npc - 8 sprites inside
    // item-dynamic.pak - fishes
    // item-ground.pak - items on ground
    // item-pack.pak - items in backpack
    // Kennedy.pak - kennedy npc - 8 sprites inside
    // maptiles.pak
    // maptiles2.pak
    // maptiles3.pak - holy sh*t that must be implemented!!!
    // maptiles4.pak
    // maptiles5.pak
    // maptiles6.pak
    // maptiles353-361.pak
    // McGaffin.pak - mcgaffin npc - 8 sprites inside
    // Mhr.pak - ???
    // monster.pak - minimap monsters
    // MPTWK.pak
    // Msh.pak - shields
    // Msw.pak - swords
    // Msw2.pak - swords
    // Msw3.pak - swords
    // newmaps.pak
    // Objects1.pak
    // Objects2.pak
    // Objects3.pak
    // Objects4.pak
    // Objects5.pak
    // Objects6.pak
    // Objects7.pak
    // Perry.pak - perry npc - 8 sprites inside
    // SHOPKPR.pak - shopkeeper - 8 sprites inside
    // Sinside1.pak
    // Tile223-225.pak
    // Tile226-229.pak
    // Tile363-366.pak
    // Tile367-367.pak
    // Tile370-381.pak
    // Tile382-387.pak
    // Tile388-402.pak
    // Tile403-405.pak
    // Tile406-421.pak
    // Tile422-429.pak
    // Tile430-443.pak
    // Tile444-444.pak
    // Tile445-461.pak
    // Tile462-464.pak
    // Tile462-473.pak
    // Tile462-475.pak
    // Tile474-478.pak
    // Tile474-488.pak
    // Tile479-488.pak
    // Tile489-522.pak
    // Tile523-530.pak
    // Tile523-532.pak - empty ?
    // Tile531-540.pak
    // Tile541-545.pak
    // Structures1.pak
    // Telescope.pak
    // Telescope2.pak
    // Tom.pak - npc tom - 8 sprites
    // TREES1.pak
    // TreeShadows.pak
    // TutelarAngel1.pak
    // TutelarAngel2.pak
    // TutelarAngel3.pak
    // TutelarAngel4.pak
    // yspro.pak - abbaddon - 32 sprites
    // Wbo.pak
    // Whr.pak
    // William.pak - william npc - 8 sprites
    // Wsh.pak
    // Wsw.pak
    // Wsw2.pak
    // Wsw3.pak
    // Wyvern.pak - 24 sprites
    // yseffect2.pak
    // yseffect3.pak
    // yseffect4.pak

    // EQUIPMENT


    // some animation bugs? or different method to display them?
    // NMHelm1.pak - 12 sprites inside
    // NWHelm1.pak - 12 sprites inside
    // NMHelm2.pak - 12 sprites inside
    // NWHelm2.pak - 12 sprites inside
    // NMHelm3.pak - 12 sprites inside
    // NWHelm3.pak - 12 sprites inside

    // NMHelm4.pak - 12 sprites inside
    // NWHelm4.pak - 12 sprites inside


    // MLeggings.pak - 12 sprites inside
    // WLeggings.pak - 12 sprites inside

    // MHCap1.pak - 12 sprites inside
    // MHCap2.pak - 12 sprites inside

    // MCMail.pak - 12 sprites inside
    // MLarmor.pak - 12 sprites inside


    // MHelm1.pak - 12 sprites inside
    // MHelm2.pak - 12 sprites inside
    // MHelm3.pak - 11 sprites inside !!!!!
    // MHelm4.pak - 12 sprites inside


    // MHHelm1.pak - 12 sprites inside
    // MHHelm2.pak - 12 sprites inside
    // MTrouser.pak - 12 sprites inside
    // MTunic.pak - 12 sprites inside
    // MPMail.pak - 12 sprites inside
    // Mrobe1.pak - 12 sprites inside
    // MShirt.pak - 12 sprites inside
    // MSMail.pak - 12 sprites inside
    // WBodice1.pak - 12 sprites inside
    // WBodice2.pak - 12 sprites inside
    // WChemiss.pak - 12 sprites inside
    // WCMail.pak - 12 sprites inside
    // WHCap1.pak - 12 sprites inside
    // WHCap2.pak - 12 sprites inside
    // WHHelm1.pak - 12 sprites inside
    // WHHelm2.pak - 12 sprites inside
    // WHoe.pak - 12 sprites inside
    // WHelm4.pak - 12 sprites inside
    // WLarmor.pak - 12 sprites inside
    // WPMail.pak - 12 sprites inside
    // WRobe1.pak - 12 sprites inside
    // WShirt.pak - 12 sprites inside
    // WSkirt.pak - 12 sprites inside
    // WSMail.pak - 12 sprites inside
    // WTrouser.pak - 12 sprites inside

    // WEAPONS

    // MStaff1.pak - 56 sprites inside
    // MStaff2.pak - 56 sprites inside
    // MStaff3.pak - 56 sprites inside
    // MStaff4.pak - 56 sprites inside
    // WStaff1.pak - 56 sprites inside
    // WStaff2.pak - 56 sprites inside
    // WStaff3.pak - 56 sprites inside
    // WStaff4.pak - 56 sprites inside

    // MDirectBow.pak - 56 sprites inside
    // MFireBow.pak - 56 sprites inside
    // MHammer.pak - 56 sprites inside
    // MBabHammer.pak - 56 sprites inside
    // MBerserkWand.pak - 56 sprites inside
    // MBHammer.pak - 56 sprites inside
    // Mbo.pak - 112 sprites inside
    // MDebastator.pak - 56 sprites inside
    // MKlonessAxe.pak - 56 sprites inside
    // MKlonessBlade.pak - 56 sprites inside
    // MKlonessWand.pak - 56 sprites inside
    // MHoe.pak - 56 sprites inside
    // MKlonessAstock.pak - 56 sprites inside
    // Mswx.pak - 56 sprites inside
    // MReMagicWand.pak - 56 sprites inside
    // MStaff2222.pak - 56 sprites inside
    // WBabHammer.pak - 56 sprites inside
    // WBerserkWand.pak - 56 sprites inside
    // WBHammer.pak - 56 sprites inside
    // WDebastator.pak - 56 sprites inside
    // WDirectBow.pak - 56 sprites inside
    // WFireBow.pak - FUU
    // WHammer.pak - 56 sprites inside
    // WKlonessAstock.pak - 56 sprites inside
    // WKlonessAxe.pak - 56 sprites inside
    // WKlonessBlade.pak - 56 sprites inside
    // WKlonessWand.pak - 56 sprites inside
    // WReMagicWand.pak - 56 sprites inside
    // Wswx.pak - 56 sprites inside

    switch(percent)
    {
        case 0:
            SpriteBank::manager.load("GameDialog");
            SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).setColorKey();
            SpriteBank::manager.load("item-equipM");
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_M_MODELS).setColorKey();
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_M_UNDERWEAR).setColorKey();
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_M_HAIR_STYLES).setColorKey();
            SpriteBank::manager.load("item-equipW");
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_W_MODELS).setColorKey();
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_W_UNDERWEAR).setColorKey();
            SpriteBank::manager.getSprite(SPRID_ITEM_EQUIP_W_HAIR_STYLES).setColorKey();
            break;
        case 1:
            // monsters
            fprintf(stdout, "Loading creature sprites\r\n");

            SpriteBank::manager.loadCreatureSprites("ABS");
            SpriteBank::manager.loadCreatureSprites("DarkElf");
            SpriteBank::manager.loadCreatureSprites("Cyc");
            SpriteBank::manager.loadCreatureSprites("Ant");
            SpriteBank::manager.loadCreatureSprites("Demon");
            SpriteBank::manager.loadCreatureSprites("Beholder");
            SpriteBank::manager.loadCreatureSprites("BG");
            SpriteBank::manager.loadCreatureSprites("Amp");
            SpriteBank::manager.loadCreatureSprites("Babarian");
            SpriteBank::manager.loadCreatureSprites("Barlog");
            SpriteBank::manager.loadCreatureSprites("Bunny");
            SpriteBank::manager.loadCreatureSprites("CanPlant");
            SpriteBank::manager.loadCreatureSprites("Cat");
            SpriteBank::manager.loadCreatureSprites("Catapult");
            SpriteBank::manager.loadCreatureSprites("Centaurus");
            SpriteBank::manager.loadCreatureSprites("Cla");
            SpriteBank::manager.loadCreatureSprites("Clawturtle");
            SpriteBank::manager.loadCreatureSprites("Crop");
            SpriteBank::manager.loadCreatureSprites("DarkKnight");
            SpriteBank::manager.loadCreatureSprites("Detector");
            SpriteBank::manager.loadCreatureSprites("DireBoar");
            SpriteBank::manager.loadCreatureSprites("dummy");
            SpriteBank::manager.loadCreatureSprites("ElfMaster");
            SpriteBank::manager.loadCreatureSprites("ESG");
            SpriteBank::manager.loadCreatureSprites("Ettin");
            SpriteBank::manager.loadCreatureSprites("FireWyvern");
            SpriteBank::manager.loadCreatureSprites("frost");
            SpriteBank::manager.loadCreatureSprites("gagoyle");
            SpriteBank::manager.loadCreatureSprites("GHK");
            SpriteBank::manager.loadCreatureSprites("GHKABS");
            SpriteBank::manager.loadCreatureSprites("GiantCrayfish");
            SpriteBank::manager.loadCreatureSprites("GiantFrog");
            SpriteBank::manager.loadCreatureSprites("GiantLizard");
            SpriteBank::manager.loadCreatureSprites("GiantPlant");
            break;
        case 25:
            SpriteBank::manager.loadCreatureSprites("GMG");
            SpriteBank::manager.loadCreatureSprites("GOL");
            SpriteBank::manager.loadCreatureSprites("GT-Arrow");
            SpriteBank::manager.loadCreatureSprites("GT-Cannon");
            SpriteBank::manager.loadCreatureSprites("Guard");
            SpriteBank::manager.loadCreatureSprites("Helb");
            SpriteBank::manager.loadCreatureSprites("Hellclaw");
            SpriteBank::manager.loadCreatureSprites("IceGolem");
            SpriteBank::manager.loadCreatureSprites("Liche");
            SpriteBank::manager.loadCreatureSprites("LWB");
            SpriteBank::manager.loadCreatureSprites("ManaCollector");
            SpriteBank::manager.loadCreatureSprites("ManaStone");
            SpriteBank::manager.loadCreatureSprites("MasterMageOrc");
            SpriteBank::manager.loadCreatureSprites("Minotaurs");
            SpriteBank::manager.loadCreatureSprites("MTGiant");
            SpriteBank::manager.loadCreatureSprites("Orc");
            SpriteBank::manager.loadCreatureSprites("Orge");
            SpriteBank::manager.loadCreatureSprites("Nizie");
            SpriteBank::manager.loadCreatureSprites("Rudolph");
            SpriteBank::manager.loadCreatureSprites("Scp");
            SpriteBank::manager.loadCreatureSprites("SKE");
            SpriteBank::manager.loadCreatureSprites("SLM");
            SpriteBank::manager.loadCreatureSprites("Sorceress");
            SpriteBank::manager.loadCreatureSprites("Stalker");
            SpriteBank::manager.loadCreatureSprites("Tentocle");
            SpriteBank::manager.loadCreatureSprites("Tigerworm");
            SpriteBank::manager.loadCreatureSprites("Unicorn");
            SpriteBank::manager.loadCreatureSprites("TK");
            SpriteBank::manager.loadCreatureSprites("TPKnight");
            SpriteBank::manager.loadCreatureSprites("Troll");
            SpriteBank::manager.loadCreatureSprites("Zom");
            SpriteBank::manager.loadCreatureSprites("WereWolf");
            // TODO: This one fails to load. Figure out why
            //SpriteBank::manager.loadCreatureSprites("Scarecrow");
            break;
        case 50:
            // players
            fprintf(stdout, "Loading player sprites\r\n");

            SpriteBank::manager.loadPlayerSprites("Bm");
            SpriteBank::manager.loadPlayerSprites("Bw");
            SpriteBank::manager.loadPlayerSprites("Wm");
            SpriteBank::manager.loadPlayerSprites("Ww");
            SpriteBank::manager.loadPlayerSprites("Ym");
            SpriteBank::manager.loadPlayerSprites("Yw");

            // player equipment
            fprintf(stdout, "Loading player equipment sprites\r\n");
            SpriteBank::manager.loadPlayerEquipment("Mhr", "Whr");
            SpriteBank::manager.loadPlayerEquipment("Mpt", "Wpt");
            SpriteBank::manager.loadPlayerEquipment("MHauberk", "WHauberk");
            SpriteBank::manager.loadPlayerEquipment("MHHauberk1", "WHHauberk1");
            SpriteBank::manager.loadPlayerEquipment("MHHauberk2", "WHHauberk2");
            SpriteBank::manager.loadPlayerEquipment("MHLeggings1", "WHLeggings1");
            SpriteBank::manager.loadPlayerEquipment("MHLeggings2", "WHLeggings2");
            SpriteBank::manager.loadPlayerEquipment("MHTrouser", "WHTrouser");
            SpriteBank::manager.loadPlayerEquipment("MSanta", "WSanta");
            SpriteBank::manager.loadPlayerEquipment("MLBoots", "WLBoots");
            SpriteBank::manager.loadPlayerEquipment("MShoes", "WShoes");
            SpriteBank::manager.loadPlayerEquipment("Mmantle01", "Wmantle01");
            SpriteBank::manager.loadPlayerEquipment("Mmantle02", "Wmantle02");
            SpriteBank::manager.loadPlayerEquipment("Mmantle03", "Wmantle03");
            SpriteBank::manager.loadPlayerEquipment("Mmantle04", "Wmantle04");
            SpriteBank::manager.loadPlayerEquipment("Mmantle05", "Wmantle05");
            SpriteBank::manager.loadPlayerEquipment("Mmantle06", "Wmantle06");
            SpriteBank::manager.loadPlayerEquipment("MCHoses", "WCHoses");
            SpriteBank::manager.loadPlayerEquipment("MHPMail1", "WHPMail1");
            SpriteBank::manager.loadPlayerEquipment("MHPMail2", "WHPMail2");
            SpriteBank::manager.loadPlayerEquipment("MHRobe1", "WHRobe1");
            SpriteBank::manager.loadPlayerEquipment("MHRobe2", "WHRobe2");

            // player weapons
            fprintf(stdout, "Loading player weapon sprites\r\n");
            SpriteBank::manager.loadPlayerWeapons("MAxe1", "WAxe1");
            SpriteBank::manager.loadPlayerWeapons("MAxe2", "WAxe2");
            SpriteBank::manager.loadPlayerWeapons("MAxe3", "WAxe3");
            // TODO: this one has wrong color key
            SpriteBank::manager.loadPlayerWeapons("MAxe4", "WAxe4");
            SpriteBank::manager.loadPlayerWeapons("MAxe5", "WAxe5");
            SpriteBank::manager.loadPlayerWeapons("MAxe6", "WAxe6");
            SpriteBank::manager.loadPlayerWeapons("MDarkExec", "WDarkExec");
            SpriteBank::manager.loadPlayerWeapons("MLightBlade", "WLightBlade");
            SpriteBank::manager.loadPlayerWeapons("MBShadowSword", "WBShadowSword");
            // TODO: this one has wrong color key
            SpriteBank::manager.loadPlayerWeapons("MPickAxe1", "WPickAxe1");
            SpriteBank::manager.loadPlayerWeapons("MStormBringer", "WStormbringer");
        break;
    case 73:
        {MapBank maps;
        maps.loadMap("ARESDEN");
        maps.loadMap("ELVINE");
        if (maps.loadMap("middleland"))
        {
                Debug() << "OK";
                Debug() << "W" << maps.getMap("middleland").getSizeX();
                Debug() << "H" << maps.getMap("middleland").getSizeY();
        }
        else
                Debug() << "middleland loanding fail";
        }
    	break;

    case 100:
            Game::getInstance().changeScene(new MenuScene);
            Game::getInstance().mouseCursor.setCursorStyle(Mouse::ARROW);
            break;
    }

    if (percent <= 100) percent++;
}

void LoadingScene::onDraw(SDL_Surface* dest)
{
    SpriteBank::manager.draw(dest, 1, 1, SPRID_NEWDIALOG_LOADING, 0);
    SpriteBank::manager.draw(dest, 473, 443, percent+17, 17, SPRID_NEWDIALOG_LOADING, 1);
}
