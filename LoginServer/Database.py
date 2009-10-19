import MySQLdb, _mysql_exceptions, time, random, os, re
from Helpers import PutLogFileList
from GlobalDef import Account, DEF, Logfile
from threading import Semaphore, BoundedSemaphore

MySQL_Auth = {'host' : 'localhost', 'port': 3307, 'user': 'root', 'passwd': '', 'db': 'playerdb'}

class DatabaseDriver(object):
	def __init__(self):
		global MySQL_Auth
		MySQL_Auth = self.ReadDatabaseConfigFile('LServer.cfg')
		Default = {'host' : 'localhost', 'port': 3306, 'user': 'root', 'passwd': '', 'db': 'playerdb'}
		for k in Default.keys():
			if k not in MySQL_Auth:
				MySQL_Auth[k] = Default[k]
		self.Ready = False
		self.Access = Semaphore() #change if server is laggy
		
	def Initialize(self):
		if self.Ready:
			print "(!) MySQL Driver already initialized!"
			return False
		global MySQL_Auth
		print "(*) Connecting to MySQL database..."
		try:
			self.db = MySQLdb.connect(**MySQL_Auth)
		except _mysql_exceptions.OperationalError as (E_No, E_Str):
			print "(!!!) MySQL ERROR #%d - %s!" % (E_No, E_Str)
			return False
		except:
			print "(!!!) Unhandled MySQL error (!!!)"
			return False
		
		self.Ready = True
		if not self.CheckDatabase():
			print "(!) Database tables are corrupted!"
			return False

		print "(*) Connection to MySQL database was successfully established!"

		return True
		
	def __querybuilder(self, Query, *Args):
		"""
			Mapping every string Arg to escape_string. Private method.
			Returns: valid query string
		"""
		if not self.Ready:
			return Query
		Values = tuple(map(lambda x: self.db.escape_string(x) if type(x) == str else x, Args))
		return Query % Values if len(Args)>0 else Query
	
	def ExecuteSQL(self, Query, *Args):
		if not self.Ready:
			return False
		self.Access.acquire()
		QueryConsult = self.__querybuilder(Query, *Args)
		try:
			self.db.query(QueryConsult)
		except:
			PutLogFileList(QueryConsult, Logfile.MYSQL)
			self.Access.release()
			return False

		self.Access.release()
		return True
		
	def fetch_array(self, result):
		"""
			Fetching dictionary {field_name: row} instead of tuple.
			This must be optimized before use.
		"""
		row = result.fetch_row()
		if row == ():
			return {}
		descr = result.describe()
		d={}
		
		for i in range(len(descr)):
			d[descr[i][0]]=row[0][i]
			
		return d
		
	def CheckDatabase(self):
		if not self.Ready:
			raise Exception('Database driver not ready!')
			
		if not self.ExecuteSQL("SHOW TABLES"):
			return False
			
		r = self.db.store_result()
		Tables = ('account_database', 'bank_item', 'char_database', 'guild', 'guild_member', 'ipblocked', 'item', 'setup', 'skill')
		PlayerDB = []
		while True:
			row = r.fetch_row()
			if row == ():
				break
			table_name = row[0][0]
			PlayerDB += [table_name]

		if len(PlayerDB) != len(Tables):
			return False
			
		ile = 0
		for i in PlayerDB: #count how much elements from PlayerDB is in Tables
			ok = False
			for j in Tables:
				if i == j:
					ile += 1
		return ile == len(Tables)
		
	def ChangePassword(self, LoginName, Password, NewPassword):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		try:
			QueryConsult = "UPDATE `account_database` SET `password` = '%s' WHERE BINARY `name` = '%s' AND BINARY `password` = '%s' LIMIT 1"
			if not self.ExecuteSQL(QueryConsult, NewPassword, LoginName, Password):
				return False
		except:
			return False
			
		return self.db.affected_rows() > 0
		
	def CheckAccountLogin(self, LoginName, Password):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		QueryConsult = "SELECT `name`, `password`, `BlockDate` FROM `account_database` WHERE BINARY `name` = '%s' LIMIT 1"
		if not self.ExecuteSQL(QueryConsult, LoginName):
			return (Account.BLOCKED, 0, 0, 0) #SQL Failed -> Account blocked, please try again later
		try:
			r = self.db.store_result()
			if r.num_rows() == 0:
				return (Account.NOTEXISTS,)
			
			row = r.fetch_row()[0]
			if Password != row[1]:
				return (Account.WRONGPASS, Password, row[1])
			
			if row[2] != None: #BLOCKED?!
				BlockDate = str(row[2])
				try:
					tm = time.strptime(BlockDate, "%Y-%m-%d %H:%M:%S")
				except:
					print "(WTF) Account invalid BlockDate value %s (Acc: %s)" % (row[2], LoginName)
					return (Account.BLOCKED, 0, 0, 0)
				if tm > time.localtime():
					return (Account.BLOCKED, tm.tm_year, tm.tm_mon, tm.tm_mday)
				else:
					return (Account.OK, )
		except:
			return (Account.BLOCKED, 0, 0, 0)
			
		return (Account.OK,)
		
	def CharacterExists(self, char_name):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		QueryConsult = "SELECT `CharID` FROM `char_database` WHERE BINARY `char_name` = '%s'"
		if not self.ExecuteSQL(QueryConsult, char_name):
			return False
		r = self.db.store_result()
		return r.num_rows() > 0
		
	def GetAccountCharacterList(self, account_name, account_password):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		QueryConsult = "SELECT chr.* FROM `account_database` as acc, `char_database` as chr WHERE BINARY chr.account_name = acc.name AND BINARY acc.name = '%s' AND BINARY acc.password = '%s' ORDER BY chr.CreateDate ASC"
		if not self.ExecuteSQL(QueryConsult, account_name, account_password):
			return []
		try:
			r = self.db.store_result()
			if r.num_rows() == 0:
				return []
			rows = []	
			while True:
				#row = r.fetch_row()
				row = self.fetch_array(r)
				if row == {}:
					break
				rows += [row]
		except:
			return []
			
		return rows
		
	def CreateNewCharacter(self, Packet):
		if not self.Ready:
			raise Exception('Database driver not ready!')

		QueryConsult = "INSERT INTO `char_database` (`account_name`, `char_name`, `Strength` , `Vitality` , `Dexterity` , `Intelligence` , `Magic` , `Agility` , `Appr1`, `Gender` , `Skin` , `HairStyle` , `HairColor` , `Underwear` , `HP` , `MP` , `SP`, `CreateDate`)" + \
							"VALUES ( '%s', '%s' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', NOW())"
		if not self.ExecuteSQL(QueryConsult,
							Packet.AccountName,
							Packet.PlayerName,
							Packet.Str,
							Packet.Vit,
							Packet.Dex,
							Packet.Int,
							Packet.Mag,
							Packet.Agi,
							((Packet.HairStyle << 8) | (Packet.HairCol << 4) | (Packet.UnderCol)), #Appr1
							Packet.Gender,
							Packet.SkinCol,
							Packet.HairStyle,
							Packet.HairCol,
							Packet.UnderCol,
							(Packet.Vit * 3) + (Packet.Str / 2) + 2,
							(Packet.Mag * 2) + (Packet.Int / 2) + 2,
							(Packet.Str * 2) + 2):
			return False #False means no query was executed so no worry about empty skills or no items
		if self.db.affected_rows() > 0:
			try:
				Char_ID = self.db.insert_id()
				self.CreateNewItem(Char_ID, 10, 30, 300, 1, "Dagger")
				self.CreateNewItem(Char_ID, 20, 30, 25, 1, "Map")
				self.CreateNewItem(Char_ID, 30, 30, 1, 1, "RedPotion")
				self.CreateNewItem(Char_ID, 40, 30, 1, 1, "RedPotion")
				self.CreateNewItem(Char_ID, 50, 30, 1, 1, "BluePotion")
				self.CreateNewItem(Char_ID, 60, 30, 1, 1, "GreenPotion")
				self.CreateNewItem(Char_ID, 70, 30, 1, 1, "RecallScroll")
				if Packet.Gender == 1:# Male
					if random.randint(1, 16) == 16:
						self.CreateNewItem(Char_ID, 30, 40, 1, 1, "Shoes")
					else:
						self.CreateNewItem(Char_ID, 30, 40, 1, 1, "Shirt(M)")
					self.CreateNewItem(Char_ID, 50, 40, 1, 1, "KneeTrousers(M)")
				if Packet.Gender == 2:# Female
					self.CreateNewItem(Char_ID, 30, 40, 1, 1, "Shirt(W)")
					self.CreateNewItem(Char_ID, 50, 40, 1, 1, "KneeTrousers(W)")
				print "Itemki"
				for s in range(DEF.MAXSKILLS):
					if s in [4, 5, 7]:
						SkillMastery = 20
					elif s == 3:
						SkillMastery = 3
					else:
						SkillMastery = 0
					QueryConsult = "INSERT INTO `skill` ( `CharID` , `SkillID`, `SkillMastery` , `SkillSSN`)" + \
													"VALUES ('%d', '%d', '%d', '%d')"
					if not self.ExecuteSQL(QueryConsult, Char_ID, s, SkillMastery, 0):
						raise Exception('This is only for sure. Propably will not ever appear.')
			except:
				print "(MySQL) Exception in CreateCharacter! Deleting char %s..." % Packet.PlayerName
				self.DeleteCharacter(Packet.AccountName, Packet.AccountPassword, Packet.PlayerName)
				return False
		return True
		
	def DeleteCharacter(self, account_name, account_password, char_name):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		try:
			QueryConsult = "SELECT chr.CharID FROM `account_database` as acc, `char_database` as chr WHERE BINARY chr.account_name = acc.name AND BINARY acc.name = '%s' AND BINARY acc.password = '%s' AND BINARY chr.char_name = '%s'"
			if not self.ExecuteSQL(QueryConsult, account_name, account_password, char_name):
				return False

			r = self.db.store_result()
			if r.num_rows() == 0:
				return False
			
			CharID = int(r.fetch_row()[0][0])
			
			QueryConsult = "DELETE FROM `char_database` WHERE BINARY account_name='%s' AND BINARY char_name='%s'"
			if not self.ExecuteSQL(QueryConsult, account_name, char_name):
				return False
			
			if self.db.affected_rows() == 0:
				#For sure, propably will not happen
				return False

			for table_name in ['skill','item','bank_item']:
				QueryConsult = "DELETE FROM `%s` WHERE CharID = '%d'"
				if not self.ExecuteSQL(QueryConsult, table_name, CharID):
					#For sure, propably will not happen
					return False
		except:
			return False

		return True
	def CreateNewAccount(self, account_name, account_password, mail, quiz, answer, address):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		QueryConsult = "SELECT AccountID FROM `account_database` WHERE BINARY `name` = '%s'"
		if not self.ExecuteSQL(QueryConsult, account_name):
			return Account.FAIL
		r = self.db.store_result()
		if r.num_rows() > 0:
			return Account.EXISTS
		QueryConsult = "INSERT INTO `account_database` (`name`, `password`, `Email`, `Quiz`, `Answer`, `SignUpIpAddress`, `SignUpDate`, `SignUpFromClient`)" + \
							"VALUES ('%s', '%s', '%s', '%s', '%s', '%s', NOW(), 1)"
		if not self.ExecuteSQL(QueryConsult, account_name, account_password, mail, quiz, answer, address):
			return Account.FAIL
			
		return Account.OK
		
	def GetCharacter(self, account_name, account_password, char_name):
		QueryConsult = "SELECT chr.* FROM `account_database` as acc, `char_database` as chr WHERE BINARY chr.account_name = acc.name AND BINARY acc.name = '%s' AND BINARY acc.password = '%s' AND BINARY chr.char_name = '%s'"
		if not self.ExecuteSQL(QueryConsult, account_name, account_password, char_name):
			return False
		r = self.db.store_result()
		if r.num_rows() == 0:
			return False
			
		Character = {}
		Character['Content'] = self.fetch_array(r)
	
		QueryConsult = "SELECT `SkillID`, `SkillMastery`, `SkillSSN` FROM `skill` WHERE `CharID` = '%d' LIMIT %d"
		if not self.ExecuteSQL(QueryConsult, Character['Content']['CharID'], DEF.MAXSKILLS):
			return False
		r = self.db.store_result()
		if r.num_rows() == 0:
			return False
		Character['Skill'] = []
		while True:
			row = r.fetch_row()
			if row == ():
				break
			Character['Skill'] += [dict(zip(['SkillID', 'SkillMastery', 'SkillSSN'], row[0]))]

		QueryConsult = "SELECT `ItemName`, `Count`, `ItemType`, `ID1`, `ID2`, `ID3`, `Color`, `Effect1`, `Effect2`, `Effect3`, `LifeSpan`, `Attribute`, `ItemEquip`, `ItemPosX`, `ItemPosY`, `ItemID` FROM `item` WHERE `CharID` = '%d' LIMIT %d"
		if not self.ExecuteSQL(QueryConsult, Character['Content']['CharID'], DEF.MAXITEMS):
			return False
		r = self.db.store_result()
		Character['Item'] = []
		while True:
			row = r.fetch_row()
			if row == ():
				break
			Character['Item'] += [dict(zip(['ItemName', 'Count', 'ItemType', 'ID1', 'ID2', 'ID3', 'Color', 'Effect1', 'Effect2', 'Effect3', 'LifeSpan', 'Attribute', 'ItemEquip', 'ItemPosX', 'ItemPosY', 'ItemID'], row[0]))]

		QueryConsult = "SELECT `ItemName`, `Count`, `ItemType`, `ID1`, `ID2`, `ID3`, `Color`, `Effect1`, `Effect2`, `Effect3`, `LifeSpan`, `Attribute`, `ItemID` FROM `bank_item` WHERE `CharID` = '%d' LIMIT %d"
		if not self.ExecuteSQL(QueryConsult, Character['Content']['CharID'], DEF.MAXBANKITEMS):
			return False
		r = self.db.store_result()
		Character['Bank'] = []
		while True:
			row = r.fetch_row()
			if row == ():
				break
			Character['Bank'] += [dict(zip(['ItemName', 'Count', 'ItemType', 'ID1', 'ID2', 'ID3', 'Color', 'Effect1', 'Effect2', 'Effect3', 'LifeSpan', 'Attribute', 'ItemID'], row[0]))]
		return Character
		
	def SavePlayerContents(self, char_name, account_name, account_password, Data):
		QueryConsult = "SELECT chr.* FROM `account_database` as acc, `char_database` as chr WHERE BINARY chr.account_name = acc.name AND BINARY acc.name = '%s' AND BINARY acc.password = '%s' AND BINARY chr.char_name = '%s'"
		if not self.ExecuteSQL(QueryConsult, account_name, account_password, char_name):
			return False
		r = self.db.store_result()
		if r.num_rows() == 0:
			return False
		try:
			CharID = int(r.fetch_row()[0][0])
		except:
			return False
		QueryConsult = "UPDATE `char_database` SET `LastSaveDate` = NOW(), `ID1` = '%d', `ID2` = '%d', `ID3` = '%d'," + \
						"`Level` = '%d',`Strength` = '%d',`Vitality` = '%d',`Dexterity` = '%d',"+\
						"`Intelligence` = '%d',`Magic` = '%d',`Agility` = '%d',"+\
						"`Luck` = '%d',`Exp` = '%lu',`Gender` = '%d',`Skin` = '%d',"+\
						"`HairStyle` = '%d',`HairColor` = '%d',`Underwear` = '%d',"+\
						"`ApprColor` = '%d',`Appr1` = '%d',`Appr2` = '%d',`Appr3` = '%d',`Appr4` = '%d',"+\
						"`Nation` = '%s',`MapLoc` = '%s',`LocX` = '%d',`LocY` = '%d',"+\
						"`Profile` = '%s',`Contribution` = '%d',`LeftSpecTime` = '%lu',"+\
						"`LockMapName` = '%s',`LockMapTime` = '%d',`BlockDate` = '%s',"+\
						"`GuildName` = '%s',`GuildID` = '%d',`GuildRank` = '%d',`FightNum` = '%d',"+\
						"`FightDate` = '%d',`FightTicket` = '%d',`QuestNum` = '%d',`QuestID` = '%d',"+\
						"`QuestCount` = '%d',`QuestRewType` = '%d',`QuestRewAmmount` = '%d'," +\
						"`QuestCompleted` = '%d',`EventID` = '%d',`WarCon` = '%d',`CruJob` = '%d',"+\
						"`CruID` = '%d',`CruConstructPoint` = '%d', `Popularity` = '%li' ,"+\
						"`HP` = '%d',`MP` = '%d',`SP` = '%d',`EK` = '%d',`PK` = '%d',"+\
						"`RewardGold` = '%d',`DownSkillID` = '%d',`Hunger` = '%d',`LeftSAC` = '%d',"+\
						"`LeftShutupTime` = '%d',`LeftPopTime` = '%lu',`LeftForceRecallTime` = '%d',"+\
						"`LeftFirmStaminarTime` = '%d',`LeftDeadPenaltyTime` = '%d',`MagicMastery` = '%s',"+\
						"`PartyID` = '%lu',`GizonItemUpgradeLeft` = '%d' WHERE `CharID` = '%d' LIMIT 1;"
		Content = Data['Player']
		if not self.ExecuteSQL(QueryConsult, 
								Content.m_sCharIDnum1, Content.m_sCharIDnum2, Content.m_sCharIDnum1, 
								Content.m_iLevel, Content.m_iStr, Content.m_iVit, Content.m_iDex,
								Content.m_iInt,Content.m_iMag,Content.m_iAgi,Content.m_iLuck,
								Content.m_iExp, Content.m_cSex, Content.m_cSkin,Content.m_cHairStyle,
								Content.m_cHairColor,Content.m_cUnderwear,Content.m_iApprColor,
								Content.m_sAppr1,Content.m_sAppr2,Content.m_sAppr3,Content.m_sAppr4,
								Content.m_cLocation, Content.m_cMapName, Content.m_sX,Content.m_sY, 
								Data['Profile'], 
								Content.m_iContribution, Content.m_iSpecialAbilityTime, Content.m_cLockedMapName, Content.m_iLockedMapTime,
								Content.m_iBlockDate, Content.m_cGuildName, Content.m_iGuildGuid, Content.m_cGuildRank,
								Content.m_iFightzoneNumber, Content.m_iReserveTime, Content.m_iFightZoneTicketNumber, Content.m_iQuest,
								Content.m_iQuestID, Content.m_iCurQuestCount, Content.m_iQuestRewardType, Content.m_iQuestRewardAmount, 
								Content.m_bIsQuestCompleted, Content.m_iSpecialEventID, Content.m_iWarContribution, Content.m_iCrusadeDuty, Content.m_dwCrusadeGUID,
								Content.m_iConstructionPoint, Content.m_iRating,Content.m_iHP,Content.m_iMP,Content.m_iSP,Content.m_iEnemyKillCount,Content.m_iPKCount,
								Content.m_iRewardGold,Content.m_iDownSkillIndex,Content.m_iHungerStatus,Content.m_iSuperAttackLeft,
								Content.m_iTimeLeft_ShutUp,Content.m_iTimeLeft_Rating,Content.m_iTimeLeft_ForceRecall,
								Content.m_iTimeLeft_FirmStaminar,Content.m_iDeadPenaltyTime,Content.MagicMastery,Content.m_iPartyID,
								Content.m_iGizonItemUpgradeLeft, CharID):
			return False
		for i in range(24):
			SkillMastery = Data['Skills'][i]
			SkillSSN = Data['Skills'][24+i]
			if not self.ExecuteSQL("UPDATE `skill` SET `SkillMastery` = '%d',`SkillSSN` = '%d' WHERE `CharID` = '%d' AND `SkillID` = '%d' LIMIT 1;",
								SkillMastery, SkillSSN, CharID, i):
					return False
		if not self.ExecuteSQL("DELETE FROM `item` WHERE CharID='%d'", CharID):
			return False
		for item in Data['Items']:
			Query = "INSERT INTO `item` (`CharID`,`ItemName`,`ItemID`,`Count`,`ItemType`,`ID1`,`ID2`,`ID3`,`Color`,`Effect1`,`Effect2`,`Effect3`,`LifeSpan`,`Attribute`,`ItemEquip`,`ItemPosX`,`ItemPosY`) "+\
					"VALUES('%d','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')"
			if not self.ExecuteSQL(Query, CharID, 
							item.m_cName,
							item.ItemUniqueID,
							item.m_dwCount,
							item.m_sTouchEffectType,
							item.m_sTouchEffectValue1,
							item.m_sTouchEffectValue2,
							item.m_sTouchEffectValue3,
							item.m_cItemColor,
							item.m_sItemSpecEffectValue1,
							item.m_sItemSpecEffectValue2,
							item.m_sItemSpecEffectValue3,
							item.m_wCurLifeSpan,item.m_dwAttribute,item.m_bIsItemEquipped, 
							item.X, item.Y):
				return False
		if not self.ExecuteSQL("DELETE FROM `bank_item` WHERE CharID='%d'", CharID):
			return False
		for item in Data["BankItems"]:
			Query = "INSERT INTO `bank_item` (`CharID`, `ItemName`,`ItemID`,`Count`,`ItemType`,`ID1`,`ID2`,`ID3`,`Color`,`Effect1`,`Effect2`,`Effect3`,`LifeSpan`,`Attribute`)" + \
						"VALUES('%d', '%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')"
			if not self.ExecuteSQL(Query, CharID,
					item.m_cName,
					item.ItemUniqueID,
					item.m_dwCount,
					item.m_sTouchEffectType,
					item.m_sTouchEffectValue1,
					item.m_sTouchEffectValue2,
					item.m_sTouchEffectValue3,
					item.m_cItemColor,
					item.m_sItemSpecEffectValue1,
					item.m_sItemSpecEffectValue2,
					item.m_sItemSpecEffectValue3,
					item.m_wCurLifeSpan,
					item.m_dwAttribute):
				return False
		return True

	def CreateNewItem(self, CharID, PosX, PosY, LifeSpan, Count, Name):
		if CharID == None:
			return False
		Query = "INSERT INTO `item` (`CharID`,`ItemName`,`Count`,`LifeSpan`,`ItemPosX`,`ItemPosY`) "+\
		"VALUES('%d','%s','%d','%d','%d','%d')"
		if not self.ExecuteSQL(Query, CharID, Name, Count, LifeSpan, PosX, PosY):
			return False
		
	def ReadDatabaseConfigFile(self, cFn):
		"""
			Parse database configuration file
		"""
		if not os.path.exists(cFn) and not os.path.isfile(cFn):
			PutLogList("(!) Cannot open database configuration file.")
			return False

		sHost = MySQL_Auth['host']
		iPort = MySQL_Auth['port']
		sUser = MySQL_Auth['user']
		sPass = MySQL_Auth['passwd']
		sDB   = MySQL_Auth['db']
		reg = re.compile('[a-zA-Z]')
		fin = open(cFn, 'r')
		try:
			for line in fin:
				if reg.match(line) == None:
					continue
					
				token = filter(lambda l: True if type(l) == int else (l.strip() != ""), map(lambda x: (lambda y: int(y) if y.isdigit() else y)(x.strip().replace('\t',' ').replace('\r', '').replace('\n','')), line.split('=')))
				
				if len(token)<2:
					continue
					
				if token[0] == "mysql-server-host":
					sHost = token[1]
					
				if token[0] == "mysql-server-port":
					iPort = token[1]
					
				if token[0] == "mysql-username":
					sUser = token[1]
					
				if token[0] == "mysql-password":
					sPass = token[1]
						
				if token[0] == "mysql-database":
					sDB = token[1]
					
		finally:
			fin.close()
		return {'host' : sHost, 'port': int(iPort), 'user': sUser, 'passwd': sPass, 'db': sDB}
