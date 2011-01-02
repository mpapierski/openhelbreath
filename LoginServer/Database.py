from sqlalchemy.orm import mapper, relationship, sessionmaker, backref
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.exc import *
from sqlalchemy.sql import exists
from sqlalchemy.sql.expression import *
from sqlalchemy import (MetaData, Table, Column, DateTime, SmallInteger, Integer, Boolean,
					   String, ForeignKey, create_engine,
					   and_, or_)

import time, random, os, re, datetime
from Helpers import PutLogFileList, PutLogList
from GlobalDef import AccountInfo, DEF, Logfile
from sqlalchemy.orm.exc import NoResultFound

Base = declarative_base()

class Account(Base):
	__tablename__ = "account"
	AccountID = Column(Integer, primary_key = True)
	Name = Column(String(10), nullable = False, unique = True)
	Password = Column(String(10), nullable = False)
	Mail = Column(String(50), nullable = False)
	Quiz = Column(String(45))
	Answer = Column(String(20))
	SignupDate = Column(DateTime(), nullable = False)
	BlockDate = Column(DateTime())
	IpAddress = Column(String(15), nullable = False)
	
	def __init__(self, name, password, mail, quiz, answer, address):
		self.Name = name
		self.Password = password
		self.Mail = mail
		self.Quiz = quiz
		self.Answer = answer
		self.SignupDate = datetime.datetime.now()
		self.IpAddress = address
		
	def __repr__(self):
		return "<User('%s', '%s', '%s')>" % (str(self.AccountID), self.Name, self.Password)
	@staticmethod
	def ByName(session, name):
		try:
			return session.query(Account).\
				filter(Account.Name == name).\
				one()
		except NoResultFound:
			return False
	@staticmethod
	def Match(session, name, pwd):
		try:
			return session.query(Account).\
				filter(Account.Name == name).\
				filter(Account.Password == pwd).\
				one()
		except NoResultFound:
			return False
		
	def Has(self, player_name):
		return filter(lambda ch: ch.CharName == player_name, self.CharList)
	def Find(self, player_name):
		return (lambda x: x[0] if x else False)(self.Has(player_name))
	
