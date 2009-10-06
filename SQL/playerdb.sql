-- phpMyAdmin SQL Dump
-- version 3.1.3.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 06, 2009 at 09:16 AM
-- Server version: 5.1.33
-- PHP Version: 5.2.9-2

SET FOREIGN_KEY_CHECKS=0;

--
-- Database: `playerdb`
--
DROP DATABASE `playerdb`;
CREATE DATABASE `playerdb` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `playerdb`;

-- --------------------------------------------------------

--
-- Table structure for table `account_database`
--

DROP TABLE IF EXISTS `account_database`;
CREATE TABLE IF NOT EXISTS `account_database` (
  `name` varchar(10) NOT NULL DEFAULT '',
  `password` varchar(10) NOT NULL DEFAULT '',
  `AccountID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `LoginIpAddress` varchar(20) NOT NULL DEFAULT '',
  `IsGMAccount` smallint(1) NOT NULL DEFAULT '0',
  `CreateDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `LoginDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `LogoutDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `BlockDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `RealName` varchar(30) NOT NULL DEFAULT '',
  `Gender` char(1) NOT NULL DEFAULT '',
  `Email` varchar(50) NOT NULL DEFAULT '',
  `CharRecord` varchar(100) NOT NULL DEFAULT '',
  `Quiz` varchar(45) NOT NULL DEFAULT '',
  `Answer` varchar(20) NOT NULL DEFAULT '',
  `ValidDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`name`),
  UNIQUE KEY `AccountID` (`AccountID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `bank_item`
--

DROP TABLE IF EXISTS `bank_item`;
CREATE TABLE IF NOT EXISTS `bank_item` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemName` varchar(20) NOT NULL DEFAULT '',
  `ItemID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ID1` smallint(6) NOT NULL DEFAULT '0',
  `ID2` smallint(6) unsigned NOT NULL DEFAULT '0',
  `ID3` smallint(6) unsigned NOT NULL DEFAULT '0',
  `Color` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect1` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect2` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect3` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `LifeSpan` int(11) unsigned NOT NULL DEFAULT '0',
  `Attribute` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `char_database`
--

DROP TABLE IF EXISTS `char_database`;
CREATE TABLE IF NOT EXISTS `char_database` (
  `CharID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `account_name` varchar(10) NOT NULL DEFAULT '',
  `char_name` varchar(10) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `ID1` mediumint(9) NOT NULL DEFAULT '0',
  `ID2` mediumint(9) NOT NULL DEFAULT '0',
  `ID3` mediumint(9) NOT NULL DEFAULT '0',
  `Level` smallint(4) unsigned NOT NULL DEFAULT '1',
  `Strength` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Vitality` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Dexterity` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Intelligence` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Magic` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Agility` tinyint(4) unsigned NOT NULL DEFAULT '10',
  `Luck` smallint(5) unsigned NOT NULL DEFAULT '10',
  `Exp` int(11) unsigned NOT NULL DEFAULT '0',
  `Gender` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `Skin` smallint(6) unsigned NOT NULL DEFAULT '0',
  `HairStyle` smallint(6) unsigned NOT NULL DEFAULT '0',
  `HairColor` smallint(6) unsigned NOT NULL DEFAULT '0',
  `Underwear` smallint(6) unsigned NOT NULL DEFAULT '0',
  `ApprColor` int(11) NOT NULL DEFAULT '0',
  `Appr1` mediumint(6) NOT NULL DEFAULT '0',
  `Appr2` mediumint(6) NOT NULL DEFAULT '0',
  `Appr3` mediumint(6) NOT NULL DEFAULT '0',
  `Appr4` mediumint(6) NOT NULL DEFAULT '0',
  `Nation` varchar(10) NOT NULL DEFAULT 'NONE',
  `MapLoc` varchar(10) NOT NULL DEFAULT 'default',
  `LocX` mediumint(4) NOT NULL DEFAULT '-1',
  `LocY` mediumint(4) NOT NULL DEFAULT '-1',
  `Profile` varchar(255) NOT NULL DEFAULT '__________',
  `AdminLevel` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Contribution` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftSpecTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LockMapName` varchar(10) NOT NULL DEFAULT '',
  `LockMapTime` int(11) unsigned NOT NULL DEFAULT '0',
  `CreateDate` datetime NOT NULL,
  `LastSaveDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `BlockDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `GuildName` varchar(20) NOT NULL DEFAULT 'NONE',
  `GuildID` int(11) NOT NULL DEFAULT '-1',
  `GuildRank` tinyint(4) NOT NULL DEFAULT '-1',
  `FightNum` tinyint(4) NOT NULL DEFAULT '0',
  `FightDate` int(10) unsigned NOT NULL DEFAULT '0',
  `FightTicket` tinyint(4) NOT NULL DEFAULT '0',
  `QuestNum` smallint(5) unsigned NOT NULL DEFAULT '0',
  `QuestID` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestCount` smallint(5) unsigned NOT NULL DEFAULT '0',
  `QuestRewType` smallint(6) NOT NULL DEFAULT '0',
  `QuestRewAmmount` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestCompleted` tinyint(1) NOT NULL DEFAULT '0',
  `EventID` int(11) unsigned NOT NULL DEFAULT '0',
  `WarCon` int(11) unsigned NOT NULL DEFAULT '0',
  `CruJob` smallint(2) unsigned NOT NULL DEFAULT '0',
  `CruID` int(11) unsigned NOT NULL DEFAULT '0',
  `CruConstructPoint` int(11) unsigned NOT NULL DEFAULT '0',
  `Popularity` int(11) NOT NULL DEFAULT '0',
  `HP` int(11) unsigned NOT NULL DEFAULT '0',
  `MP` int(11) unsigned NOT NULL DEFAULT '0',
  `SP` int(11) unsigned NOT NULL DEFAULT '0',
  `EK` int(11) unsigned NOT NULL DEFAULT '0',
  `PK` int(11) unsigned NOT NULL DEFAULT '0',
  `RewardGold` int(11) unsigned NOT NULL DEFAULT '0',
  `DownSkillID` tinyint(4) NOT NULL DEFAULT '-1',
  `Hunger` tinyint(4) unsigned NOT NULL DEFAULT '100',
  `LeftSAC` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `LeftShutupTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftPopTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftForceRecallTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftFirmStaminarTime` int(11) unsigned NOT NULL DEFAULT '0',
  `LeftDeadPenaltyTime` int(11) unsigned NOT NULL DEFAULT '0',
  `MagicMastery` varchar(100) NOT NULL DEFAULT '0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000',
  `PartyID` int(11) unsigned NOT NULL DEFAULT '0',
  `GizonItemUpgradeLeft` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`char_name`),
  UNIQUE KEY `CharID` (`CharID`),
  KEY `account_name` (`account_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `guild`
--

DROP TABLE IF EXISTS `guild`;
CREATE TABLE IF NOT EXISTS `guild` (
  `GuildName` varchar(20) NOT NULL DEFAULT '',
  `GuildID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `MasterName` varchar(10) NOT NULL DEFAULT '',
  `Nation` varchar(10) NOT NULL DEFAULT '',
  `NumberOfMembers` smallint(6) unsigned NOT NULL DEFAULT '0',
  `CreateDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `BaseScore` bigint(20) unsigned NOT NULL DEFAULT '0',
  `TotalScore` bigint(20) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `GuildID` (`GuildID`),
  KEY `GuildName` (`GuildName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `guild_member`
--

DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE IF NOT EXISTS `guild_member` (
  `GuildName` varchar(20) NOT NULL DEFAULT '',
  `MemberName` varchar(10) NOT NULL DEFAULT '',
  `JoinDate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `GuildName` (`GuildName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `ipblocked`
--

DROP TABLE IF EXISTS `ipblocked`;
CREATE TABLE IF NOT EXISTS `ipblocked` (
  `ipaddress` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`ipaddress`),
  UNIQUE KEY `ipaddress` (`ipaddress`),
  KEY `ipaddress_2` (`ipaddress`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `item`
--

DROP TABLE IF EXISTS `item`;
CREATE TABLE IF NOT EXISTS `item` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemName` varchar(20) NOT NULL DEFAULT '',
  `ItemID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Count` int(11) unsigned NOT NULL DEFAULT '1',
  `ItemType` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `ID1` smallint(6) NOT NULL DEFAULT '0',
  `ID2` smallint(6) NOT NULL DEFAULT '0',
  `ID3` smallint(6) NOT NULL DEFAULT '0',
  `Color` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect1` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect2` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `Effect3` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `LifeSpan` int(11) unsigned NOT NULL DEFAULT '0',
  `Attribute` int(11) unsigned NOT NULL DEFAULT '0',
  `ItemEquip` tinyint(1) NOT NULL DEFAULT '0',
  `ItemPosX` int(11) NOT NULL DEFAULT '40',
  `ItemPosY` int(11) NOT NULL DEFAULT '30',
  PRIMARY KEY (`ItemID`),
  UNIQUE KEY `ItemID` (`ItemID`),
  KEY `Index` (`CharID`),
  KEY `ItemName` (`ItemName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `setup`
--

DROP TABLE IF EXISTS `setup`;
CREATE TABLE IF NOT EXISTS `setup` (
  `name` varchar(20) NOT NULL DEFAULT '',
  `primary-drop-rate` int(10) unsigned NOT NULL DEFAULT '6500',
  `secondary-drop-rate` int(10) unsigned NOT NULL DEFAULT '9000',
  `enemy-kill-mode` varchar(10) NOT NULL DEFAULT '',
  `enemy-kill-adjust` smallint(5) unsigned NOT NULL DEFAULT '0',
  `admin-security` char(3) NOT NULL DEFAULT '',
  `monday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `tuesday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `wednesday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `thursday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `friday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `saturday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `sunday-raid-time` int(10) unsigned NOT NULL DEFAULT '0',
  `log-chat-settings` varchar(10) NOT NULL DEFAULT '',
  `summonguild-cost` bigint(20) unsigned NOT NULL DEFAULT '0',
  `slate-success-rate` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `character-stat-limit` int(10) unsigned NOT NULL DEFAULT '0',
  `character-skill-limit` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `rep-drop-modifier` smallint(5) unsigned NOT NULL DEFAULT '0',
  `admin-security-code` varchar(20) NOT NULL DEFAULT '',
  `max-player-level` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `createguild-cost` bigint(20) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `name_2` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `skill`
--

DROP TABLE IF EXISTS `skill`;
CREATE TABLE IF NOT EXISTS `skill` (
  `CharID` int(11) unsigned NOT NULL DEFAULT '0',
  `SkillID` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `SkillMastery` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `SkillSSN` int(11) unsigned NOT NULL DEFAULT '0',
  KEY `Index` (`CharID`),
  KEY `SkillID` (`SkillID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
