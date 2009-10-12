-- ----------------------------
-- OpenHelbreath MySQL Dump
-- ----------------------------

DROP DATABASE `playerdb`;
CREATE DATABASE `playerdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `playerdb`;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for account_database
-- ----------------------------
DROP TABLE IF EXISTS `account_database`;
CREATE TABLE `account_database` (
  `name` varchar(10) character set utf8 collate utf8_bin NOT NULL default '',
  `password` varchar(40) NOT NULL default '',
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
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=utf8 PACK_KEYS=0;

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
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for guild
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild` (
  `GuildName` varchar(20) NOT NULL default '',
  `GuildID` int(11) unsigned NOT NULL auto_increment,
  `MasterName` varchar(10) NOT NULL default '',
  `Nation` varchar(10) NOT NULL default '',
  `NumberOfMembers` smallint(6) unsigned NOT NULL default '0',
  `CreateDate` datetime NOT NULL default '0000-00-00 00:00:00',
  `BaseScore` bigint(20) unsigned NOT NULL default '0',
  `TotalScore` bigint(20) unsigned NOT NULL default '0',
  UNIQUE KEY `GuildID` (`GuildID`),
  KEY `GuildName` (`GuildName`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0;

-- ----------------------------
-- Table structure for guild_member
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member` (
  `GuildName` varchar(20) NOT NULL default '',
  `MemberName` varchar(10) NOT NULL default '',
  `JoinDate` datetime NOT NULL default '0000-00-00 00:00:00',
  KEY `GuildName` (`GuildName`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for ipblocked
-- ----------------------------
DROP TABLE IF EXISTS `ipblocked`;
CREATE TABLE `ipblocked` (
  `ipaddress` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`ipaddress`),
  UNIQUE KEY `ipaddress` (`ipaddress`),
  KEY `ipaddress_2` (`ipaddress`)
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
-- Table structure for setup
-- ----------------------------
DROP TABLE IF EXISTS `setup`;
CREATE TABLE `setup` (
  `name` varchar(20) NOT NULL default '',
  `primary-drop-rate` int(10) unsigned NOT NULL default '6500',
  `secondary-drop-rate` int(10) unsigned NOT NULL default '9000',
  `enemy-kill-mode` varchar(10) NOT NULL default '',
  `enemy-kill-adjust` smallint(5) unsigned NOT NULL default '0',
  `admin-security` char(3) NOT NULL default '',
  `monday-raid-time` int(10) unsigned NOT NULL default '0',
  `tuesday-raid-time` int(10) unsigned NOT NULL default '0',
  `wednesday-raid-time` int(10) unsigned NOT NULL default '0',
  `thursday-raid-time` int(10) unsigned NOT NULL default '0',
  `friday-raid-time` int(10) unsigned NOT NULL default '0',
  `saturday-raid-time` int(10) unsigned NOT NULL default '0',
  `sunday-raid-time` int(10) unsigned NOT NULL default '0',
  `log-chat-settings` varchar(10) NOT NULL default '',
  `summonguild-cost` bigint(20) unsigned NOT NULL default '0',
  `slate-success-rate` tinyint(3) unsigned NOT NULL default '0',
  `character-stat-limit` int(10) unsigned NOT NULL default '0',
  `character-skill-limit` mediumint(8) unsigned NOT NULL default '0',
  `rep-drop-modifier` smallint(5) unsigned NOT NULL default '0',
  `admin-security-code` varchar(20) NOT NULL default '',
  `max-player-level` mediumint(8) unsigned NOT NULL default '0',
  `createguild-cost` bigint(20) unsigned NOT NULL default '0',
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `name_2` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

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
