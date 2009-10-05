import MySQLdb, _mysql_exceptions, time
from GlobalDef import Account, DEF
from threading import BoundedSemaphore

MySQL_Auth = {'host' : 'localhost', 'port': 3307, 'user': 'root', 'passwd': '', 'db': 'playerdb'}

class DatabaseDriver(object):
	def __init__(self):
		global MySQL_Auth
		Default = {'host' : 'localhost', 'port': 3306, 'user': 'root', 'passwd': '', 'db': 'playerdb'}
		for k in Default.keys():
			if k not in MySQL_Auth:
				MySQL_Auth[k] = Default[k]
		self.Ready = False
		self.Access = BoundedSemaphore(10) #change if server is laggy
		
	def Initialize(self):
		if self.Ready:
			print "(!) MySQL Driver already initialized!"
			return False
		global MySQL_Auth
		print "(!) Connecting to mySql database..."
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

		print "-Connection to mySQL database was sucessfully established!"

		return True

	def CheckDatabase(self):
		if not self.Ready:
			return False
		self.Access.acquire()
		self.db.query("SHOW TABLES")
		r = self.db.use_result()
		Tables = ('account_database', 'bank_item', 'char_database', 'guild', 'guild_member', 'ipblocked', 'item', 'setup', 'skill')
		PlayerDB = []
		while True:
			row = r.fetch_row()
			if row == ():
				break
			table_name = row[0][0]
			PlayerDB += [table_name]

		if len(PlayerDB) != len(Tables):
			self.Access.release()
			return False
		ile = 0
		for i in PlayerDB:
			ok = False
			for j in Tables:
				if i == j:
					ile += 1
		self.Access.release()
		return ile == len(Tables)
		
	def ChangePassword(self, LoginName, Password, NewPassword):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		self.Access.acquire()
		QueryConsult = "UPDATE `account_database` SET `password` = '%s' WHERE BINARY `name` = '%s' AND BINARY `password` = '%s' LIMIT 1" % (self.db.escape_string(NewPassword), self.db.escape_string(LoginName), self.db.escape_string(Password))
		self.db.query(QueryConsult)
		return self.db.affected_rows() > 0
		
	def CheckAccountLogin(self, LoginName, Password):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		self.Access.acquire()
		QueryConsult = "SELECT `name`, `password`, `BlockDate` FROM `account_database` WHERE BINARY `name` = '%s' LIMIT 1" % (self.db.escape_string(LoginName))
		self.db.query(QueryConsult)
		r = self.db.store_result()
		if r.num_rows() == 0:
			self.Access.release()
			return (Account.NOTEXISTS,)
		
		row = r.fetch_row()[0]
		if Password != row[1]:
			self.Access.release()
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
		
		self.Access.release()
		return (Account.OK,)
		
	def CharacterExists(self, char_name):
		QueryConsult = "SELECT `CharID` FROM `char_database` WHERE BINARY `char_name` = '%s'" % (self.db.escape_string(char_name))
		self.db.query(QueryConsult)
		r = self.db.store_result()
		return r.num_rows() > 0
		
	def GetAccountCharacterList(self, account_name, account_password):
		QueryConsult = "SELECT chr.* FROM `account_database` as acc, `char_database` as chr WHERE BINARY chr.account_name = acc.name AND BINARY acc.name = '%s' AND BINARY acc.password = '%s'" % (self.db.escape_string(account_name), self.db.escape_string(account_password))
		self.db.query(QueryConsult)
		r = self.db.store_result()
		if r.num_rows() == 0:
			return []
		rows = []	
		while True:
			row = r.fetch_row()
			if row == ():
				break
			rows += [row]
		return rows
		
	def CreateNewCharacter(self, Read):
		QueryConsult = "INSERT INTO `char_database` (`account_name`, `char_name`, `Strength` , `Vitality` , `Dexterity` , `Intelligence` , `Magic` , `Agility` , `Appr1`, `Gender` , `Skin` , `HairStyle` , `HairColor` , `Underwear` , `HP` , `MP` , `SP`, `CreateDate`)" + \
							"VALUES ( '%s', '%s' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', NOW())" % (
							self.db.escape_string(Read['AccountName']),
							self.db.escape_string(Read['PlayerName']),
							Read['Str'],
							Read['Vit'],
							Read['Dex'],
							Read['Int'],
							Read['Mag'],
							Read['Agi'],
							((Read['HairStyle'] << 8) | (Read['HairCol'] << 4) | (Read['UnderCol'])), #Appr1
							Read['Gender'],
							Read['SkinCol'],
							Read['HairStyle'],
							Read['HairCol'],
							Read['UnderCol'],
							(Read['Vit']*3)+(Read['Str']/2)+2,
							(Read['Mag']*2)+(Read['Int']/2)+2,
							(Read['Str']*2)+ 2)
		self.db.query(QueryConsult)
		if self.db.affected_rows() > 0:
			try:
				Char_ID = self.db.insert_id()
				for s in range(DEF.MAXSKILLS):
					if s in [4, 5, 7]:
						#`SkillID`, `SkillMastery` , `SkillSSN`
						SkillMastery = 20
					elif s == 3:
						SkillMastery = 3
					else:
						SkillMastery = 0
					QueryConsult = "INSERT INTO `skill` ( `CharID` , `SkillID`, `SkillMastery` , `SkillSSN`)" + \
													"VALUES ('%d', '%d', '%d', '%d')" % (Char_ID, s, SkillMastery, 0)
					self.db.query(QueryConsult)
			except:
				print "(MySQL) Exception in CreateCharacter! Deleting char %s..." % Read['PlayerName']
				self.DeleteCharacter(Read['AccountName'], Read['AccountPassword'], Read['PlayerName'])
				return False
		return True
		
	def DeleteCharacter(self, account_name, account_password, char_name):
		try:
			Ch = self.GetAccountCharacterList(account_name, account_password)
			if len(Ch) == 0:
				return False
			Found = False
			for C in Ch:
				if C[0][2] == char_name:
					Found = True
					
			if not Found:
				return False
				
			QueryConsult = "DELETE FROM `char_database` WHERE BINARY account_name='%s' AND BINARY char_name='%s'" % (self.db.escape_string(account_name), self.db.escape_string(char_name))
			self.db.query(QueryConsult)
			
			if self.db.affected_rows() == 0:
				return False

			for table_name in ['skill','item','bank_item']:
				QueryConsult = "DELETE FROM `%s` WHERE CharID = (SELECT `CharID` FROM `char_database` WHERE BINARY char_name='%s')" % (table_name, self.db.escape_string(char_name))
				self.db.query(QueryConsult)
		except:
			return False
			
		return True
