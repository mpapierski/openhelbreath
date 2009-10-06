import MySQLdb, _mysql_exceptions, time
from GlobalDef import Account, DEF
from threading import Semaphore, BoundedSemaphore

MySQL_Auth = {'host' : 'localhost', 'port': 3307, 'user': 'root', 'passwd': '', 'db': 'playerdb'}

class DatabaseDriver(object):
	def __init__(self):
		global MySQL_Auth
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

		print "(*) Connection to MySQL database was sucessfully established!"

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
		try:
			self.db.query(self.__querybuilder(Query, *Args))
		except:
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
				row = r.fetch_row()
				if row == ():
					break
				rows += [row[0]]
		except:
			return []
			
		return rows
		
	def CreateNewCharacter(self, Read):
		if not self.Ready:
			raise Exception('Database driver not ready!')

		QueryConsult = "INSERT INTO `char_database` (`account_name`, `char_name`, `Strength` , `Vitality` , `Dexterity` , `Intelligence` , `Magic` , `Agility` , `Appr1`, `Gender` , `Skin` , `HairStyle` , `HairColor` , `Underwear` , `HP` , `MP` , `SP`, `CreateDate`)" + \
							"VALUES ( '%s', '%s' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', '%d' , '%d' , '%d' , '%d' , '%d' , '%d' , '%d', NOW())"
		if not self.ExecuteSQL(QueryConsult,
							Read['AccountName'],
							Read['PlayerName'],
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
							(Read['Str']*2)+ 2):
			return False #False means no query was executed so no worry about empty skills or no items
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
													"VALUES ('%d', '%d', '%d', '%d')"
					if not self.ExecuteSQL(QueryConsult, Char_ID, s, SkillMastery, 0):
						raise Exception('This is only for sure. Propably will not ever appear.')
			except:
				print "(MySQL) Exception in CreateCharacter! Deleting char %s..." % Read['PlayerName']
				self.DeleteCharacter(Read['AccountName'], Read['AccountPassword'], Read['PlayerName'])
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
