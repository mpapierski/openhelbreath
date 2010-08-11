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
    // Bm.pak - naked man - 96 sprites inside
    // Bw.pak - naked female - 96 sprites inside
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
    // Yw.pak - woman model - 96 sprites
    // Wbo.pak
    // Whr.pak
    // William.pak - william npc - 8 sprites
    // Wm.pak - male model - 96 sprites
    // Wpt.pak
    // Wsh.pak
    // Wsw.pak
    // Wsw2.pak
    // Wsw3.pak
    // Ww.pak - woman model - 96 sprites
    // Wyvern.pak - 24 sprites
    // Ym.pak - male model - 96 sprites
    // yseffect2.pak
    // yseffect3.pak
    // yseffect4.pak

    // EQUIPMENT

    // MHauberk.pak - 12 sprites inside
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
    // WHauberk.pak - 12 sprites inside
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
            SpriteBank::manager.loadCreature("ABS");
            break;
    case 2:
        SpriteBank::manager.loadCreature("DarkElf");
        break;
    case 3:
        SpriteBank::manager.loadCreature("Cyc");
        break;
    case 4:
        SpriteBank::manager.loadCreature("Ant");
        break;
    case 5:
        SpriteBank::manager.loadCreature("Demon");
        break;
    case 6:
        SpriteBank::manager.loadCreature("Beholder");
        break;
    case 7:
        SpriteBank::manager.loadCreature("BG");
        break;
    case 8:
        SpriteBank::manager.loadCreature("Amp");
        break;
    case 9:
        SpriteBank::manager.loadCreature("Babarian");
        break;
    case 10:
        SpriteBank::manager.loadCreature("Barlog");
        break;
    case 11:
        SpriteBank::manager.loadCreature("Bunny");
        break;
    case 12:
        SpriteBank::manager.loadCreature("CanPlant");
        break;
    case 13:
        SpriteBank::manager.loadCreature("Cat");
        break;
    case 14:
        SpriteBank::manager.loadCreature("Catapult");
        break;
    case 15:
        SpriteBank::manager.loadCreature("Centaurus");
        break;
    case 16:
        SpriteBank::manager.loadCreature("Cla");
        break;
    case 17:
        SpriteBank::manager.loadCreature("Clawturtle");
        break;
    case 18:
        SpriteBank::manager.loadCreature("Crop");
        break;
    case 19:
        SpriteBank::manager.loadCreature("DarkKnight");
        break;
    case 20:
        SpriteBank::manager.loadCreature("Detector");
        break;
    case 21:
        SpriteBank::manager.loadCreature("Direboar");
        break;
    case 22:
        SpriteBank::manager.loadCreature("dummy");
        break;
    case 23:
        SpriteBank::manager.loadCreature("ElfMaster");
        break;
    case 24:
        SpriteBank::manager.loadCreature("ESG");
        break;
    case 25:
        SpriteBank::manager.loadCreature("Ettin");
        break;
    case 26:
        SpriteBank::manager.loadCreature("Frost");
        break;
    case 27:
        SpriteBank::manager.loadCreature("gagoyle");
        break;
    case 28:
        SpriteBank::manager.loadCreature("GHK");
        break;
    case 29:
        SpriteBank::manager.loadCreature("GHKABS");
        break;
    case 30:
        SpriteBank::manager.loadCreature("GiantCrayfish");
        break;
    case 31:
        SpriteBank::manager.loadCreature("GiantFrog");
        break;
    case 32:
        SpriteBank::manager.loadCreature("GiantLizard");
        break;
    case 33:
        SpriteBank::manager.loadCreature("GiantPlant");
        break;
    case 34:
        SpriteBank::manager.loadCreature("GMG");
        break;
    case 35:
        SpriteBank::manager.loadCreature("GOL");
        break;
    case 36:
        SpriteBank::manager.loadCreature("GT-Arrow");
        break;
    case 37:
        SpriteBank::manager.loadCreature("GT-Cannon");
        break;
    case 38:
        SpriteBank::manager.loadCreature("Guard");
        break;
    case 39:
        SpriteBank::manager.loadCreature("Helb");
        break;
    case 40:
        SpriteBank::manager.loadCreature("Hellclaw");
        break;
    case 41:
        SpriteBank::manager.loadCreature("IceGolem");
        break;
    case 42:
        SpriteBank::manager.loadCreature("Liche");
        break;
    case 43:
        SpriteBank::manager.loadCreature("LWB");
        break;
    case 44:
        SpriteBank::manager.loadCreature("ManaCollector");
        break;
    case 45:
        SpriteBank::manager.loadCreature("ManaStone");
        break;
    case 46:
        SpriteBank::manager.loadCreature("MasterMageOrc");
        break;
    case 47:
        SpriteBank::manager.loadCreature("Minotaurs");
        break;
    case 48:
        SpriteBank::manager.loadCreature("MTGiant");
        break;
    case 49:
        SpriteBank::manager.loadCreature("Orc");
        break;
    case 50:
        SpriteBank::manager.loadCreature("Orge");
        break;
    case 51:
        SpriteBank::manager.loadCreature("Nizie");
        break;
    case 52:
        SpriteBank::manager.loadCreature("Rudolph");
        break;
    case 53:
        SpriteBank::manager.loadCreature("Scp");
        break;
    case 54:
        SpriteBank::manager.loadCreature("SKE");
        break;
    case 55:
        SpriteBank::manager.loadCreature("SLM");
        break;
    case 56:
        SpriteBank::manager.loadCreature("Sorceress");
        break;
    case 57:
        SpriteBank::manager.loadCreature("Stalker");
        break;
    case 58:
        SpriteBank::manager.loadCreature("Tentocle");
        break;
    case 59:
        SpriteBank::manager.loadCreature("Tigerworm");
        break;
    case 60:
        SpriteBank::manager.loadCreature("Unicorn");
        break;
    case 61:
        SpriteBank::manager.loadCreature("TK");
        break;
    case 62:
        SpriteBank::manager.loadCreature("TPKnight");
        break;
    case 63:
        SpriteBank::manager.loadCreature("Troll");
        break;
    case 64:
        SpriteBank::manager.loadCreature("Zom");
        break;
    case 65:
        SpriteBank::manager.loadCreature("WereWolf");
        break;
    case 66:
        // TODO: This one fails to load. Figure out why
        //SpriteBank::manager.loadCreature("Scarecrow");
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