class Character(Base):
	__tablename__ = "character"
	AccountID = Column(Integer, ForeignKey("account.AccountID"))
	CharacterID = Column(Integer, primary_key = True)
	CharName = Column(String(10), nullable = False, unique = True)
	ID1 = Column(Integer, default = 0)
	ID2 = Column(Integer, default = 0)
	ID3 = Column(Integer, default = 0)
	Level = Column(Integer, default = 1)
	Strength = Column(Integer, default = 10)
	Dexterity = Column(Integer, default = 10)
	Intelligence = Column(Integer, default = 10)
	Magic = Column(Integer, default = 10)
	Vitality = Column(Integer, default = 10)
	Charisma = Column(Integer, default = 10)
	Luck = Column(Integer, default = 0)
	Experience = Column(Integer, default = 0)
	Gender = Column(SmallInteger, default = 0)
	Skin = Column(SmallInteger, default = 0)
	HairStyle = Column(SmallInteger, default = 0)
	HairColor = Column(SmallInteger, default = 0)
	Underwear = Column(SmallInteger, default = 0)
	ApprColor = Column(Integer, default = 0)
	Appr1 = Column(Integer, default = 0)
	Appr2 = Column(Integer, default = 0)
	Appr3 = Column(Integer, default = 0)
	Appr4 = Column(Integer, default = 0)
	Nation = Column(String(10), default = "NONE")
	MapLoc = Column(String(10), default = "default")
	LocX = Column(SmallInteger, default = 0)
	LocY = Column(SmallInteger, default = 0)
	Profile = Column(String(255))
	AdminLevel = Column(SmallInteger, default = 0)
	Contribution = Column(Integer, default = 0)
	LeftSpecialTime = Column(Integer, default = 0)
	LockedMapName = Column(String(10), default = "")
	LockedMapTime = Column(Integer, default = 0)
	CreateDate = Column(DateTime)
	LogoutDate = Column(DateTime)
	BlockDate = Column(DateTime)
	GuildName = Column(String(20))
	GuildID = Column(Integer, default = -1)
	GuildRank = Column(Integer, default = -1)
	FightNum = Column(SmallInteger, default = 0)
	FightDate = Column(SmallInteger, default = 0)
	FightTicket = Column(SmallInteger, default = 0)
	QuestNum = Column(SmallInteger, default = 0)
	QuestID = Column(SmallInteger, default = 0)
	QuestCount = Column(SmallInteger, default = 0)
	QuestRewType = Column(SmallInteger, default = 0)
	QuestRewAmmount = Column(SmallInteger, default = 0)
	QuestCompleted = Column(SmallInteger, default = 0)
	EventID = Column(Integer, default = 0)
	WarCon = Column(Integer, default = 0)
	CruJob = Column(Integer, default = 0)
	CruID = Column(Integer, default = 0)
	CruConstructPoint = Column(SmallInteger, default = 0)
	Popularity = Column(Integer, default = 0)
	HP = Column(Integer, default = 0)
	MP = Column(Integer, default = 0)
	SP = Column(Integer, default = 0)
	EK = Column(Integer, default = 0)
	PK = Column(Integer, default = 0)
	RewardGold = Column(Integer, default = 0)
	DownSkillID = Column(Integer, default = -1)
	Hunger = Column(SmallInteger, default = 100)
	LeftSAC = Column(Integer, default = 0)
	LeftShutupTime = Column(Integer, default = 0)
	LeftPopTime = Column(Integer, default = 0)
	LeftForceRecallTime = Column(Integer, default = 0)
	LeftFirmStaminarTime = Column(Integer, default = 0)
	LeftDeadPenaltyTime = Column(Integer, default = 0)
	MagicMastery = Column(String(100), default = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")
	PartyID = Column(Integer, default = 0)
	GizonItemUpgradeLeft = Column(Integer, default = 0)
	Account = relationship(Account, backref = backref("CharList", order_by = Level))
	
	@staticmethod
	def Exists(session, Name):
		try:
			return session.query(Character).\
				filter(Character.CharName == Name).\
				one()
		except NoResultFound:
			return False
		
	def __init__(self, CharName, Gender, SkinColor,
				 HairStyle, HairColor, UnderColor, Str, Dex, Int, Mag, Vit, Chr):
		# TODO : fix ApprX values!
		self.CharName = CharName
		self.Gender = int(Gender)
		self.Skin = int(SkinColor)
		self.HairStyle = int(HairStyle)
		self.HairColor = int(HairColor)
		self.Underwear = int(UnderColor)
		self.Strength = Str
		self.Dexterity = Dex
		self.Intelligence = Int
		self.Magic = Mag
		self.Vitality = Vit
		self.Charisma = Chr
		self.Appr1 = (HairStyle << 8) | (HairColor << 4) | (UnderColor)
		self.HP = (Vit * 3) + (Str / 2) + 2
		self.MP = (Mag * 2) + (Int / 2) + 2
		self.SP = (Str * 2) + 2
		self.CreateDate = datetime.datetime.now()
		self.AddItem(56, "Gold", 0, 0, 0, 0, 65, 30)
		self.CreateDate = datetime.datetime.now()
		for s in range(24):
			if s in [4, 5, 7]:
				SkillMastery = 20
			elif s == 3:
				SkillMastery = 3
			else:
				SkillMastery = 0
			self.Skills.append(Skill(SkillID = s,
									 SkillMastery = SkillMastery))
		
	def __repr__(self):
		return "<Character(CharName = '%s', Level = '%d')>" % (self.CharName, self.Level)
	
	def AddItem(self, _ID, _Name, _LifeSpan, _Color, _Attr, _Equip, _X, _Y):
		self.Items.append(Item(Name = _Name,
								ItemID = _ID,
								Color = _Color,
								LifeSpan = _LifeSpan,
								Attribute = _Attr,
								Equip = _Equip,
								X = _X,
								Y = _Y))
	def Erase(self, sess):
		while len(self.Skills):
			sess.delete(self.Skills.pop(0))
		while len(self.Items):
			sess.delete(self.Items.pop(0))
		while len(self.BankItems):
			sess.delete(self.BankItems.pop(0))
		sess.delete(self)
		
class BankItem(Base):
	__tablename__ = "bankitem"
	ID = Column(Integer, primary_key = True)
	CharID = Column(Integer, ForeignKey("character.CharacterID"))
	Name = Column(String(20), nullable = False)
	ItemID = Column(Integer, nullable = False)
	Count = Column(Integer, default = 1)
	Type = Column(Integer, default = 0)
	ID1 = Column(Integer, default = 0)
	ID2 = Column(Integer, default = 0)
	ID3 = Column(Integer, default = 0)
	Color = Column(Integer, default = 0)
	Effect1 = Column(Integer, default = 0)
	Effect2 = Column(Integer, default = 0)
	Effect3 = Column(Integer, default = 0)
	LifeSpan = Column(Integer, default = 0)
	Attribute = Column(Integer, default = 0)
	Char = relationship(Character, backref = backref("BankItems"))
#	def __init__(self, Name, ID, Count, Type, ID1, ID2, ID3, Color, Effect1, Effect2,Effect3, LifeSpan
	
class Item(Base):
	__tablename__ = "item"
	ID = Column(Integer, primary_key = True)
	CharID = Column(Integer, ForeignKey("character.CharacterID"))
	Name = Column(String(20), nullable = False)
	ItemID = Column(Integer, nullable = False)
	Count = Column(Integer, default = 1)
	Type = Column(Integer, default = 0)
	ID1 = Column(Integer, default = 0)
	ID2 = Column(Integer, default = 0)
	ID3 = Column(Integer, default = 0)
	Color = Column(Integer, default = 0)
	Effect1 = Column(Integer, default = 0)
	Effect2 = Column(Integer, default = 0)
	Effect3 = Column(Integer, default = 0)
	LifeSpan = Column(Integer, default = 0)
	Attribute = Column(Integer, default = 0)
	Equip = Column(Boolean, default = False)
	X = Column(Integer, default = 0)
	Y = Column(Integer, default = 0)
	Char = relationship(Character, backref = backref("Items"))
	
class Skill(Base):
	__tablename__ = "skill"
	ID = Column(Integer, primary_key = True)
	CharacterID = Column(Integer, ForeignKey("character.CharacterID"))
	SkillID = Column(Integer, default = 0)
	SkillMastery = Column(Integer, default = 0)
	SkillSSN = Column(Integer, default = 0)
	SkillChar = relationship(Character, backref = backref("Skills", order_by = ID))

"""class Guild(Base):
	ID = Column(Integer, primary_key = True)
	Name = Column(String(20))
	Char = 	"""

class DatabaseDriver:
	def Initialize(self, URL):
		self.engine = None
		self.Session = None
		try:
			self.engine = create_engine(URL, echo = False)
			Base.metadata.create_all(self.engine)
		except ArgumentError:
			return False
		self.Session = sessionmaker(bind = self.engine)
		return True
	
	def session(self):
		return self.Session()