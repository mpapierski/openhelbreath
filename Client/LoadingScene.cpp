//
//  Game initialization
//  Loads sprites, maps, sounds
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
    // item-equipM.pak - m items in character screen
    // item-equipW.pak - w items in character screen
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
    // Mpt.pak
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
    // Wpt.pak
    // Wsh.pak
    // Wsw.pak
    // Wsw2.pak
    // Wsw3.pak
    // Wyvern.pak - 24 sprites
    // yseffect2.pak
    // yseffect3.pak
    // yseffect4.pak

    // EQUIPMENT

    // MHCap1.pak - 12 sprites inside
    // MHCap2.pak - 12 sprites inside
    // MCHoses.pak - 12 sprites inside
    // MCMail.pak - 12 sprites inside
    // MLarmor.pak - 12 sprites inside
    // MLBoots.pak - 12 sprites inside
    // MLeggings.pak - 12 sprites inside
    // MHelm1.pak - 12 sprites inside
    // MHelm2.pak - 12 sprites inside
    // MHelm3.pak - 11 sprites inside !!!!!
    // MHelm4.pak - 12 sprites inside
    // MHHauberk1.pak - 12 sprites inside
    // MHHauberk2.pak - 12 sprites inside
    // MHHelm1.pak - 12 sprites inside
    // MHHelm2.pak - 12 sprites inside
    // MHLeggings1.pak - 12 sprites inside
    // MHLeggings2.pak - 12 sprites inside
    // MHPMail1.pak - 12 sprites inside
    // MHPMail2.pak - 12 sprites inside
    // MHRobe1.pak - 12 sprites inside
    // MHRobe2.pak - 12 sprites inside
    // MHTrouser.pak - 12 sprites inside
    // MTrouser.pak - 12 sprites inside
    // MTunic.pak - 12 sprites inside
    // Mmantle01.pak - 12 sprites inside
    // Mmantle02.pak - 12 sprites inside
    // Mmantle03.pak - 12 sprites inside
    // Mmantle04.pak - 12 sprites inside
    // Mmantle05.pak - 12 sprites inside
    // Mmantle06.pak - 12 sprites inside
    // MPMail.pak - 12 sprites inside
    // Mrobe1.pak - 12 sprites inside
    // MSanta.pak - 12 sprites inside
    // MShirt.pak - 12 sprites inside
    // MShoes.pak - 12 sprites inside
    // MSMail.pak - 12 sprites inside
    // NMHelm1.pak - 12 sprites inside
    // NMHelm2.pak - 12 sprites inside
    // NMHelm3.pak - 12 sprites inside
    // NMHelm4.pak - 12 sprites inside
    // NWHelm1.pak - 12 sprites inside
    // NWHelm2.pak - 12 sprites inside
    // NWHelm3.pak - 12 sprites inside
    // NWHelm4.pak - 12 sprites inside
    // WBodice1.pak - 12 sprites inside
    // WBodice2.pak - 12 sprites inside
    // WChemiss.pak - 12 sprites inside
    // WCHoses.pak - 12 sprites inside
    // WCMail.pak - 12 sprites inside
    // WHHauberk1.pak - 12 sprites inside
    // WHHauberk2.pak - 12 sprites inside
    // WHCap1.pak - 12 sprites inside
    // WHCap2.pak - 12 sprites inside
    // WHHelm1.pak - 12 sprites inside
    // WHHelm2.pak - 12 sprites inside
    // WHLeggings1.pak - 12 sprites inside
    // WHLeggings2.pak - 12 sprites inside
    // WHoe.pak - 12 sprites inside
    // WHelm4.pak - 12 sprites inside
    // WHPMail1.pak - 12 sprites inside
    // WHPMail2.pak - 12 sprites inside
    // WHRobe1.pak - 12 sprites inside
    // WHRobe2.pak - 12 sprites inside
    // WHTrouser.pak - 12 sprites inside
    // WLarmor.pak - 12 sprites inside
    // WLBoots.pak - 12 sprites inside
    // WLeggings.pak - 12 sprites inside
    // Wmantle01.pak - 12 sprites inside
    // Wmantle02.pak - 12 sprites inside
    // Wmantle03.pak - 12 sprites inside
    // Wmantle04.pak - 12 sprites inside
    // Wmantle05.pak - 12 sprites inside
    // Wmantle06.pak - 12 sprites inside
    // WPMail.pak - 12 sprites inside
    // WRobe1.pak - 12 sprites inside
    // WSanta.pak - 12 sprites inside
    // WShirt.pak - 12 sprites inside
    // WShoes.pak - 12 sprites inside
    // WSkirt.pak - 12 sprites inside
    // WSMail.pak - 12 sprites inside
    // WTrouser.pak - 12 sprites inside

    // WEAPONS

    // MAxe1.pak - 56 sprites inside
    // MAxe2.pak - 56 sprites inside
    // Maxe3.pak - 56 sprites inside
    // Maxe4.pak - 56 sprites inside
    // Maxe5.pak - 56 sprites inside
    // Maxe6.pak - 56 sprites inside
    // MDirectBow.pak - 56 sprites inside
    // MFireBow.pak - 56 sprites inside
    // STOP! HAMMERTIME!
    // MHammer.pak - 56 sprites inside
    // MBabHammer.pak - 56 sprites inside
    // MBerserkWand.pak - 56 sprites inside
    // MBHammer.pak - 56 sprites inside
    // Mbo.pak - 112 sprites inside
    // MBShadowSword.pak - 56 sprites inside
    // MDarkExec.pak - 56 sprites inside
    // MDebastator.pak - 56 sprites inside
    // MKlonessAxe.pak - 56 sprites inside
    // MKlonessBlade.pak - 56 sprites inside
    // MKlonessWand.pak - 56 sprites inside
    // MLightBlade.pak - 56 sprites inside
    // MHoe.pak - 56 sprites inside
    // MKlonessAstock.pak - 56 sprites inside
    // Mswx.pak - 56 sprites inside
    // MPickAxe1.pak - 56 sprites inside
    // MReMagicWand.pak - 56 sprites inside
    // MStaff1.pak - 56 sprites inside
    // MStaff2.pak - 56 sprites inside
    // MStaff3.pak - 56 sprites inside
    // MStaff4.pak - 56 sprites inside
    // MStaff2222.pak - 56 sprites inside
    // MStormBringer.pak - 56 sprites inside
    // WAxe1.pak - 56 sprites inside
    // WAxe2.pak - 56 sprites inside
    // WAxe3.pak - 56 sprites inside
    // WAxe4.pak - 56 sprites inside
    // WAxe5.pak - 56 sprites inside
    // WAxe6.pak - 56 sprites inside
    // WBabHammer.pak - 56 sprites inside
    // WBerserkWand.pak - 56 sprites inside
    // WBHammer.pak - 56 sprites inside
    // WBShadowSword.pak - 56 sprites inside
    // WDarkExec.pak - 56 sprites inside
    // WDebastator.pak - 56 sprites inside
    // WDirectBow.pak - 56 sprites inside
    // WFireBow.pak - FUU
    // WHammer.pak - 56 sprites inside
    // WKlonessAstock.pak - 56 sprites inside
    // WKlonessAxe.pak - 56 sprites inside
    // WKlonessBlade.pak - 56 sprites inside
    // WKlonessWand.pak - 56 sprites inside
    // WLightBlade.pak - 56 sprites inside
    // WPickAxe1.pak - 56 sprites inside
    // WReMagicWand.pak - 56 sprites inside
    // WStaff1.pak - 56 sprites inside
    // WStaff2.pak - 56 sprites inside
    // WStaff3.pak - 56 sprites inside
    // WStaff4.pak - 56 sprites inside
    // WStormbringer.pak - 56 sprites inside
    // Wswx.pak - 56 sprites inside

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
        case 1:
            SpriteBank::manager.loadCreatureSprites("ABS");
            break;
    case 2:
        SpriteBank::manager.loadCreatureSprites("DarkElf");
        break;
    case 3:
        SpriteBank::manager.loadCreatureSprites("Cyc");
        break;
    case 4:
        SpriteBank::manager.loadCreatureSprites("Ant");
        break;
    case 5:
        SpriteBank::manager.loadCreatureSprites("Demon");
        break;
    case 6:
        SpriteBank::manager.loadCreatureSprites("Beholder");
        break;
    case 7:
        SpriteBank::manager.loadCreatureSprites("BG");
        break;
    case 8:
        SpriteBank::manager.loadCreatureSprites("Amp");
        break;
    case 9:
        SpriteBank::manager.loadCreatureSprites("Babarian");
        break;
    case 10:
        SpriteBank::manager.loadCreatureSprites("Barlog");
        break;
    case 11:
        SpriteBank::manager.loadCreatureSprites("Bunny");
        break;
    case 12:
        SpriteBank::manager.loadCreatureSprites("CanPlant");
        break;
    case 13:
        SpriteBank::manager.loadCreatureSprites("Cat");
        break;
    case 14:
        SpriteBank::manager.loadCreatureSprites("Catapult");
        break;
    case 15:
        SpriteBank::manager.loadCreatureSprites("Centaurus");
        break;
    case 16:
        SpriteBank::manager.loadCreatureSprites("Cla");
        break;
    case 17:
        SpriteBank::manager.loadCreatureSprites("Clawturtle");
        break;
    case 18:
        SpriteBank::manager.loadCreatureSprites("Crop");
        break;
    case 19:
        SpriteBank::manager.loadCreatureSprites("DarkKnight");
        break;
    case 20:
        SpriteBank::manager.loadCreatureSprites("Detector");
        break;
    case 21:
        SpriteBank::manager.loadCreatureSprites("Direboar");
        break;
    case 22:
        SpriteBank::manager.loadCreatureSprites("dummy");
        break;
    case 23:
        SpriteBank::manager.loadCreatureSprites("ElfMaster");
        break;
    case 24:
        SpriteBank::manager.loadCreatureSprites("ESG");
        break;
    case 25:
        SpriteBank::manager.loadCreatureSprites("Ettin");
        break;
    case 26:
        SpriteBank::manager.loadCreatureSprites("Frost");
        break;
    case 27:
        SpriteBank::manager.loadCreatureSprites("gagoyle");
        break;
    case 28:
        SpriteBank::manager.loadCreatureSprites("GHK");
        break;
    case 29:
        SpriteBank::manager.loadCreatureSprites("GHKABS");
        break;
    case 30:
        SpriteBank::manager.loadCreatureSprites("GiantCrayfish");
        break;
    case 31:
        SpriteBank::manager.loadCreatureSprites("GiantFrog");
        break;
    case 32:
        SpriteBank::manager.loadCreatureSprites("GiantLizard");
        break;
    case 33:
        SpriteBank::manager.loadCreatureSprites("GiantPlant");
        break;
    case 34:
        SpriteBank::manager.loadCreatureSprites("GMG");
        break;
    case 35:
        SpriteBank::manager.loadCreatureSprites("GOL");
        break;
    case 36:
        SpriteBank::manager.loadCreatureSprites("GT-Arrow");
        break;
    case 37:
        SpriteBank::manager.loadCreatureSprites("GT-Cannon");
        break;
    case 38:
        SpriteBank::manager.loadCreatureSprites("Guard");
        break;
    case 39:
        SpriteBank::manager.loadCreatureSprites("Helb");
        break;
    case 40:
        SpriteBank::manager.loadCreatureSprites("Hellclaw");
        break;
    case 41:
        SpriteBank::manager.loadCreatureSprites("IceGolem");
        break;
    case 42:
        SpriteBank::manager.loadCreatureSprites("Liche");
        break;
    case 43:
        SpriteBank::manager.loadCreatureSprites("LWB");
        break;
    case 44:
        SpriteBank::manager.loadCreatureSprites("ManaCollector");
        break;
    case 45:
        SpriteBank::manager.loadCreatureSprites("ManaStone");
        break;
    case 46:
        SpriteBank::manager.loadCreatureSprites("MasterMageOrc");
        break;
    case 47:
        SpriteBank::manager.loadCreatureSprites("Minotaurs");
        break;
    case 48:
        SpriteBank::manager.loadCreatureSprites("MTGiant");
        break;
    case 49:
        SpriteBank::manager.loadCreatureSprites("Orc");
        break;
    case 50:
        SpriteBank::manager.loadCreatureSprites("Orge");
        break;
    case 51:
        SpriteBank::manager.loadCreatureSprites("Nizie");
        break;
    case 52:
        SpriteBank::manager.loadCreatureSprites("Rudolph");
        break;
    case 53:
        SpriteBank::manager.loadCreatureSprites("Scp");
        break;
    case 54:
        SpriteBank::manager.loadCreatureSprites("SKE");
        break;
    case 55:
        SpriteBank::manager.loadCreatureSprites("SLM");
        break;
    case 56:
        SpriteBank::manager.loadCreatureSprites("Sorceress");
        break;
    case 57:
        SpriteBank::manager.loadCreatureSprites("Stalker");
        break;
    case 58:
        SpriteBank::manager.loadCreatureSprites("Tentocle");
        break;
    case 59:
        SpriteBank::manager.loadCreatureSprites("Tigerworm");
        break;
    case 60:
        SpriteBank::manager.loadCreatureSprites("Unicorn");
        break;
    case 61:
        SpriteBank::manager.loadCreatureSprites("TK");
        break;
    case 62:
        SpriteBank::manager.loadCreatureSprites("TPKnight");
        break;
    case 63:
        SpriteBank::manager.loadCreatureSprites("Troll");
        break;
    case 64:
        SpriteBank::manager.loadCreatureSprites("Zom");
        break;
    case 65:
        SpriteBank::manager.loadCreatureSprites("WereWolf");
        break;
    case 66:
        // TODO: This one fails to load. Figure out why
        //SpriteBank::manager.loadCreatureSprites("Scarecrow");
        break;
    case 67:
        SpriteBank::manager.loadPlayerSprites("Bm");
        break;
    case 68:
        SpriteBank::manager.loadPlayerSprites("Bw");
        break;
    case 69:
        SpriteBank::manager.loadPlayerSprites("Wm");
        break;
    case 70:
        SpriteBank::manager.loadPlayerSprites("Ww");
        break;
    case 71:
        SpriteBank::manager.loadPlayerSprites("Ym");
        break;
    case 72:
        SpriteBank::manager.loadPlayerSprites("Yw");
        SpriteBank::manager.loadPlayerEquipment("MHauberk", "WHauberk");
        break;

        case 100:
            Game::getInstance().changeScene(new MenuScene);
            break;
    }

    if (percent <= 100) percent++;
}

void LoadingScene::onDraw(SDL_Surface* dest)
{
    SpriteBank::manager.draw(dest, 1, 1, SPRID_NEWDIALOG_LOADING, 0);
    SpriteBank::manager.draw(dest, 473, 443, percent+17, 17, SPRID_NEWDIALOG_LOADING, 1);
}
