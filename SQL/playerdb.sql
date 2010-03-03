-- --------------------------------------------------------- --
-- OpenHelbreath MySQL Dump                                  --
-- Run this script ONLY to install empty database structure. --
-- --------------------------------------------------------- --

DROP DATABASE IF EXISTS `playerdb`;
CREATE DATABASE `playerdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `playerdb`;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for account_database
-- ----------------------------
DROP TABLE IF EXISTS `account_database`;
CREATE TABLE `account_database` (
  `name` varchar(10) character set utf8 collate utf8_bin NOT NULL default '',
  `password` varchar(10) NOT NULL default '',
  `AccountID` int(11) unsigned NOT NULL auto_increment,
  `RealName` varchar(30) NOT NULL default '',
  `Gender` char(1) NOT NULL default '',
  `Email` varchar(50) NOT NULL default '',
  `Quiz` varchar(45) NOT NULL default '',
  `Answer` varchar(20) NOT NULL default '',
  `IsGMAccount` smallint(1) NOT NULL default '0',
  `SignUpFromClient` smallint(1) NOT NULL default '0',
  `LoginDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `BlockDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `LogoutDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `SignUpDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `LoginIpAddress` varchar(20) NOT NULL default '',
  `SignUpIpAddress` varchar(20) NOT NULL default '0.0.0.0',
  `LoginCount` int(11) NOT NULL default '0',
  PRIMARY KEY  (`name`),
  UNIQUE KEY `AccountID` (`AccountID`)
) DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for bank_item
-- ----------------------------
DROP TABLE IF EXISTS `bank_item`;
CREATE TABLE `bank_item` (
  `CharID` int(11) unsigned NOT NULL default '0',
  `ItemName` varchar(20) NOT NULL default '',
  `ItemID` bigint(20) unsigned NOT NULL auto_increment,
  `Count` int(11) unsigned NOT NULL default '0',
  `ItemType` tinyint(4) unsigned NOT NULL default '0',
  `ID1` smallint(6) NOT NULL default '0',
  `ID2` smallint(6) unsigned NOT NULL default '0',
  `ID3` smallint(6) unsigned NOT NULL default '0',
  `Color` tinyint(4) unsigned NOT NULL default '0',
  `Effect1` tinyint(4) unsigned NOT NULL default '0',
  `Effect2` tinyint(4) unsigned NOT NULL default '0',
  `Effect3` tinyint(4) unsigned NOT NULL default '0',
  `LifeSpan` int(11) unsigned NOT NULL default '0',
  `Attribute` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for char_database
-- ----------------------------
DROP TABLE IF EXISTS `char_database`;
CREATE TABLE `char_database` (
  `CharID` int(11) unsigned NOT NULL auto_increment,
  `account_name` varchar(10) NOT NULL default '',
  `char_name` varchar(10) character set utf8 collate utf8_bin NOT NULL default '',
  `ID1` mediumint(9) NOT NULL default '0',
  `ID2` mediumint(9) NOT NULL default '0',
  `ID3` mediumint(9) NOT NULL default '0',
  `Level` smallint(4) unsigned NOT NULL default '1',
  `Strength` tinyint(4) unsigned NOT NULL default '10',
  `Vitality` tinyint(4) unsigned NOT NULL default '10',
  `Dexterity` tinyint(4) unsigned NOT NULL default '10',
  `Intelligence` tinyint(4) unsigned NOT NULL default '10',
  `Magic` tinyint(4) unsigned NOT NULL default '10',
  `Agility` tinyint(4) unsigned NOT NULL default '10',
  `Luck` smallint(5) unsigned NOT NULL default '10',
  `Exp` int(11) unsigned NOT NULL default '0',
  `Gender` tinyint(1) unsigned NOT NULL default '0',
  `Skin` smallint(6) unsigned NOT NULL default '0',
  `HairStyle` smallint(6) unsigned NOT NULL default '0',
  `HairColor` smallint(6) unsigned NOT NULL default '0',
  `Underwear` smallint(6) unsigned NOT NULL default '0',
  `ApprColor` int(11) NOT NULL default '0',
  `Appr1` mediumint(6) NOT NULL default '0',
  `Appr2` mediumint(6) NOT NULL default '0',
  `Appr3` mediumint(6) NOT NULL default '0',
  `Appr4` mediumint(6) NOT NULL default '0',
  `Nation` varchar(10) NOT NULL default 'NONE',
  `MapLoc` varchar(10) NOT NULL default 'default',
  `LocX` mediumint(4) NOT NULL default '-1',
  `LocY` mediumint(4) NOT NULL default '-1',
  `Profile` varchar(255) NOT NULL default '__________',
  `AdminLevel` tinyint(4) unsigned NOT NULL default '0',
  `Contribution` int(11) unsigned NOT NULL default '0',
  `LeftSpecTime` int(11) unsigned NOT NULL default '0',
  `LockMapName` varchar(10) NOT NULL default '',
  `LockMapTime` int(11) unsigned NOT NULL default '0',
  `CreateDate` datetime NOT NULL,
  `LastSaveDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `BlockDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `GuildName` varchar(20) NOT NULL default 'NONE',
  `GuildID` int(11) NOT NULL default '-1',
  `GuildRank` tinyint(4) NOT NULL default '-1',
  `FightNum` tinyint(4) NOT NULL default '0',
  `FightDate` int(10) unsigned NOT NULL default '0',
  `FightTicket` tinyint(4) NOT NULL default '0',
  `QuestNum` smallint(5) unsigned NOT NULL default '0',
  `QuestID` int(10) unsigned NOT NULL default '0',
  `QuestCount` smallint(5) unsigned NOT NULL default '0',
  `QuestRewType` smallint(6) NOT NULL default '0',
  `QuestRewAmmount` int(10) unsigned NOT NULL default '0',
  `QuestCompleted` tinyint(1) NOT NULL default '0',
  `EventID` int(11) unsigned NOT NULL default '0',
  `WarCon` int(11) unsigned NOT NULL default '0',
  `CruJob` smallint(2) unsigned NOT NULL default '0',
  `CruID` int(11) unsigned NOT NULL default '0',
  `CruConstructPoint` int(11) unsigned NOT NULL default '0',
  `Popularity` int(11) NOT NULL default '0',
  `HP` int(11) unsigned NOT NULL default '0',
  `MP` int(11) unsigned NOT NULL default '0',
  `SP` int(11) unsigned NOT NULL default '0',
  `EK` int(11) unsigned NOT NULL default '0',
  `PK` int(11) unsigned NOT NULL default '0',
  `RewardGold` int(11) unsigned NOT NULL default '0',
  `DownSkillID` tinyint(4) NOT NULL default '-1',
  `Hunger` tinyint(4) unsigned NOT NULL default '100',
  `LeftSAC` tinyint(4) unsigned NOT NULL default '0',
  `LeftShutupTime` int(11) unsigned NOT NULL default '0',
  `LeftPopTime` int(11) unsigned NOT NULL default '0',
  `LeftForceRecallTime` int(11) unsigned NOT NULL default '0',
  `LeftFirmStaminarTime` int(11) unsigned NOT NULL default '0',
  `LeftDeadPenaltyTime` int(11) unsigned NOT NULL default '0',
  `MagicMastery` varchar(100) NOT NULL default '0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000',
  `PartyID` int(11) unsigned NOT NULL default '0',
  `GizonItemUpgradeLeft` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`char_name`),
  UNIQUE KEY `CharID` (`CharID`),
  KEY `account_name` (`account_name`)
) DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for guild
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild` (
  `GuildID` int(11) unsigned NOT NULL auto_increment,
  `GuildName` varchar(20) NOT NULL default '',
  `MasterName` varchar(10) NOT NULL default '',
  `Nation` varchar(10) NOT NULL default '',
  `CreateDate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`GuildID`),
  UNIQUE KEY `GuildID` (`GuildID`),
  KEY `GuildName` (`GuildName`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for guild_member
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member` (
  `GuildID` int(11) NOT NULL,
  `MemberName` varchar(10) NOT NULL default '',
  `JoinDate` datetime NOT NULL default '0000-00-00 00:00:00',
  KEY `GuildName` (`GuildID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for item
-- ----------------------------
DROP TABLE IF EXISTS `item`;
CREATE TABLE `item` (
  `CharID` int(11) unsigned NOT NULL default '0',
  `ItemName` varchar(20) NOT NULL default '',
  `ItemID` bigint(20) unsigned NOT NULL auto_increment,
  `Count` int(11) unsigned NOT NULL default '1',
  `ItemType` tinyint(4) unsigned NOT NULL default '0',
  `ID1` smallint(6) NOT NULL default '0',
  `ID2` smallint(6) NOT NULL default '0',
  `ID3` smallint(6) NOT NULL default '0',
  `Color` tinyint(4) unsigned NOT NULL default '0',
  `Effect1` tinyint(4) unsigned NOT NULL default '0',
  `Effect2` tinyint(4) unsigned NOT NULL default '0',
  `Effect3` tinyint(4) unsigned NOT NULL default '0',
  `LifeSpan` int(11) unsigned NOT NULL default '0',
  `Attribute` int(11) unsigned NOT NULL default '0',
  `ItemEquip` tinyint(1) NOT NULL default '0',
  `ItemPosX` int(11) NOT NULL default '40',
  `ItemPosY` int(11) NOT NULL default '30',
  PRIMARY KEY  (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for skill
-- ----------------------------
DROP TABLE IF EXISTS `skill`;
CREATE TABLE `skill` (
  `CharID` int(11) unsigned NOT NULL default '0',
  `SkillID` tinyint(4) unsigned NOT NULL default '0',
  `SkillMastery` tinyint(4) unsigned NOT NULL default '0',
  `SkillSSN` int(11) unsigned NOT NULL default '0',
  KEY `Index` (`CharID`),
  KEY `SkillID` (`SkillID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `item_config`
-- ----------------------------
DROP TABLE IF EXISTS `item_config`;
CREATE TABLE `item_config` (
  `ItemID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(30) NOT NULL,
  `Type` int(11) NOT NULL,
  `EquipPos` int(11) NOT NULL,
  `Effect` int(11) NOT NULL,
  `ETValue1` int(11) NOT NULL,
  `ETValue2` int(11) NOT NULL,
  `ETValue3` int(11) NOT NULL,
  `ETValue4` int(11) NOT NULL,
  `ETValue5` int(11) NOT NULL,
  `ETValue6` int(11) NOT NULL,
  `MaxLife` int(11) NOT NULL,
  `SEffect` int(11) NOT NULL,
  `Spr` int(11) NOT NULL,
  `SprFrame` int(11) NOT NULL,
  `Price` int(11) NOT NULL,
  `Weight` int(11) NOT NULL,
  `ApprV` int(11) NOT NULL,
  `Speed` int(11) NOT NULL,
  `Level` int(11) NOT NULL,
  `Gender` int(11) NOT NULL,
  `SM_HitRatio` int(11) NOT NULL,
  `L_HitRatio` int(11) NOT NULL,
  `Skill` int(11) NOT NULL,
  `Category` int(11) NOT NULL,
  `Color` int(11) NOT NULL,
  PRIMARY KEY (`ItemID`)
) ENGINE=MyISAM AUTO_INCREMENT=559 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_config
-- ----------------------------
INSERT INTO `item_config` VALUES ('1', 'Dagger', '1', '8', '1', '1', '5', '0', '1', '4', '0', '300', '0', '1', '0', '25', '200', '1', '0', '0', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('2', 'Dagger(S.C)', '1', '8', '1', '1', '4', '0', '1', '3', '0', '800', '0', '1', '0', '-55', '200', '1', '0', '0', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('3', 'Dagger(Swd.breaker)', '1', '8', '1', '1', '4', '0', '1', '3', '0', '1', '0', '1', '0', '-55', '200', '1', '0', '0', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('4', 'Dagger+1', '1', '8', '1', '1', '5', '1', '1', '4', '1', '800', '0', '1', '0', '100', '200', '1', '0', '10', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('5', 'KightDagger', '1', '8', '1', '1', '4', '0', '1', '3', '0', '800', '0', '1', '0', '-35', '200', '1', '0', '0', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('6', 'Dirk', '1', '8', '1', '1', '4', '0', '1', '3', '0', '800', '0', '1', '0', '-35', '200', '1', '0', '0', '0', '0', '-10', '7', '1', '0');
INSERT INTO `item_config` VALUES ('7', 'ShortSword', '1', '8', '1', '1', '6', '0', '1', '5', '0', '500', '0', '1', '1', '50', '800', '2', '2', '0', '0', '0', '-5', '7', '1', '0');
INSERT INTO `item_config` VALUES ('8', 'ShortSword+1', '1', '8', '1', '1', '6', '1', '1', '5', '1', '800', '0', '1', '1', '200', '800', '2', '2', '10', '0', '0', '-5', '7', '1', '0');
INSERT INTO `item_config` VALUES ('9', 'ShortSword(S.C)', '1', '8', '1', '1', '6', '0', '1', '5', '0', '800', '0', '1', '1', '-100', '800', '2', '2', '0', '0', '0', '-5', '7', '1', '0');
INSERT INTO `item_config` VALUES ('10', 'MainGauche', '1', '8', '1', '1', '7', '0', '1', '6', '0', '500', '0', '1', '1', '50', '800', '2', '2', '0', '0', '0', '-2', '7', '1', '0');
INSERT INTO `item_config` VALUES ('11', 'MainGauche+1', '1', '8', '1', '1', '7', '1', '1', '6', '1', '800', '0', '1', '1', '200', '800', '2', '2', '15', '0', '0', '-2', '7', '1', '0');
INSERT INTO `item_config` VALUES ('12', 'MainGauche(S.C)', '1', '8', '1', '1', '6', '0', '1', '4', '0', '800', '0', '1', '1', '-100', '800', '2', '2', '0', '0', '0', '-2', '7', '1', '0');
INSERT INTO `item_config` VALUES ('13', 'Gradius', '1', '8', '1', '1', '8', '0', '1', '7', '0', '500', '0', '1', '1', '90', '800', '2', '2', '0', '0', '0', '-2', '7', '1', '0');
INSERT INTO `item_config` VALUES ('14', 'Gradius+1', '1', '8', '1', '1', '8', '1', '1', '7', '1', '800', '0', '1', '1', '350', '800', '2', '2', '20', '0', '0', '-2', '7', '1', '0');
INSERT INTO `item_config` VALUES ('15', 'LongSword', '1', '8', '1', '1', '9', '0', '1', '10', '0', '800', '0', '1', '2', '180', '1400', '3', '6', '0', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('16', 'LongSword+1', '1', '8', '1', '1', '9', '1', '1', '10', '1', '1400', '0', '1', '2', '650', '1400', '3', '6', '25', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('17', 'LongSword+2', '1', '8', '1', '1', '9', '2', '1', '10', '2', '1400', '0', '1', '2', '-2600', '1600', '3', '6', '50', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('18', 'Excaliber', '1', '8', '1', '2', '10', '4', '2', '12', '4', '8000', '0', '1', '19', '-31000', '4000', '5', '0', '0', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('19', 'LongSword(S.C)', '1', '8', '1', '1', '8', '0', '1', '12', '0', '1400', '0', '1', '2', '-250', '1400', '3', '6', '0', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('20', 'Sabre', '1', '8', '1', '1', '8', '0', '1', '9', '0', '800', '0', '1', '3', '150', '1200', '4', '5', '0', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('21', 'Sabre+1', '1', '8', '1', '1', '8', '1', '1', '9', '1', '1000', '0', '1', '3', '600', '1200', '4', '5', '20', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('22', 'Scimitar', '1', '8', '1', '1', '10', '0', '1', '12', '0', '800', '0', '1', '4', '200', '1800', '6', '6', '0', '0', '-1', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('23', 'Scimitar+1', '1', '8', '1', '1', '10', '1', '1', '12', '1', '1000', '0', '1', '4', '800', '1800', '6', '6', '30', '0', '-1', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('24', 'Scimitar+2', '1', '8', '1', '1', '10', '2', '1', '12', '2', '1000', '0', '1', '4', '-3200', '2000', '6', '6', '70', '0', '-1', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('25', 'Falchion', '1', '8', '1', '1', '12', '0', '2', '7', '0', '800', '0', '1', '5', '250', '2200', '6', '6', '0', '0', '-2', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('26', 'Falchion+1', '1', '8', '1', '1', '12', '1', '2', '7', '1', '1400', '0', '1', '5', '1000', '2200', '6', '6', '35', '0', '-2', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('27', 'Falchion+2', '1', '8', '1', '1', '12', '2', '2', '7', '2', '1400', '0', '1', '5', '-4000', '2200', '6', '6', '70', '0', '-2', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('28', 'Esterk', '1', '8', '1', '1', '8', '0', '1', '12', '0', '800', '0', '1', '6', '400', '1200', '7', '4', '0', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('29', 'Esterk+1', '1', '8', '1', '1', '8', '1', '1', '12', '1', '1400', '0', '1', '6', '800', '1200', '7', '4', '20', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('30', 'Esterk+2', '1', '8', '1', '1', '8', '2', '1', '12', '2', '1400', '0', '1', '6', '-3200', '1200', '7', '4', '70', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('31', 'Rapier', '1', '8', '1', '1', '7', '0', '1', '10', '0', '800', '0', '1', '6', '300', '1100', '7', '3', '0', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('32', 'Rapier+1', '1', '8', '1', '1', '7', '1', '1', '10', '1', '1000', '0', '1', '6', '1300', '1100', '7', '3', '30', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('33', 'Rapier+2', '1', '8', '1', '1', '7', '2', '1', '10', '2', '1000', '0', '1', '6', '-5200', '1100', '7', '3', '70', '0', '0', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('34', 'TemplerSword', '1', '8', '1', '1', '8', '0', '1', '12', '0', '1000', '0', '1', '6', '-1000', '1200', '7', '5', '0', '0', '-1', '1', '8', '1', '0');
INSERT INTO `item_config` VALUES ('35', 'BroadSword', '1', '9', '1', '2', '7', '0', '2', '8', '0', '800', '0', '1', '7', '250', '2800', '8', '6', '0', '0', '-3', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('36', 'BroadSword+1', '1', '9', '1', '2', '7', '1', '2', '8', '1', '1400', '0', '1', '7', '1100', '2800', '8', '6', '30', '0', '-3', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('37', 'BroadSword+2', '1', '9', '1', '2', '7', '2', '2', '8', '2', '1400', '0', '1', '7', '-4400', '2800', '8', '6', '70', '0', '-3', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('38', 'BroadSword(S.C)', '1', '9', '1', '2', '7', '0', '2', '8', '0', '1400', '0', '1', '7', '-400', '2800', '8', '6', '0', '0', '-3', '2', '8', '1', '0');
INSERT INTO `item_config` VALUES ('39', 'BastadSword', '1', '9', '1', '2', '8', '0', '2', '9', '0', '800', '0', '1', '8', '300', '3300', '9', '6', '0', '0', '-4', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('40', 'BastadSword+1', '1', '9', '1', '2', '8', '1', '2', '9', '1', '1400', '0', '1', '8', '1200', '3300', '9', '6', '35', '0', '-4', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('41', 'BastadSword+2', '1', '9', '1', '2', '8', '2', '2', '9', '2', '1400', '0', '1', '8', '-4800', '3300', '9', '6', '70', '0', '-4', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('42', 'BastadSword(S.C)', '1', '9', '1', '2', '5', '0', '2', '9', '0', '1400', '0', '1', '8', '-450', '3300', '9', '6', '0', '0', '-4', '3', '8', '1', '0');
INSERT INTO `item_config` VALUES ('43', 'Claymore', '1', '9', '1', '2', '9', '0', '2', '10', '0', '1000', '0', '1', '9', '400', '4000', '10', '7', '0', '0', '-5', '4', '8', '1', '0');
INSERT INTO `item_config` VALUES ('44', 'Claymore+1', '1', '9', '1', '2', '9', '1', '2', '10', '1', '1400', '0', '1', '9', '1800', '4000', '10', '7', '40', '0', '-5', '4', '8', '1', '0');
INSERT INTO `item_config` VALUES ('45', 'Claymore+2', '1', '9', '1', '2', '9', '2', '2', '10', '2', '1400', '0', '1', '9', '-7200', '4000', '10', '7', '70', '0', '-5', '4', '8', '1', '0');
INSERT INTO `item_config` VALUES ('46', 'Claymore(S.C)', '1', '9', '1', '2', '9', '0', '2', '10', '0', '1400', '0', '1', '9', '-600', '4000', '10', '7', '0', '0', '-5', '4', '8', '1', '0');
INSERT INTO `item_config` VALUES ('47', 'GreatSword', '1', '9', '1', '2', '10', '0', '2', '11', '0', '1000', '0', '1', '10', '500', '5200', '11', '8', '0', '0', '-8', '5', '8', '1', '0');
INSERT INTO `item_config` VALUES ('48', 'GreatSword+1', '1', '9', '1', '2', '10', '1', '2', '11', '1', '1400', '0', '1', '10', '2300', '5200', '11', '8', '50', '0', '-8', '5', '8', '1', '0');
INSERT INTO `item_config` VALUES ('49', 'GreatSword+2', '1', '9', '1', '2', '10', '2', '2', '11', '2', '1400', '0', '1', '10', '-9200', '5200', '11', '8', '70', '0', '-8', '5', '8', '1', '0');
INSERT INTO `item_config` VALUES ('50', 'GreatSword(S.C)', '1', '9', '1', '2', '10', '0', '2', '11', '0', '1400', '0', '1', '10', '-700', '5200', '11', '8', '0', '0', '-8', '5', '8', '1', '0');
INSERT INTO `item_config` VALUES ('51', 'Flameberge', '1', '9', '1', '2', '11', '0', '2', '12', '0', '1000', '0', '1', '11', '700', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '0');
INSERT INTO `item_config` VALUES ('52', 'Flameberge+1', '1', '9', '1', '2', '11', '1', '2', '12', '1', '1400', '0', '1', '11', '3300', '6000', '12', '10', '60', '0', '-15', '10', '8', '1', '0');
INSERT INTO `item_config` VALUES ('53', 'Flameberge+2', '1', '9', '1', '2', '11', '2', '2', '12', '2', '1400', '0', '1', '11', '-13200', '6000', '12', '10', '70', '0', '-15', '10', '8', '1', '0');
INSERT INTO `item_config` VALUES ('54', 'Flameberge(S.C)', '1', '9', '1', '2', '11', '0', '2', '12', '0', '1400', '0', '1', '11', '-1000', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '0');
INSERT INTO `item_config` VALUES ('55', 'LightAxe', '1', '8', '1', '1', '6', '0', '1', '7', '0', '500', '0', '15', '2', '100', '1400', '22', '3', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('56', 'LightAxe+1', '1', '8', '1', '1', '6', '1', '1', '7', '1', '500', '0', '15', '2', '350', '1400', '22', '3', '10', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('57', 'LightAxe+2', '1', '8', '1', '1', '6', '2', '1', '7', '2', '500', '0', '15', '2', '-1400', '1400', '22', '3', '70', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('58', 'Tomahoc', '1', '8', '1', '2', '3', '0', '2', '4', '0', '500', '0', '15', '2', '180', '1700', '22', '4', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('59', 'Tomahoc+1', '1', '8', '1', '2', '3', '1', '2', '4', '1', '500', '0', '15', '2', '700', '1700', '22', '4', '20', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('60', 'Tomahoc+2', '1', '8', '1', '2', '3', '2', '2', '4', '2', '500', '0', '15', '2', '-2800', '1700', '22', '4', '70', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('61', 'SexonAxe', '1', '8', '1', '2', '4', '0', '2', '5', '0', '700', '0', '15', '3', '200', '2000', '23', '4', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('62', 'SexonAxe+1', '1', '8', '1', '2', '4', '1', '2', '5', '1', '700', '0', '15', '3', '800', '2000', '23', '4', '30', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('63', 'SexonAxe+2', '1', '8', '1', '2', '4', '2', '2', '5', '2', '700', '0', '15', '3', '-3200', '2000', '23', '4', '70', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('64', 'DoubleAxe', '1', '8', '1', '3', '3', '0', '3', '3', '0', '800', '0', '15', '0', '560', '3300', '20', '5', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('65', 'DoubleAxe+1', '1', '8', '1', '3', '3', '1', '3', '3', '1', '800', '0', '15', '0', '1200', '3300', '20', '5', '40', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('66', 'DoubleAxe+2', '1', '8', '1', '3', '3', '2', '3', '3', '2', '800', '0', '15', '0', '-4800', '3300', '20', '5', '70', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('67', 'WarAxe', '1', '8', '1', '3', '5', '0', '3', '6', '0', '1000', '0', '15', '1', '700', '4400', '21', '8', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('68', 'WarAxe+1', '1', '8', '1', '3', '5', '1', '3', '6', '1', '1000', '0', '15', '1', '2000', '4400', '21', '8', '60', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('69', 'WarAxe+2', '1', '8', '1', '3', '5', '2', '3', '6', '2', '1000', '0', '15', '1', '-8000', '4400', '21', '8', '70', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('70', '4BladeGoldenAxe', '1', '8', '1', '3', '6', '0', '3', '6', '0', '2000', '0', '15', '4', '-52000', '2000', '24', '6', '60', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('71', 'ShortBow', '1', '9', '3', '1', '6', '0', '1', '6', '0', '500', '0', '2', '0', '100', '800', '40', '4', '0', '0', '5', '0', '6', '3', '0');
INSERT INTO `item_config` VALUES ('72', 'LongBow', '1', '9', '3', '1', '7', '0', '1', '7', '0', '800', '0', '2', '1', '200', '1200', '41', '5', '0', '0', '0', '5', '6', '3', '0');
INSERT INTO `item_config` VALUES ('73', 'Arrow', '6', '0', '0', '1', '4', '0', '1', '4', '0', '1', '0', '6', '10', '1', '10', '1', '3', '0', '0', '0', '0', '0', '4', '0');
INSERT INTO `item_config` VALUES ('74', 'PoisonArrow', '6', '0', '0', '1', '8', '0', '1', '8', '0', '1', '0', '6', '10', '-5', '10', '1', '5', '0', '0', '0', '0', '0', '4', '0');
INSERT INTO `item_config` VALUES ('75', 'WoodShield', '1', '7', '2', '8', '1', '1', '1', '1', '1', '300', '0', '3', '0', '100', '800', '1', '0', '0', '0', '0', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('76', 'LeatherShield', '1', '7', '2', '10', '1', '1', '1', '1', '1', '300', '0', '3', '1', '150', '1000', '2', '0', '0', '0', '0', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('77', 'TargeShield', '1', '7', '2', '13', '1', '1', '1', '1', '1', '500', '0', '3', '2', '250', '1800', '3', '0', '0', '0', '0', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('78', 'ScootermShield', '1', '7', '2', '16', '1', '1', '1', '1', '1', '500', '0', '3', '3', '300', '2000', '4', '0', '0', '0', '0', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('79', 'BlondeShield', '1', '7', '2', '18', '1', '1', '1', '1', '1', '500', '0', '3', '4', '450', '2000', '5', '0', '0', '0', '0', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('80', 'IronShield', '1', '7', '2', '22', '1', '1', '1', '1', '1', '500', '0', '3', '5', '700', '2500', '6', '0', '0', '0', '-2', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('81', 'LagiShield', '1', '7', '2', '26', '1', '1', '1', '1', '1', '800', '0', '3', '6', '1300', '3000', '7', '0', '0', '0', '-4', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('82', 'KnightShield', '1', '7', '2', '30', '1', '1', '1', '1', '1', '800', '0', '3', '7', '1500', '3200', '8', '0', '0', '0', '-8', '-5', '11', '5', '0');
INSERT INTO `item_config` VALUES ('83', 'TowerShield', '1', '7', '2', '35', '1', '1', '1', '1', '1', '800', '0', '3', '8', '1800', '4000', '9', '0', '0', '0', '-10', '-10', '11', '5', '0');
INSERT INTO `item_config` VALUES ('84', 'GuildAdmissionTicket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '6', '9', '5', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('85', 'GuildSecessionTicket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '6', '9', '5', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('86', 'Gold', '5', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '6', '0', '1', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('87', 'RedPotion', '7', '0', '4', '2', '12', '10', '0', '0', '0', '1', '0', '6', '1', '10', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('88', 'BigRedPotion', '7', '0', '4', '3', '8', '40', '0', '0', '0', '1', '0', '6', '2', '65', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('89', 'BluePotion', '7', '0', '5', '2', '12', '10', '0', '0', '0', '1', '0', '6', '3', '10', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('90', 'BigBluePotion', '7', '0', '5', '4', '8', '50', '0', '0', '0', '1', '0', '6', '4', '65', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('91', 'GreenPotion', '7', '0', '6', '2', '12', '10', '0', '0', '0', '1', '0', '6', '5', '10', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('92', 'BigGreenPotion', '7', '0', '6', '4', '8', '50', '0', '0', '0', '1', '0', '6', '6', '65', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('93', 'DilutionPotion', '3', '0', '9', '23', '20', '0', '0', '0', '0', '1', '0', '6', '5', '200', '30', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('94', 'Baguette', '7', '0', '7', '2', '8', '10', '0', '0', '0', '1', '0', '6', '8', '5', '17', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('95', 'Meat', '7', '0', '7', '4', '8', '10', '0', '0', '0', '1', '0', '6', '7', '10', '52', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('96', 'Fish', '7', '0', '7', '4', '8', '10', '0', '0', '0', '1', '0', '6', '11', '30', '30', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('97', 'RedFish', '7', '0', '7', '8', '4', '60', '0', '0', '0', '1', '0', '6', '14', '-400', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('98', 'GreenFish', '7', '0', '7', '8', '4', '40', '0', '0', '0', '1', '0', '6', '15', '-200', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('99', 'YellowFish', '7', '0', '7', '8', '4', '30', '0', '0', '0', '1', '0', '6', '16', '-100', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('100', 'Map', '9', '0', '10', '1', '0', '0', '0', '0', '0', '35', '0', '6', '9', '30', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('101', 'FishingRod', '8', '0', '0', '1', '8', '0', '0', '0', '0', '200', '0', '14', '0', '100', '300', '-1', '0', '0', '0', '0', '0', '1', '43', '0');
INSERT INTO `item_config` VALUES ('102', 'PretendCorpseManual', '3', '0', '9', '19', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('103', 'ArcheryManual', '3', '0', '9', '6', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('104', 'ShieldManual', '3', '0', '9', '11', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('105', 'LongSwordManual', '3', '0', '9', '8', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('106', 'FencingManual', '3', '0', '9', '9', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('107', 'FishingManual', '3', '0', '9', '1', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('108', 'AxeManual', '3', '0', '9', '10', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('109', 'MagicResistManual', '3', '0', '9', '3', '20', '0', '0', '0', '0', '0', '0', '6', '92', '500', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('110', 'RecallScroll', '3', '0', '11', '1', '0', '0', '0', '0', '0', '1', '0', '6', '9', '120', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('111', 'InvisibilityScroll', '3', '0', '11', '2', '0', '0', '0', '0', '0', '1', '0', '6', '9', '560', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('112', 'DetectInviScroll', '3', '0', '11', '3', '0', '0', '0', '0', '0', '1', '0', '6', '9', '330', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('113', 'BleedingIslandTicket', '3', '0', '11', '4', '1', '0', '0', '0', '0', '1', '0', '6', '9', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('114', 'SnakeMeat', '7', '0', '7', '4', '8', '20', '0', '0', '0', '1', '0', '6', '17', '-57', '45', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('115', 'SnakeSkin', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '18', '-175', '20', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('116', 'SnakeTeeth', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '19', '-55', '5', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('117', 'SnakeTongue', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '20', '-50', '3', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('118', 'AntLeg', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '21', '-32', '17', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('119', 'AntFeeler', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '22', '-34', '10', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('120', 'CyclopsEye', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '23', '-170', '330', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('121', 'CyclopsHandEdge', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '24', '-270', '4000', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('122', 'CyclopsHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '25', '-160', '1230', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('123', 'CyclopsMeat', '7', '0', '7', '4', '8', '30', '0', '0', '0', '1', '0', '6', '26', '-90', '500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('124', 'CyclopsLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '27', '-600', '350', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('125', 'HelboundHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '28', '-90', '820', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('126', 'HelboundLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '29', '-320', '200', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('127', 'HelboundTail', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '30', '-70', '250', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('128', 'HelboundTeeth', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '31', '-70', '130', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('129', 'HelboundClaw', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '32', '-70', '280', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('130', 'HelboundTongue', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '33', '-75', '150', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('131', 'LumpofClay', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '34', '-95', '230', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('132', 'OrcMeat', '7', '0', '7', '2', '4', '5', '0', '0', '0', '1', '0', '6', '35', '-50', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('133', 'OrcLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '36', '-193', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('134', 'OrcTeeth', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '37', '-56', '50', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('135', 'OgreHair', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '38', '-230', '250', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('136', 'OgreHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '39', '-340', '1580', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('137', 'OgreMeat', '7', '0', '7', '4', '8', '50', '0', '0', '0', '1', '0', '6', '40', '-200', '710', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('138', 'OgreLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '41', '-840', '650', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('139', 'OgreTeeth', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '42', '-215', '230', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('140', 'OgreClaw', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '43', '-215', '370', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('141', 'ScorpionPincers', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '44', '-50', '1200', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('142', 'ScorpionMeat', '7', '0', '7', '4', '8', '25', '0', '0', '0', '1', '0', '6', '45', '-55', '450', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('143', 'ScorpionSting', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '46', '-55', '1000', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('144', 'ScorpionSkin', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '47', '-90', '380', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('145', 'SkeletonBones', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '48', '-50', '1300', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('146', 'SlimeJelly', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '49', '-10', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('147', 'StoneGolemPiece', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '50', '-50', '500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('148', 'TrollHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '51', '-145', '1050', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('149', 'TrollMeat', '7', '0', '7', '8', '4', '50', '0', '0', '0', '1', '0', '6', '52', '-180', '500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('150', 'TrollLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '53', '-335', '450', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('151', 'TrollClaw', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '54', '-70', '290', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('152', 'AlchemyManual', '3', '0', '9', '12', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('153', 'AlchemyBowl', '10', '0', '0', '1', '0', '0', '0', '0', '0', '300', '0', '6', '55', '1000', '700', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('154', 'MiningManual', '3', '0', '9', '0', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('155', 'PickAxe', '1', '8', '1', '2', '4', '0', '2', '4', '0', '1000', '0', '15', '5', '500', '1000', '25', '10', '0', '0', '0', '0', '0', '1', '0');
INSERT INTO `item_config` VALUES ('156', 'Hoe', '1', '8', '1', '2', '4', '0', '2', '4', '0', '800', '0', '15', '9', '300', '1000', '27', '5', '0', '0', '0', '0', '-1', '1', '0');
INSERT INTO `item_config` VALUES ('157', 'ManufacturingManual', '3', '0', '9', '13', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('158', 'ManufacturingHammer', '10', '0', '0', '1', '0', '0', '0', '0', '0', '300', '0', '6', '113', '1500', '2000', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('159', 'HammerAttackManual', '3', '0', '9', '14', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('160', 'AresdenFlag(Master)', '11', '0', '16', '1', '1', '0', '0', '0', '0', '1', '0', '6', '56', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('161', 'ElvineFlag(Master)', '11', '0', '16', '2', '1', '0', '0', '0', '0', '1', '0', '6', '57', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('162', 'AresdenFlag', '11', '0', '16', '1', '0', '0', '0', '0', '0', '1', '0', '6', '56', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('163', 'ElvineFlag', '11', '0', '16', '2', '0', '0', '0', '0', '0', '1', '0', '6', '57', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('164', 'WandAttackManual', '3', '0', '9', '21', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('165', 'MagicWand(MS20)', '1', '8', '13', '2', '4', '0', '20', '0', '0', '3600', '0', '17', '1', '5000', '1000', '36', '3', '50', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('166', 'MagicWand(MS10)', '1', '8', '13', '2', '4', '0', '10', '0', '0', '2400', '0', '17', '1', '2500', '1000', '36', '3', '40', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('167', 'MagicWand(MS0)', '1', '8', '13', '2', '4', '0', '0', '0', '0', '1200', '0', '17', '1', '1000', '1000', '36', '3', '30', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('168', 'MagicWand(M.Shield)', '1', '8', '20', '2', '4', '0', '0', '0', '0', '5000', '30', '17', '1', '-8200', '1000', '36', '3', '0', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('169', 'HairColorPotion', '7', '0', '12', '1', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-300', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('170', 'HairStylePotion', '7', '0', '12', '2', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-400', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('171', 'SkinColorPotion', '7', '0', '12', '3', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-500', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('172', 'InvisibilityPotion', '7', '0', '11', '2', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-700', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('173', 'SexChangePotion', '7', '0', '12', '4', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-4000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('174', 'OgrePotion', '7', '0', '11', '5', '8', '0', '0', '0', '0', '1', '0', '6', '5', '-5000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('175', 'UnderWearPotion', '7', '0', '12', '5', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-4000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('176', 'Flameberge+3(LLF)', '1', '9', '1', '2', '11', '3', '2', '12', '3', '8000', '0', '1', '11', '-21000', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '0');
INSERT INTO `item_config` VALUES ('177', 'MagicWand(MS30-LLF)', '1', '8', '13', '2', '4', '0', '30', '0', '0', '4800', '0', '17', '0', '-10000', '1000', '35', '3', '0', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('178', 'GoldenAxe(LLF)', '1', '8', '1', '2', '8', '0', '2', '8', '0', '2000', '0', '15', '4', '-32000', '2000', '24', '6', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('179', 'MagicNecklace(RM10)', '1', '6', '14', '1', '10', '0', '0', '0', '0', '300', '0', '16', '4', '-2250', '400', '-1', '0', '30', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('180', 'MagicNecklace(DM+1)', '1', '6', '14', '3', '1', '0', '0', '0', '0', '300', '0', '16', '5', '-39800', '400', '-1', '0', '65', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('181', 'MagicNecklace(MS10)', '1', '6', '14', '2', '10', '0', '0', '0', '0', '300', '0', '16', '7', '-7000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('182', 'MagicNecklace(DF+10)', '1', '6', '14', '4', '10', '0', '0', '0', '0', '300', '0', '16', '6', '-19000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('183', 'GoldNecklace', '1', '6', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '8', '1000', '300', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('184', 'SilverNecklace', '1', '6', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '9', '500', '300', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('185', 'GoldRing', '1', '10', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '14', '700', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('186', 'SilverRing', '1', '10', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '15', '350', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('187', 'PlatinumRing', '1', '10', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '15', '-750', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('188', 'LuckyGoldRing', '1', '10', '14', '5', '0', '0', '0', '0', '0', '300', '0', '16', '13', '-2750', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('189', 'EmeraldRing', '1', '10', '15', '0', '0', '0', '0', '0', '0', '9000', '0', '16', '10', '-2500', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('190', 'SapphireRing', '1', '10', '0', '0', '0', '0', '0', '0', '0', '5000', '0', '16', '11', '-2450', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('191', 'RubyRing', '1', '10', '15', '0', '0', '0', '0', '0', '0', '5000', '0', '16', '12', '-1800', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('192', 'MemorialRing', '1', '10', '0', '0', '0', '0', '0', '0', '0', '300', '0', '16', '12', '-1000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('193', 'Diamond', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '42', '-3000', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('194', 'Ruby', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '43', '-2000', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('195', 'Sapphire', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '44', '-2000', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('196', 'Emerald', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '45', '-2000', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('197', 'GoldNugget', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '21', '-300', '300', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('198', 'Coal', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '22', '-50', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('199', 'SilverNugget', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '23', '-200', '220', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('200', 'IronOre', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '24', '-100', '250', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('201', 'Crystal', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '46', '-300', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('202', 'Dye(Indigo)', '11', '0', '17', '1', '0', '0', '0', '0', '0', '1', '0', '6', '58', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('203', 'Dye(Crimson-Red)', '11', '0', '17', '2', '0', '0', '0', '0', '0', '1', '0', '6', '58', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('204', 'Dye(Brown)', '11', '0', '17', '3', '0', '0', '0', '0', '0', '1', '0', '6', '58', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('205', 'Dye(Gold)', '11', '0', '17', '4', '0', '0', '0', '0', '0', '1', '0', '6', '58', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('206', 'Dye(Green)', '11', '0', '17', '5', '0', '0', '0', '0', '0', '1', '0', '6', '62', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('207', 'Dye(Gray)', '11', '0', '17', '6', '0', '0', '0', '0', '0', '1', '0', '6', '63', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('208', 'Dye(Aqua)', '11', '0', '17', '7', '0', '0', '0', '0', '0', '1', '0', '6', '58', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('209', 'Dye(Pink)', '11', '0', '17', '8', '0', '0', '0', '0', '0', '1', '0', '6', '58', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('210', 'Dye(Violet)', '11', '0', '17', '9', '0', '0', '0', '0', '0', '1', '0', '6', '66', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('211', 'Dye(Blue)', '11', '0', '17', '10', '0', '0', '0', '0', '0', '1', '0', '6', '67', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('212', 'Dye(Tan)', '11', '0', '17', '11', '0', '0', '0', '0', '0', '1', '0', '6', '68', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('213', 'Dye(Khaki)', '11', '0', '17', '12', '0', '0', '0', '0', '0', '1', '0', '6', '69', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('214', 'Dye(Yellow)', '11', '0', '17', '13', '0', '0', '0', '0', '0', '1', '0', '6', '70', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('215', 'Dye(Red)', '11', '0', '17', '14', '0', '0', '0', '0', '0', '1', '0', '6', '71', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('216', 'Dye(Black)', '11', '0', '17', '15', '0', '0', '0', '0', '0', '1', '0', '6', '58', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('217', 'DecolorationPotion', '11', '0', '17', '0', '0', '0', '0', '0', '0', '1', '0', '6', '58', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('218', 'IceStormManual', '3', '0', '18', '55', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '1');
INSERT INTO `item_config` VALUES ('219', 'MassFireStrikeManual', '3', '0', '18', '61', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '2');
INSERT INTO `item_config` VALUES ('220', 'BloodyShockW.Manual', '3', '0', '18', '70', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '2');
INSERT INTO `item_config` VALUES ('221', 'HandAttackManual', '3', '0', '9', '5', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('222', 'ShortSwordManual', '3', '0', '9', '7', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('223', 'PowerGreenPotion', '7', '0', '22', '300', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-600', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('224', 'SuperGreenPotion', '7', '0', '22', '600', '0', '0', '0', '0', '0', '1', '0', '6', '5', '-1200', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('225', 'AresdenHeroCape', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '0', '-2000', '200', '1', '0', '0', '0', '0', '0', '-1', '13', '0');
INSERT INTO `item_config` VALUES ('226', 'ElvineHeroCape', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '1', '-2000', '200', '2', '0', '0', '0', '0', '0', '-1', '13', '0');
INSERT INTO `item_config` VALUES ('227', 'Cape', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '2', '1000', '200', '3', '0', '0', '0', '0', '0', '-1', '12', '0');
INSERT INTO `item_config` VALUES ('228', 'aHeroHelm(M)', '1', '1', '2', '18', '24', '0', '0', '0', '0', '2500', '0', '21', '7', '-16000', '10000', '10', '0', '0', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('229', 'aHeroHelm(W)', '1', '1', '2', '18', '24', '0', '0', '0', '0', '2500', '0', '21', '7', '-16000', '10000', '10', '0', '0', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('230', 'eHeroHelm(M)', '1', '1', '2', '18', '24', '0', '0', '0', '0', '2500', '0', '21', '6', '-16000', '10000', '9', '0', '0', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('231', 'eHeroHelm(W)', '1', '1', '2', '18', '24', '0', '0', '0', '0', '2500', '0', '21', '6', '-16000', '10000', '9', '0', '0', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('232', 'aHeroCap(M)', '1', '1', '2', '12', '15', '0', '0', '0', '0', '1500', '0', '21', '9', '-12000', '1500', '12', '0', '0', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('233', 'aHeroCap(W)', '1', '1', '2', '12', '15', '0', '0', '0', '0', '1500', '0', '21', '9', '-12000', '1500', '12', '0', '0', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('234', 'eHeroCap(M)', '1', '1', '2', '12', '15', '0', '0', '0', '0', '1500', '0', '21', '8', '-12000', '1500', '11', '0', '0', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('235', 'eHeroCap(W)', '1', '1', '2', '12', '15', '0', '0', '0', '0', '1500', '0', '21', '8', '-12000', '1500', '11', '0', '0', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('236', 'aHeroArmor(M)', '1', '2', '2', '45', '48', '0', '0', '0', '0', '5000', '0', '9', '8', '-40000', '10000', '9', '0', '0', '1', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('237', 'aHeroArmor(W)', '1', '2', '2', '45', '48', '0', '0', '0', '0', '5000', '0', '13', '9', '-40000', '10000', '10', '0', '0', '2', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('238', 'eHeroArmor(M)', '1', '2', '2', '45', '48', '0', '0', '0', '0', '5000', '0', '9', '7', '-40000', '10000', '8', '0', '0', '1', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('239', 'eHeroArmor(W)', '1', '2', '2', '45', '48', '0', '0', '0', '0', '5000', '0', '13', '8', '-40000', '10000', '9', '0', '0', '2', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('240', 'aHeroRobe(M)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '4000', '0', '9', '10', '-30000', '1500', '11', '0', '0', '1', '0', '0', '0', '13', '0');
INSERT INTO `item_config` VALUES ('241', 'aHeroRobe(W)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '4000', '0', '13', '11', '-30000', '1500', '12', '0', '0', '2', '0', '0', '0', '13', '0');
INSERT INTO `item_config` VALUES ('242', 'eHeroRobe(M)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '4000', '0', '9', '9', '-30000', '1500', '10', '0', '0', '1', '0', '0', '0', '13', '0');
INSERT INTO `item_config` VALUES ('243', 'eHeroRobe(W)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '4000', '0', '13', '10', '-30000', '1500', '11', '0', '0', '2', '0', '0', '0', '13', '0');
INSERT INTO `item_config` VALUES ('244', 'aHeroHauberk(M)', '1', '3', '2', '15', '15', '0', '0', '0', '0', '2000', '0', '7', '3', '-14000', '1500', '4', '0', '0', '1', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('245', 'aHeroHauberk(W)', '1', '3', '2', '15', '15', '0', '0', '0', '0', '2000', '0', '11', '4', '-14000', '1500', '5', '0', '0', '2', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('246', 'eHeroHauberk(M)', '1', '3', '2', '15', '15', '0', '0', '0', '0', '2000', '0', '7', '2', '-14000', '1500', '3', '0', '0', '1', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('247', 'eHeroHauberk(W)', '1', '3', '2', '15', '15', '0', '0', '0', '0', '2000', '0', '11', '3', '-14000', '1500', '4', '0', '0', '2', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('248', 'aHeroLeggings(M)', '1', '4', '2', '18', '25', '1', '1', '1', '1', '3000', '0', '8', '5', '-22000', '1500', '6', '0', '0', '1', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('249', 'aHeroLeggings(W)', '1', '4', '2', '18', '25', '1', '1', '1', '1', '3000', '0', '12', '6', '-22000', '1500', '7', '0', '0', '2', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('250', 'eHeroLeggings(M)', '1', '4', '2', '18', '25', '1', '1', '1', '1', '3000', '0', '8', '4', '-22000', '1500', '5', '0', '0', '1', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('251', 'eHeroLeggings(W)', '1', '4', '2', '18', '25', '1', '1', '1', '1', '3000', '0', '12', '5', '-22000', '1500', '6', '0', '0', '2', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('252', 'AresdenHeroCape+1', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '3', '-2000', '200', '4', '0', '0', '0', '0', '0', '-1', '13', '0');
INSERT INTO `item_config` VALUES ('253', 'ElvineHeroCape+1', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '4', '-2000', '200', '5', '0', '0', '0', '0', '0', '-1', '13', '0');
INSERT INTO `item_config` VALUES ('254', 'Cape+1', '1', '12', '2', '2', '1', '1', '1', '1', '1', '300', '0', '20', '5', '1000', '200', '6', '0', '0', '0', '0', '0', '-1', '12', '0');
INSERT INTO `item_config` VALUES ('255', 'Shoes', '1', '5', '2', '1', '1', '1', '1', '1', '1', '300', '0', '5', '0', '20', '200', '1', '0', '0', '0', '0', '0', '0', '12', '0');
INSERT INTO `item_config` VALUES ('256', 'LongBoots', '1', '5', '2', '1', '1', '1', '1', '1', '1', '300', '0', '5', '1', '100', '500', '2', '0', '0', '0', '0', '0', '0', '12', '0');
INSERT INTO `item_config` VALUES ('257', 'Shirt(M)', '1', '3', '2', '1', '1', '1', '1', '1', '1', '300', '0', '7', '0', '20', '100', '1', '0', '0', '1', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('258', 'Hauberk(M)', '1', '3', '2', '8', '10', '0', '0', '0', '0', '300', '0', '7', '1', '400', '1200', '2', '0', '0', '1', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('259', 'LeatherArmor(M)', '1', '2', '2', '10', '10', '0', '0', '0', '0', '400', '0', '9', '0', '500', '1500', '1', '0', '0', '1', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('260', 'ChainMail(M)', '1', '2', '2', '30', '32', '0', '0', '0', '0', '1000', '0', '9', '1', '1200', '3000', '2', '0', '0', '1', '-12', '-12', '0', '6', '0');
INSERT INTO `item_config` VALUES ('261', 'ScaleMail(M)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '600', '0', '9', '2', '900', '2000', '3', '0', '0', '1', '-8', '-8', '0', '6', '0');
INSERT INTO `item_config` VALUES ('262', 'PlateMail(M)', '1', '2', '2', '37', '40', '0', '0', '0', '0', '3000', '0', '9', '3', '4500', '10000', '4', '0', '0', '1', '-10', '-10', '0', '6', '0');
INSERT INTO `item_config` VALUES ('263', 'Trousers(M)', '1', '4', '2', '1', '1', '1', '1', '1', '1', '300', '0', '8', '0', '80', '100', '1', '0', '0', '1', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('264', 'KneeTrousers(M)', '1', '4', '2', '1', '1', '1', '1', '1', '1', '300', '0', '8', '1', '20', '100', '2', '0', '0', '1', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('265', 'ChainHose(M)', '1', '4', '2', '6', '10', '1', '1', '1', '1', '500', '0', '8', '2', '400', '1000', '3', '0', '0', '1', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('266', 'PlateLeggings(M)', '1', '4', '2', '12', '20', '1', '1', '1', '1', '1000', '0', '8', '3', '1000', '2000', '4', '0', '0', '1', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('267', 'Chemise(W)', '1', '3', '2', '1', '1', '1', '1', '1', '1', '300', '0', '11', '0', '200', '100', '1', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('268', 'Shirt(W)', '1', '3', '2', '1', '1', '1', '1', '1', '1', '300', '0', '11', '1', '20', '100', '2', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('269', 'Hauberk(W)', '1', '3', '2', '8', '10', '0', '0', '0', '0', '300', '0', '11', '2', '400', '1200', '3', '0', '0', '2', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('270', 'Bodice(W)', '1', '2', '2', '1', '1', '1', '1', '1', '1', '400', '0', '13', '0', '150', '200', '1', '0', '0', '2', '-1', '-1', '0', '11', '0');
INSERT INTO `item_config` VALUES ('271', 'LongBodice(W)', '1', '2', '2', '1', '1', '1', '1', '1', '1', '400', '0', '13', '1', '180', '200', '2', '0', '0', '2', '-1', '-1', '0', '11', '0');
INSERT INTO `item_config` VALUES ('272', 'LeatherArmor(W)', '1', '2', '2', '10', '10', '0', '0', '0', '0', '400', '0', '13', '2', '500', '1500', '3', '0', '0', '2', '-5', '-5', '0', '6', '0');
INSERT INTO `item_config` VALUES ('273', 'ChainMail(W)', '1', '2', '2', '30', '32', '0', '0', '0', '0', '1000', '0', '13', '3', '1200', '3000', '4', '0', '0', '2', '-12', '-12', '0', '6', '0');
INSERT INTO `item_config` VALUES ('274', 'ScaleMail(W)', '1', '2', '2', '20', '20', '0', '0', '0', '0', '600', '0', '13', '4', '900', '2000', '5', '0', '0', '2', '-8', '-8', '0', '6', '0');
INSERT INTO `item_config` VALUES ('275', 'PlateMail(W)', '1', '2', '2', '37', '40', '0', '0', '0', '0', '3000', '0', '13', '5', '4500', '10000', '6', '0', '0', '2', '-10', '-10', '0', '6', '0');
INSERT INTO `item_config` VALUES ('276', 'Skirt(W)', '1', '4', '2', '1', '1', '1', '1', '1', '1', '300', '0', '12', '0', '200', '100', '1', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('277', 'Trousers(W)', '1', '4', '2', '1', '1', '1', '1', '1', '1', '300', '0', '12', '1', '80', '100', '2', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('278', 'KneeTrousers(W)', '1', '4', '2', '1', '1', '1', '1', '1', '1', '300', '0', '12', '2', '20', '100', '3', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('279', 'ChainHose(W)', '1', '4', '2', '6', '10', '1', '1', '1', '1', '500', '0', '12', '3', '400', '1000', '4', '0', '0', '2', '-3', '-3', '0', '6', '0');
INSERT INTO `item_config` VALUES ('280', 'PlateLeggings(W)', '1', '4', '2', '12', '20', '1', '1', '1', '1', '1000', '0', '12', '4', '1000', '2000', '5', '0', '0', '2', '-6', '-6', '0', '6', '0');
INSERT INTO `item_config` VALUES ('281', 'Tunic(M)', '1', '2', '2', '3', '1', '1', '1', '1', '1', '300', '0', '9', '4', '350', '500', '5', '0', '0', '1', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('282', 'BloodSword', '1', '9', '19', '4', '7', '1', '4', '7', '1', '8000', '5', '1', '7', '-31000', '13100', '8', '11', '0', '0', '0', '0', '8', '1', '9');
INSERT INTO `item_config` VALUES ('283', 'BloodAxe', '1', '8', '19', '3', '6', '2', '3', '6', '2', '5000', '5', '15', '1', '-25000', '6100', '21', '8', '0', '0', '0', '0', '10', '1', '9');
INSERT INTO `item_config` VALUES ('284', 'BloodRapier', '1', '8', '19', '2', '5', '2', '2', '5', '2', '5000', '5', '1', '6', '-25000', '1100', '7', '3', '0', '0', '0', '0', '9', '1', '9');
INSERT INTO `item_config` VALUES ('285', 'IronIngot', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '76', '-500', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('286', 'SuperCoal', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '88', '-200', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('287', 'UltraCoal', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '88', '-500', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('288', 'GoldIngot', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '74', '-3000', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('289', 'SilverIngot', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '75', '-2000', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('290', 'BlondeIngot', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '77', '-1000', '500', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('291', 'MithralIngot', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '78', '-6000', '800', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('292', 'BlondeStone', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '79', '-160', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('293', 'Mithral', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '80', '-50', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('294', 'ArenaTicket', '3', '0', '11', '4', '11', '0', '0', '0', '0', '1', '0', '6', '89', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('295', 'ArenaTicket(2)', '3', '0', '11', '4', '12', '0', '0', '0', '0', '1', '0', '6', '89', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('296', 'ArenaTicket(3)', '3', '0', '11', '4', '13', '0', '0', '0', '0', '1', '0', '6', '89', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('297', 'ArenaTicket(4)', '3', '0', '11', '4', '14', '0', '0', '0', '0', '1', '0', '6', '89', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('298', 'Bouquette', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '81', '1000', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('299', 'FlowerBasket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '82', '1500', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('300', 'Flowerpot', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '83', '500', '180', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('301', 'ArenaTicket(5)', '3', '0', '11', '4', '15', '0', '0', '0', '0', '1', '0', '6', '89', '-10', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('302', 'ArenaTicket(6)', '3', '0', '11', '4', '16', '0', '0', '0', '0', '1', '0', '6', '89', '-10', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('303', 'ArenaTicket(7)', '3', '0', '11', '4', '17', '0', '0', '0', '0', '1', '0', '6', '89', '-10', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('304', 'ArenaTicket(8)', '3', '0', '11', '4', '18', '0', '0', '0', '0', '1', '0', '6', '89', '-10', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('305', 'ArenaTicket(9)', '3', '0', '11', '4', '19', '0', '0', '0', '0', '1', '0', '6', '89', '-10', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('306', 'DemonEye', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '93', '-3000', '530', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('307', 'DemonHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '94', '-5000', '1500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('308', 'DemonMeat', '7', '0', '7', '4', '8', '50', '0', '0', '0', '1', '0', '6', '95', '-2000', '1200', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('309', 'DemonLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '96', '-6000', '900', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('310', 'UnicornHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '97', '-5000', '230', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('311', 'UnicornHorn', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '98', '-50000', '250', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('312', 'UnicornMeat', '7', '0', '7', '4', '8', '50', '0', '0', '0', '1', '0', '6', '99', '-2000', '500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('313', 'UnicornLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '100', '-6000', '650', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('314', 'WerewolfHeart', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '101', '-210', '350', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('315', 'WerewolfNail', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '102', '-140', '290', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('316', 'WerewolfMeat', '7', '0', '7', '8', '4', '50', '0', '0', '0', '1', '0', '6', '103', '-250', '500', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('317', 'WerewolfTail', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '104', '-300', '550', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('318', 'WerewolfTeeth', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '105', '-140', '290', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('319', 'WerewolfLeather', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '106', '-820', '450', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('320', 'WerewolfClaw', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '107', '-140', '290', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('321', 'BattleAxe', '1', '9', '1', '3', '8', '0', '3', '9', '0', '1500', '0', '15', '6', '3500', '9000', '26', '13', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('322', 'RedCarp', '7', '0', '7', '8', '4', '30', '0', '0', '0', '1', '0', '6', '14', '-1200', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('323', 'GreenCarp', '7', '0', '7', '8', '4', '40', '0', '0', '0', '1', '0', '6', '15', '-1500', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('324', 'GoldCarp', '7', '0', '7', '8', '4', '60', '0', '0', '0', '1', '0', '6', '16', '-3000', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('325', 'CrucianCarp', '7', '0', '7', '8', '4', '0', '0', '0', '0', '1', '0', '6', '12', '-200', '30', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('326', 'BlueSeaBream', '7', '0', '7', '8', '4', '50', '0', '0', '0', '1', '0', '6', '84', '-2000', '80', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('327', 'Salmon', '7', '0', '7', '8', '4', '10', '0', '0', '0', '1', '0', '6', '85', '-800', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('328', 'RedSeaBream', '7', '0', '7', '8', '4', '50', '0', '0', '0', '1', '0', '6', '86', '-2000', '80', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('329', 'GrayMullet', '7', '0', '7', '8', '4', '5', '0', '0', '0', '1', '0', '6', '87', '-500', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('330', 'BattleAxe+1', '1', '9', '1', '3', '8', '1', '3', '9', '1', '2000', '0', '15', '6', '6000', '9000', '26', '13', '110', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('331', 'BattleAxe+2', '1', '9', '1', '3', '8', '2', '3', '9', '2', '4000', '0', '15', '6', '-48000', '9000', '26', '13', '0', '0', '0', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('332', 'Sabre+2', '1', '8', '1', '1', '8', '2', '1', '8', '2', '1000', '0', '1', '3', '-2400', '1200', '4', '5', '20', '0', '-1', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('333', 'Robe(M)', '1', '2', '2', '12', '1', '0', '14', '100', '0', '3000', '0', '9', '5', '2000', '1000', '6', '0', '0', '1', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('334', 'Robe(W)', '1', '2', '2', '12', '1', '0', '14', '100', '0', '3000', '0', '13', '6', '2000', '1000', '7', '0', '0', '2', '0', '0', '0', '11', '0');
INSERT INTO `item_config` VALUES ('335', 'Helm(M)', '1', '1', '2', '5', '10', '0', '0', '0', '0', '1500', '0', '21', '0', '800', '5200', '4', '0', '0', '1', '-4', '-4', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('336', 'FullHelm(M)', '1', '1', '2', '10', '20', '0', '0', '0', '0', '2000', '0', '21', '1', '1500', '8500', '1', '0', '0', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('337', 'Helm(W)', '1', '1', '2', '5', '10', '0', '0', '0', '0', '1500', '0', '21', '0', '800', '5200', '4', '0', '0', '2', '-4', '-4', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('338', 'FullHelm(W)', '1', '1', '2', '10', '20', '0', '0', '0', '0', '2000', '0', '21', '1', '1500', '8500', '1', '0', '0', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('339', 'XelimaBlade', '1', '9', '24', '2', '11', '2', '2', '12', '2', '8000', '1', '1', '13', '-31000', '12000', '11', '11', '0', '0', '60', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('340', 'XelimaAxe', '1', '9', '24', '3', '8', '1', '3', '9', '1', '5000', '1', '1', '12', '-31000', '12000', '26', '13', '0', '0', '60', '0', '10', '1', '0');
INSERT INTO `item_config` VALUES ('341', 'XelimaRapier', '1', '8', '24', '2', '6', '1', '2', '6', '1', '5000', '1', '1', '14', '-25000', '1100', '7', '3', '0', '0', '60', '0', '9', '1', '0');
INSERT INTO `item_config` VALUES ('342', 'SwordofMedusa', '1', '9', '24', '2', '11', '2', '2', '12', '2', '7000', '3', '1', '16', '-31000', '10000', '11', '10', '0', '0', '60', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('343', 'SwordofIceElemental', '1', '9', '24', '2', '11', '2', '2', '12', '2', '7000', '2', '1', '15', '-31000', '10000', '11', '10', '0', '0', '60', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('344', 'GiantSword', '1', '9', '1', '2', '11', '3', '2', '12', '3', '1500', '0', '1', '18', '8000', '13000', '13', '12', '100', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('345', 'DemonSlayer', '1', '9', '1', '4', '7', '2', '4', '8', '2', '5000', '0', '1', '17', '-25000', '12000', '13', '12', '0', '0', '0', '0', '8', '1', '9');
INSERT INTO `item_config` VALUES ('346', 'CompositeBow', '1', '9', '3', '1', '6', '0', '1', '6', '0', '1200', '0', '2', '2', '3000', '4000', '41', '5', '70', '0', '0', '0', '6', '3', '0');
INSERT INTO `item_config` VALUES ('347', 'DarkElfBow', '1', '9', '3', '2', '7', '0', '2', '7', '0', '2500', '0', '2', '3', '-8000', '8000', '40', '4', '0', '0', '0', '0', '6', '3', '0');
INSERT INTO `item_config` VALUES ('348', 'MerienShield', '1', '7', '25', '50', '1', '1', '1', '1', '1', '1600', '52', '3', '9', '-45000', '4000', '9', '0', '0', '0', '60', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('349', 'MerienPlateMailM', '1', '2', '25', '60', '45', '0', '0', '0', '0', '5000', '50', '9', '3', '-45000', '10000', '4', '0', '0', '1', '60', '0', '0', '6', '5');
INSERT INTO `item_config` VALUES ('350', 'MerienPlateMailW', '1', '2', '25', '60', '45', '0', '0', '0', '0', '5000', '50', '13', '5', '-45000', '10000', '6', '0', '0', '2', '60', '0', '0', '6', '5');
INSERT INTO `item_config` VALUES ('351', 'GM-Shield', '1', '7', '25', '50', '1', '1', '1', '1', '1', '1600', '53', '3', '7', '-1000', '1000', '8', '0', '0', '0', '60', '0', '11', '5', '0');
INSERT INTO `item_config` VALUES ('352', 'RingoftheXelima', '1', '10', '14', '3', '7', '0', '0', '0', '0', '300', '0', '16', '25', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('353', 'RingoftheAbaddon', '1', '10', '14', '3', '10', '0', '0', '0', '0', '300', '0', '16', '26', '-19000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('354', 'RingofOgrepower', '1', '10', '14', '3', '2', '0', '0', '0', '0', '300', '0', '16', '29', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('355', 'RingofDemonpower', '1', '10', '14', '3', '4', '0', '0', '0', '0', '300', '0', '16', '28', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('356', 'RingofWizard', '1', '10', '14', '6', '1', '0', '0', '0', '0', '300', '0', '16', '30', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('357', 'RingofMage', '1', '10', '14', '6', '2', '0', '0', '0', '0', '300', '0', '16', '31', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('358', 'RingofGrandMage', '1', '10', '14', '6', '3', '0', '0', '0', '0', '300', '0', '16', '32', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('359', 'KnecklaceOfLightPro', '1', '6', '14', '7', '25', '0', '0', '0', '0', '300', '0', '16', '33', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('360', 'KnecklaceOfFirePro', '1', '6', '14', '9', '25', '0', '0', '0', '0', '300', '0', '16', '34', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('361', 'KnecklaceOfPoisonPro', '1', '6', '14', '11', '50', '0', '0', '0', '0', '300', '0', '16', '35', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('362', 'KnecklaceOfSufferent', '1', '6', '14', '11', '110', '0', '0', '0', '0', '300', '0', '16', '36', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('363', 'KnecklaceOfMedusa', '1', '6', '14', '11', '500', '0', '0', '0', '0', '300', '0', '16', '36', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '5');
INSERT INTO `item_config` VALUES ('364', 'KnecklaceOfIcePro', '1', '6', '14', '10', '25', '0', '0', '0', '0', '300', '0', '16', '37', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('365', 'KnecklaceOfIceEle', '1', '6', '14', '10', '50', '0', '0', '0', '0', '300', '0', '16', '38', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('366', 'KnecklaceOfAirEle', '1', '6', '14', '7', '50', '0', '0', '0', '0', '300', '0', '16', '40', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('367', 'KnecklaceOfEfreet', '1', '6', '14', '9', '50', '0', '0', '0', '0', '300', '0', '16', '41', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('368', 'NecklaceOfBeholder', '1', '6', '14', '9', '50', '0', '0', '0', '0', '300', '0', '16', '47', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('369', 'NecklaceOfStoneGol', '1', '6', '14', '4', '25', '0', '0', '0', '0', '300', '0', '16', '48', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('370', 'NecklaceOfLiche', '1', '6', '14', '2', '15', '0', '0', '0', '0', '300', '0', '16', '51', '-10000', '600', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('371', 'ZemstoneofSacrifice', '0', '0', '26', '0', '0', '0', '0', '0', '0', '3', '0', '16', '39', '-5000', '5000', '-1', '0', '0', '0', '0', '0', '-1', '0', '0');
INSERT INTO `item_config` VALUES ('372', 'GreenBall', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '123', '-5000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('373', 'RedBall', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '124', '-5000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('374', 'YellowBall', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '125', '-5000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('375', 'BlueBall', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '126', '-5000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('376', 'PearlBall', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '127', '-5000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('377', 'StoneOfXelima', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '128', '-10000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('378', 'StoneOfMerien', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '6', '129', '-10000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('379', 'AresdenMinePotion', '7', '0', '4', '2', '12', '10', '0', '0', '0', '1', '0', '6', '1', '10', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('380', 'ElvineMinePotion', '7', '0', '4', '2', '12', '10', '0', '0', '0', '1', '0', '6', '1', '10', '30', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('381', 'UnfreezePotion', '7', '0', '28', '2', '12', '10', '0', '0', '0', '1', '0', '6', '130', '-200', '50', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('382', 'KnightRapier', '1', '8', '1', '1', '7', '2', '1', '7', '2', '1100', '0', '1', '6', '3200', '1200', '7', '3', '95', '0', '0', '0', '9', '1', '11');
INSERT INTO `item_config` VALUES ('383', 'KnightGreatSword', '1', '9', '1', '2', '8', '2', '2', '10', '2', '1200', '0', '1', '10', '3500', '5200', '11', '8', '85', '0', '-8', '5', '8', '1', '11');
INSERT INTO `item_config` VALUES ('384', 'KnightFlameberge', '1', '9', '1', '2', '10', '2', '2', '12', '2', '1200', '0', '1', '11', '3700', '6000', '12', '10', '95', '0', '-15', '10', '8', '1', '11');
INSERT INTO `item_config` VALUES ('385', 'KnightWarAxe', '1', '8', '1', '2', '6', '2', '2', '8', '2', '1200', '0', '15', '1', '3000', '4400', '21', '8', '85', '0', '0', '0', '10', '1', '11');
INSERT INTO `item_config` VALUES ('386', 'KnightPlateMail(M)', '1', '2', '2', '40', '42', '0', '0', '0', '0', '3500', '0', '9', '3', '6000', '10000', '4', '0', '85', '1', '-10', '-10', '0', '6', '11');
INSERT INTO `item_config` VALUES ('387', 'KnightPlateMail(W)', '1', '2', '2', '40', '42', '0', '0', '0', '0', '3500', '0', '13', '5', '6000', '10000', '6', '0', '85', '2', '-10', '-10', '0', '6', '11');
INSERT INTO `item_config` VALUES ('388', 'KnightPlateLeg(M)', '1', '4', '2', '15', '22', '1', '1', '1', '1', '1100', '0', '8', '3', '3000', '2000', '4', '0', '80', '1', '-6', '-6', '0', '6', '11');
INSERT INTO `item_config` VALUES ('389', 'KnightPlateLeg(W)', '1', '4', '2', '15', '22', '1', '1', '1', '1', '1100', '0', '12', '4', '3000', '2000', '5', '0', '80', '2', '-6', '-6', '0', '6', '11');
INSERT INTO `item_config` VALUES ('390', 'KnightFullHelm(M)', '1', '1', '2', '12', '22', '0', '0', '0', '0', '2000', '0', '21', '1', '3500', '8500', '1', '0', '80', '1', '-7', '-7', '-1', '6', '11');
INSERT INTO `item_config` VALUES ('391', 'KnightFullHelm(W)', '1', '1', '2', '12', '22', '0', '0', '0', '0', '2000', '0', '21', '1', '3500', '8500', '1', '0', '80', '2', '-7', '-7', '-1', '6', '11');
INSERT INTO `item_config` VALUES ('392', 'WizardHauberk(M)', '1', '3', '2', '12', '12', '0', '14', '100', '0', '1000', '0', '7', '1', '2400', '1200', '2', '0', '90', '1', '-3', '-3', '0', '6', '11');
INSERT INTO `item_config` VALUES ('393', 'WizardHauberk(W)', '1', '3', '2', '12', '12', '0', '14', '100', '0', '1000', '0', '11', '2', '2400', '1200', '3', '0', '90', '2', '-3', '-3', '0', '6', '11');
INSERT INTO `item_config` VALUES ('394', 'WizMagicWand(MS20)', '1', '8', '13', '1', '6', '0', '20', '0', '0', '3600', '10', '17', '1', '6000', '1000', '36', '3', '95', '0', '0', '0', '21', '8', '4');
INSERT INTO `item_config` VALUES ('395', 'WizMagicWand(MS10)', '1', '8', '13', '1', '6', '0', '10', '0', '0', '3600', '10', '17', '1', '5500', '1000', '36', '3', '90', '0', '0', '0', '21', '8', '4');
INSERT INTO `item_config` VALUES ('396', 'WizardRobe(M)', '1', '2', '2', '12', '1', '0', '14', '100', '0', '3000', '0', '9', '5', '3000', '1000', '6', '0', '80', '1', '0', '0', '0', '13', '11');
INSERT INTO `item_config` VALUES ('397', 'WizardRobe(W)', '1', '2', '2', '12', '1', '0', '14', '100', '0', '3000', '0', '13', '6', '3000', '1000', '7', '0', '80', '2', '0', '0', '0', '13', '11');
INSERT INTO `item_config` VALUES ('398', 'KnightHauberk(M)', '1', '3', '2', '12', '12', '0', '11', '100', '0', '1000', '0', '7', '1', '2400', '1200', '2', '0', '70', '1', '-3', '-3', '0', '6', '11');
INSERT INTO `item_config` VALUES ('399', 'KnightHauberk(W)', '1', '3', '2', '12', '12', '0', '11', '100', '0', '1000', '0', '11', '2', '2400', '1200', '3', '0', '70', '2', '-3', '-3', '0', '6', '11');
INSERT INTO `item_config` VALUES ('400', 'SangAhHauberk', '1', '3', '2', '18', '18', '0', '0', '0', '0', '30000', '0', '7', '1', '-2400', '1200', '2', '0', '0', '1', '-3', '-3', '0', '6', '6');
INSERT INTO `item_config` VALUES ('401', 'SangAhFullHel', '1', '1', '2', '17', '27', '0', '0', '0', '0', '30000', '0', '21', '1', '-3500', '8500', '1', '0', '0', '1', '-7', '-7', '-1', '6', '6');
INSERT INTO `item_config` VALUES ('402', 'SangAhLeggings', '1', '4', '2', '21', '28', '1', '1', '1', '1', '30000', '0', '8', '3', '-3000', '2000', '4', '0', '0', '1', '-6', '-6', '0', '6', '6');
INSERT INTO `item_config` VALUES ('403', 'SangAhFlameberge', '1', '9', '1', '4', '7', '0', '4', '7', '0', '50000', '0', '1', '11', '-3700', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('404', 'SangAhPlateMail', '1', '2', '2', '53', '55', '0', '0', '0', '0', '30000', '0', '9', '3', '-1000', '10000', '4', '0', '0', '1', '-10', '-10', '0', '6', '6');
INSERT INTO `item_config` VALUES ('405', 'SangAhJewel', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '16', '42', '-5000', '200', '1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('406', 'DarkKnightHauberk', '1', '3', '2', '18', '18', '0', '0', '0', '0', '30000', '0', '7', '1', '-2400', '1200', '2', '0', '0', '1', '-3', '-3', '0', '6', '6');
INSERT INTO `item_config` VALUES ('407', 'DarkKnightFullHelm', '1', '1', '2', '17', '27', '0', '0', '0', '0', '30000', '0', '21', '1', '-3500', '8500', '1', '0', '0', '1', '-7', '-7', '-1', '6', '6');
INSERT INTO `item_config` VALUES ('408', 'DarkKnightLeggings', '1', '4', '2', '21', '28', '1', '1', '1', '1', '30000', '0', '8', '3', '-3000', '2000', '4', '0', '0', '1', '-6', '-6', '0', '6', '6');
INSERT INTO `item_config` VALUES ('409', 'DarkKnightFlameberge', '1', '9', '1', '4', '7', '0', '4', '7', '0', '30000', '0', '1', '11', '-3700', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('410', 'DarkKnightPlateMail', '1', '2', '2', '53', '55', '0', '0', '0', '0', '30000', '0', '9', '3', '-6000', '10000', '4', '0', '0', '1', '-10', '-10', '0', '6', '6');
INSERT INTO `item_config` VALUES ('411', 'DarkMageHauberk', '1', '3', '2', '18', '18', '0', '0', '0', '0', '30000', '0', '7', '1', '-2400', '1200', '2', '0', '0', '1', '-3', '-3', '0', '6', '6');
INSERT INTO `item_config` VALUES ('412', 'DarkMageChainMail', '1', '2', '2', '36', '38', '0', '0', '0', '0', '30000', '0', '9', '1', '-1200', '3000', '2', '0', '0', '1', '-12', '-12', '0', '6', '6');
INSERT INTO `item_config` VALUES ('413', 'DarkMageLeggings', '1', '4', '2', '21', '28', '1', '1', '1', '1', '30000', '0', '8', '3', '-3000', '2000', '4', '0', '0', '1', '-6', '-6', '0', '6', '6');
INSERT INTO `item_config` VALUES ('414', 'DarkMageMagicStaff', '1', '8', '13', '1', '6', '0', '25', '0', '0', '30000', '10', '17', '1', '-6000', '1000', '36', '3', '0', '0', '0', '0', '21', '8', '6');
INSERT INTO `item_config` VALUES ('415', 'DarkMageRobe', '1', '2', '2', '22', '20', '0', '14', '100', '0', '30000', '0', '9', '5', '-2000', '1000', '6', '0', '0', '1', '0', '0', '0', '11', '6');
INSERT INTO `item_config` VALUES ('416', 'DarkMageLedderArmor', '1', '2', '2', '24', '22', '0', '0', '0', '0', '30000', '0', '9', '0', '-2000', '1500', '1', '0', '0', '1', '-5', '-5', '0', '6', '6');
INSERT INTO `item_config` VALUES ('417', 'DarkKnightRapier', '1', '8', '1', '1', '7', '0', '1', '7', '0', '30000', '0', '1', '6', '-3000', '1100', '7', '3', '0', '0', '0', '0', '9', '1', '6');
INSERT INTO `item_config` VALUES ('418', 'DarkKnightGreatSword', '1', '9', '1', '2', '8', '0', '2', '10', '0', '30000', '0', '1', '10', '-3000', '5200', '11', '8', '0', '0', '-8', '5', '8', '1', '6');
INSERT INTO `item_config` VALUES ('419', 'DarkMageScaleMail', '1', '2', '2', '32', '30', '0', '0', '0', '0', '30000', '0', '9', '2', '-1000', '2000', '3', '0', '0', '1', '-8', '-8', '0', '6', '6');
INSERT INTO `item_config` VALUES ('420', 'Songpyon', '7', '0', '22', '900', '0', '0', '0', '0', '0', '1', '0', '6', '115', '-2400', '20', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('421', 'Ginseng', '7', '0', '28', '2', '12', '10', '0', '0', '0', '1', '0', '6', '114', '-600', '50', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('422', 'BeefRibSet', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '116', '-50000', '5000', '-1', '0', '0', '0', '0', '0', '-1', '0', '0');
INSERT INTO `item_config` VALUES ('423', 'Wine', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '117', '-25000', '250', '-1', '0', '0', '0', '0', '0', '-1', '0', '0');
INSERT INTO `item_config` VALUES ('424', 'DarkKnightHauberkW', '1', '3', '2', '18', '18', '0', '0', '0', '0', '30000', '0', '11', '2', '-2400', '1200', '3', '0', '0', '2', '-3', '-3', '0', '6', '6');
INSERT INTO `item_config` VALUES ('425', 'DarkKnightFullHelmW', '1', '1', '2', '17', '27', '0', '0', '0', '0', '30000', '0', '21', '1', '-3500', '8500', '1', '0', '0', '2', '-7', '-7', '-1', '6', '6');
INSERT INTO `item_config` VALUES ('426', 'DarkKnightLeggingsW', '1', '4', '2', '21', '28', '1', '1', '1', '1', '30000', '0', '12', '4', '-3000', '2000', '5', '0', '0', '2', '-6', '-6', '0', '6', '6');
INSERT INTO `item_config` VALUES ('427', 'DarkKnightFlamebergW', '1', '9', '1', '4', '7', '0', '4', '7', '0', '30000', '0', '1', '11', '-3700', '6000', '12', '10', '0', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('428', 'DarkKnightPlateMailW', '1', '2', '2', '53', '55', '0', '0', '0', '0', '30000', '0', '13', '5', '-6000', '10000', '6', '0', '0', '2', '-10', '-10', '0', '6', '6');
INSERT INTO `item_config` VALUES ('429', 'DarkMageHauberkW', '1', '3', '2', '18', '18', '0', '0', '0', '0', '30000', '0', '11', '2', '-2400', '1200', '3', '0', '0', '2', '-3', '-3', '0', '6', '6');
INSERT INTO `item_config` VALUES ('430', 'DarkMageChainMailW', '1', '2', '2', '36', '38', '0', '0', '0', '0', '30000', '0', '13', '3', '-1200', '3000', '4', '0', '0', '2', '-12', '-12', '0', '6', '6');
INSERT INTO `item_config` VALUES ('431', 'DarkMageLeggingsW', '1', '4', '2', '21', '28', '1', '1', '1', '1', '30000', '0', '12', '4', '-3000', '2000', '5', '0', '0', '2', '-6', '-6', '0', '6', '6');
INSERT INTO `item_config` VALUES ('432', 'DarkMageMagicStaffW', '1', '8', '13', '1', '6', '0', '25', '0', '0', '30000', '10', '17', '1', '-6000', '1000', '36', '3', '0', '0', '0', '0', '21', '8', '6');
INSERT INTO `item_config` VALUES ('433', 'DarkMageRobeW', '1', '2', '2', '22', '20', '0', '14', '100', '0', '30000', '0', '13', '6', '-2000', '100', '0', '7', '0', '0', '2', '0', '0', '0', '11');
INSERT INTO `item_config` VALUES ('434', 'RingofArcmage', '1', '10', '14', '6', '4', '0', '0', '0', '0', '300', '0', '16', '49', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('435', 'RingofDragonpower', '1', '10', '14', '3', '5', '0', '0', '0', '0', '300', '0', '16', '50', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('436', 'SangAhGiantSword', '1', '9', '1', '2', '10', '2', '2', '12', '2', '50000', '0', '1', '18', '-3700', '6000', '13', '10', '120', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('437', 'DarkKnightGiantSword', '1', '9', '1', '2', '10', '2', '2', '12', '2', '30000', '0', '1', '18', '-3700', '6000', '13', '10', '120', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('438', 'DarkMageMagicWand', '1', '8', '13', '1', '6', '0', '28', '0', '0', '30000', '10', '17', '0', '-6000', '1000', '35', '3', '120', '0', '0', '0', '21', '8', '6');
INSERT INTO `item_config` VALUES ('439', '5000GoldPocket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '118', '-10000', '500', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('440', '10000GoldPocket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '119', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('441', '50000GoldPocket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '120', '-100000', '2000', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('442', '100000GoldPocket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '121', '-200000', '3000', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('443', '1000000GoldPocket', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '122', '-2000000', '4000', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('444', 'BlackKnightTemple', '1', '9', '1', '2', '10', '2', '2', '12', '2', '30000', '0', '1', '20', '-3700', '6000', '14', '10', '120', '0', '-15', '10', '8', '1', '6');
INSERT INTO `item_config` VALUES ('445', 'BlackMageTemple', '1', '8', '13', '1', '6', '0', '28', '0', '0', '30000', '10', '17', '2', '-6000', '1000', '37', '3', '120', '0', '0', '0', '21', '8', '6');
INSERT INTO `item_config` VALUES ('446', 'Horned-Helm(M)', '1', '1', '2', '17', '24', '0', '0', '0', '0', '3500', '0', '21', '2', '4000', '16000', '5', '0', '120', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('447', 'Wings-Helm(M)', '1', '1', '2', '15', '22', '0', '0', '0', '0', '2500', '0', '21', '3', '5000', '13000', '6', '0', '100', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('448', 'Wizard-Cap(M)', '1', '1', '2', '5', '10', '0', '14', '110', '0', '500', '0', '21', '4', '1500', '1500', '7', '0', '90', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('449', 'Wizard-Hat(M)', '1', '1', '2', '10', '15', '0', '14', '130', '0', '800', '0', '21', '5', '3000', '1500', '8', '0', '120', '1', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('450', 'Horned-Helm(W)', '1', '1', '2', '17', '24', '0', '0', '0', '0', '3500', '0', '21', '2', '4000', '16000', '5', '0', '120', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('451', 'Wings-Helm(W)', '1', '1', '2', '15', '22', '0', '0', '0', '0', '2500', '0', '21', '3', '5000', '13000', '6', '0', '100', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('452', 'Wizard-Cap(W)', '1', '1', '2', '5', '10', '0', '14', '110', '0', '500', '0', '21', '4', '1500', '1500', '7', '0', '90', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('453', 'Wizard-Hat(W)', '1', '1', '2', '10', '15', '0', '14', '130', '0', '800', '0', '21', '5', '3000', '1500', '8', '0', '120', '2', '-7', '-7', '-1', '6', '0');
INSERT INTO `item_config` VALUES ('454', 'Hammer', '1', '9', '1', '3', '7', '0', '3', '9', '0', '2000', '0', '15', '7', '6000', '9000', '30', '12', '0', '0', '0', '0', '14', '1', '0');
INSERT INTO `item_config` VALUES ('455', 'BattleHammer', '1', '9', '1', '3', '7', '2', '3', '9', '2', '4000', '0', '15', '8', '9000', '12000', '31', '14', '110', '0', '0', '0', '14', '1', '0');
INSERT INTO `item_config` VALUES ('456', 'GiantBattleHammer', '1', '9', '1', '3', '9', '3', '3', '10', '3', '6000', '0', '15', '8', '-15000', '14000', '31', '14', '110', '0', '0', '0', '14', '1', '9');
INSERT INTO `item_config` VALUES ('457', 'ThirdMemorialRing', '1', '10', '4', '0', '0', '0', '10', '0', '0', '300', '0', '16', '11', '-1000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('458', 'SantaCostume(M)', '1', '13', '14', '10', '25', '0', '0', '0', '0', '1500', '0', '9', '6', '-18000', '1000', '7', '0', '0', '1', '0', '0', '0', '15', '0');
INSERT INTO `item_config` VALUES ('459', 'SantaCostume(W)', '1', '13', '14', '10', '25', '0', '0', '0', '0', '1500', '0', '13', '7', '-18000', '1000', '8', '0', '0', '2', '0', '0', '0', '15', '0');
INSERT INTO `item_config` VALUES ('460', 'RedCandy', '7', '0', '4', '3', '8', '200', '0', '0', '0', '1', '0', '6', '131', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('461', 'BlueCandy', '7', '0', '5', '4', '8', '200', '0', '0', '0', '1', '0', '6', '132', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('462', 'GreenCandy', '7', '0', '6', '4', '8', '200', '0', '0', '0', '1', '0', '6', '133', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('463', 'FarmingManual', '3', '0', '9', '2', '20', '0', '0', '0', '0', '0', '0', '6', '92', '100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('464', 'SeedBag(WaterMelon)', '11', '0', '30', '1', '20', '0', '0', '0', '0', '1', '0', '6', '137', '100', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('465', 'SeedBag(Pumpkin)', '11', '0', '30', '2', '20', '0', '0', '0', '0', '1', '0', '6', '137', '100', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('466', 'SeedBag(Garlic)', '11', '0', '30', '3', '30', '0', '0', '0', '0', '1', '0', '6', '137', '150', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('467', 'SeedBag(Barley)', '11', '0', '30', '4', '30', '0', '0', '0', '0', '1', '0', '6', '137', '150', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('468', 'SeedBag(Carrot)', '11', '0', '30', '5', '40', '0', '0', '0', '0', '1', '0', '6', '137', '200', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('469', 'SeedBag(Radish)', '11', '0', '30', '6', '40', '0', '0', '0', '0', '1', '0', '6', '137', '200', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('470', 'SeedBag(Corn)', '11', '0', '30', '7', '50', '0', '0', '0', '0', '1', '0', '6', '137', '250', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('471', 'SeedBag(CBellflower)', '11', '0', '30', '8', '50', '0', '0', '0', '0', '1', '0', '6', '137', '250', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('472', 'SeedBag(Melone)', '11', '0', '30', '9', '60', '0', '0', '0', '0', '1', '0', '6', '137', '300', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('473', 'SeedBag(Tommato)', '11', '0', '30', '10', '60', '0', '0', '0', '0', '1', '0', '6', '137', '300', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('474', 'SeedBag(Grapes)', '11', '0', '30', '11', '70', '0', '0', '0', '0', '1', '0', '6', '137', '350', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('475', 'SeedBag(BlueGrapes)', '11', '0', '30', '12', '70', '0', '0', '0', '0', '1', '0', '6', '137', '350', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('476', 'SeedBag(Mushroom)', '11', '0', '30', '13', '80', '0', '0', '0', '0', '1', '0', '6', '137', '400', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('477', 'SeedBag(Ginseng)', '11', '0', '30', '14', '90', '0', '0', '0', '0', '1', '0', '6', '137', '450', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('478', 'WaterMelon', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '138', '-120', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('479', 'Pumpkin', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '139', '-120', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('480', 'Garlic', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '140', '-180', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('481', 'Barley', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '141', '-180', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('482', 'Carrot', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '142', '-200', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('483', 'Radish', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '143', '-200', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('484', 'Corn', '7', '0', '7', '4', '8', '10', '0', '0', '0', '1', '0', '6', '144', '-240', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('485', 'ChineseBellflower', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '145', '-240', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('486', 'Melone', '7', '0', '7', '5', '7', '12', '0', '0', '0', '1', '0', '6', '146', '-300', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('487', 'Tommato', '7', '0', '7', '5', '7', '10', '0', '0', '0', '1', '0', '6', '147', '-300', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('488', 'Grapes', '7', '0', '7', '5', '8', '10', '0', '0', '0', '1', '0', '6', '148', '-360', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('489', 'BlueGrapes', '7', '0', '7', '5', '8', '10', '0', '0', '0', '1', '0', '6', '149', '-360', '100', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('490', 'Mushroom', '5', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '150', '-400', '100', '1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('491', 'SuperRedPotion', '7', '0', '4', '3', '8', '130', '0', '0', '0', '1', '0', '6', '134', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('492', 'SuperBluePotion', '7', '0', '5', '3', '8', '130', '0', '0', '0', '1', '0', '6', '135', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('493', 'SuperGreenPotion', '7', '0', '6', '4', '8', '130', '0', '0', '0', '1', '0', '6', '136', '-2000', '100', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('494', 'BarbarianHammer', '1', '9', '1', '3', '9', '2', '3', '10', '2', '4500', '0', '15', '10', '15000', '20000', '32', '15', '110', '0', '0', '0', '14', '1', '0');
INSERT INTO `item_config` VALUES ('495', 'BlackShadowSword', '1', '9', '1', '2', '12', '3', '2', '12', '3', '2800', '0', '1', '25', '10000', '15000', '33', '14', '120', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('496', 'StormBringer', '1', '9', '1', '3', '10', '0', '3', '11', '0', '3000', '0', '1', '26', '-12000', '11000', '15', '11', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('497', 'The_Devastator', '1', '9', '1', '4', '8', '1', '4', '9', '1', '3000', '0', '1', '21', '-18000', '20000', '19', '15', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('498', 'DarkExecutor', '1', '9', '1', '2', '12', '3', '2', '13', '3', '4000', '0', '1', '24', '-14000', '14000', '16', '13', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('499', 'LightingBlade', '1', '9', '1', '2', '12', '3', '2', '13', '3', '4000', '0', '1', '22', '-14000', '14000', '29', '13', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('500', 'KlonessBlade', '1', '9', '1', '2', '12', '2', '2', '13', '2', '8000', '0', '1', '23', '-12000', '12000', '17', '12', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('501', 'KlonessAxe', '1', '9', '1', '3', '9', '1', '3', '10', '1', '5000', '0', '15', '11', '-8000', '15000', '28', '14', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('502', 'KlonessEsterk', '1', '8', '1', '2', '6', '2', '2', '7', '2', '5000', '0', '1', '27', '-6000', '5000', '18', '5', '0', '0', '0', '0', '8', '1', '0');
INSERT INTO `item_config` VALUES ('503', 'CancelManual', '3', '0', '18', '76', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '1');
INSERT INTO `item_config` VALUES ('504', 'E.S.W.Manual', '3', '0', '18', '96', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '1');
INSERT INTO `item_config` VALUES ('505', 'I.M.CManual', '3', '0', '18', '83', '0', '0', '0', '0', '0', '0', '0', '6', '91', '-100', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '1');
INSERT INTO `item_config` VALUES ('506', 'NecklaceOfMerien', '1', '6', '14', '4', '50', '0', '0', '0', '0', '300', '0', '16', '54', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('507', 'NecklaceOfKloness', '1', '6', '14', '4', '0', '0', '0', '0', '0', '300', '0', '16', '52', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('508', 'NecklaceOfXelima', '1', '6', '14', '12', '100', '0', '0', '0', '0', '300', '0', '16', '53', '-20000', '1000', '-1', '0', '0', '0', '0', '0', '-1', '46', '5');
INSERT INTO `item_config` VALUES ('509', 'BerserkWand(MS.20)', '1', '8', '13', '1', '6', '0', '20', '0', '0', '5000', '0', '17', '4', '-12000', '1000', '34', '3', '100', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('510', 'BerserkWand(MS.10)', '1', '8', '13', '1', '6', '0', '10', '0', '0', '5000', '0', '17', '4', '-12000', '1000', '34', '3', '100', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('511', 'KlonessWand(MS.20)', '1', '8', '13', '1', '6', '0', '20', '0', '0', '5000', '0', '17', '5', '-14000', '1000', '39', '3', '120', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('512', 'KlonessWand(MS.10)', '1', '8', '13', '1', '6', '0', '10', '0', '0', '5000', '0', '17', '5', '-14000', '1000', '39', '3', '120', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('513', 'ResurWand(MS.20)', '1', '8', '13', '1', '6', '0', '20', '0', '0', '5000', '0', '17', '3', '-10000', '1000', '38', '3', '100', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('514', 'ResurWand(MS.10)', '1', '8', '13', '1', '6', '0', '10', '0', '0', '5000', '0', '17', '3', '-10000', '1000', '38', '3', '100', '0', '0', '0', '21', '8', '0');
INSERT INTO `item_config` VALUES ('515', 'AcientTablet', '3', '0', '31', '7', '0', '0', '0', '0', '0', '1', '0', '6', '155', '-1', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('516', 'AcientTablet(LU)', '10', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '151', '-1', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('517', 'AcientTablet(LD)', '10', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '152', '-1', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('518', 'AcientTablet(RU)', '10', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '153', '-1', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('519', 'AcientTablet(RD)', '10', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '6', '154', '-1', '50', '-1', '0', '0', '0', '0', '0', '-1', '31', '0');
INSERT INTO `item_config` VALUES ('520', 'Fire-Bow', '1', '9', '3', '2', '5', '0', '2', '5', '0', '1000', '0', '2', '5', '6000', '7000', '43', '6', '70', '0', '0', '0', '6', '3', '0');
INSERT INTO `item_config` VALUES ('521', 'Direction-Bow', '1', '9', '3', '2', '6', '0', '2', '6', '0', '1200', '0', '2', '4', '7000', '10000', '42', '8', '70', '0', '0', '0', '6', '3', '0');
INSERT INTO `item_config` VALUES ('522', 'SummonScroll(SOR)', '3', '0', '11', '5', '9', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('523', 'SummonScroll(ATK)', '3', '0', '11', '5', '10', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('524', 'SummonScroll(ELF)', '3', '0', '11', '5', '11', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('525', 'SummonScroll(DSK)', '3', '0', '11', '5', '12', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('526', 'SummonScroll(HBT)', '3', '0', '11', '5', '13', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('527', 'SummonScroll(BAR)', '3', '0', '11', '5', '14', '0', '0', '0', '0', '1', '9', '6', '9', '-300', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('528', 'MaginDiamond', '1', '11', '14', '14', '0', '0', '0', '0', '0', '300', '0', '22', '6', '-8000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '9');
INSERT INTO `item_config` VALUES ('529', 'MaginRuby', '1', '11', '14', '13', '0', '0', '0', '0', '0', '300', '0', '22', '8', '-5000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '9');
INSERT INTO `item_config` VALUES ('530', 'MagicEmerald', '1', '11', '14', '15', '0', '0', '0', '0', '0', '300', '0', '22', '7', '-5000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '9');
INSERT INTO `item_config` VALUES ('531', 'MagicSapphire', '1', '11', '0', '0', '0', '0', '0', '0', '0', '300', '0', '22', '9', '-5000', '200', '-1', '0', '0', '0', '0', '-10', '-1', '46', '9');
INSERT INTO `item_config` VALUES ('532', 'LuckyPrizeTicket', '3', '0', '23', '1', '0', '0', '0', '0', '0', '1', '9', '6', '9', '50000', '1', '-1', '0', '0', '0', '0', '0', '-1', '42', '0');
INSERT INTO `item_config` VALUES ('533', 'MagicNecklace(DF+15)', '1', '6', '14', '4', '15', '0', '0', '0', '0', '300', '0', '16', '6', '-19000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('534', 'MagicNecklace(DF+20)', '1', '6', '14', '4', '20', '0', '0', '0', '0', '300', '0', '16', '6', '-19000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('535', 'MagicNecklace(DF+25)', '1', '6', '14', '4', '25', '0', '0', '0', '0', '300', '0', '16', '6', '-19000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('536', 'MagicNecklace(DF+30)', '1', '6', '14', '4', '30', '0', '0', '0', '0', '300', '0', '16', '6', '-19000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('537', 'MagicNecklace(DM+2)', '1', '6', '14', '3', '2', '0', '0', '0', '0', '300', '0', '16', '5', '-39800', '400', '-1', '0', '65', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('538', 'MagicNecklace(DM+3)', '1', '6', '14', '3', '3', '0', '0', '0', '0', '300', '0', '16', '5', '-39800', '400', '-1', '0', '65', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('539', 'MagicNecklace(DM+4)', '1', '6', '14', '3', '4', '0', '0', '0', '0', '300', '0', '16', '5', '-39800', '400', '-1', '0', '65', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('540', 'MagicNecklace(DM+5)', '1', '6', '14', '3', '5', '0', '0', '0', '0', '300', '0', '16', '5', '-39800', '400', '-1', '0', '65', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('541', 'MagicNecklace(MS12)', '1', '6', '14', '2', '12', '0', '0', '0', '0', '300', '0', '16', '7', '-7000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('542', 'MagicNecklace(MS14)', '1', '6', '14', '2', '14', '0', '0', '0', '0', '300', '0', '16', '7', '-7000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('543', 'MagicNecklace(MS16)', '1', '6', '14', '2', '16', '0', '0', '0', '0', '300', '0', '16', '7', '-7000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('544', 'MagicNecklace(MS18)', '1', '6', '14', '2', '18', '0', '0', '0', '0', '300', '0', '16', '7', '-7000', '400', '-1', '0', '50', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('545', 'MagicNecklace(RM15)', '1', '6', '14', '1', '15', '0', '0', '0', '0', '300', '0', '16', '4', '-2250', '400', '-1', '0', '30', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('546', 'MagicNecklace(RM20)', '1', '6', '14', '1', '20', '0', '0', '0', '0', '300', '0', '16', '4', '-2250', '400', '-1', '0', '30', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('547', 'MagicNecklace(RM25)', '1', '6', '14', '1', '25', '0', '0', '0', '0', '300', '0', '16', '4', '-2250', '400', '-1', '0', '30', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('548', 'MagicNecklace(RM30)', '1', '6', '14', '1', '30', '0', '0', '0', '0', '300', '0', '16', '4', '-2250', '400', '-1', '0', '30', '0', '0', '-10', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('549', 'DiamondWare', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '22', '1', '-5000', '200', '1', '0', '0', '30', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('550', 'RubyWare', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '22', '3', '-3000', '200', '1', '0', '0', '30', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('551', 'SapphireWare', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '22', '4', '-3000', '200', '1', '0', '0', '30', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('552', 'EmeraldWare', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '22', '2', '-3000', '200', '1', '0', '0', '30', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('553', 'CrystalWare', '12', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '22', '5', '-500', '200', '1', '0', '0', '30', '0', '0', '-1', '46', '0');
INSERT INTO `item_config` VALUES ('554', 'CraftingVessel', '10', '0', '0', '1', '0', '0', '0', '0', '0', '300', '0', '22', '0', '1000', '700', '-1', '0', '0', '0', '0', '0', '-1', '21', '0');
INSERT INTO `item_config` VALUES ('555', 'AngelicPandent(STR)', '1', '11', '14', '16', '0', '0', '0', '0', '0', '300', '0', '22', '11', '-3000', '200', '-1', '0', '0', '0', '60', '-10', '-1', '46', '6');
INSERT INTO `item_config` VALUES ('556', 'AngelicPandent(DEX)', '1', '11', '14', '17', '0', '0', '0', '0', '0', '300', '0', '22', '10', '-3000', '200', '-1', '0', '0', '0', '60', '-10', '-1', '46', '6');
INSERT INTO `item_config` VALUES ('557', 'AngelicPandent(INT)', '1', '11', '14', '18', '0', '0', '0', '0', '0', '300', '0', '22', '12', '-3000', '200', '-1', '0', '0', '0', '60', '-10', '-1', '46', '6');
INSERT INTO `item_config` VALUES ('558', 'AngelicPandent(MAG)', '1', '11', '14', '19', '0', '0', '0', '0', '0', '300', '0', '22', '13', '-3000', '200', '-1', '0', '0', '0', '60', '-10', '-1', '46', '6');
