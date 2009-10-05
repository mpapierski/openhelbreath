import MySQLdb, _mysql_exceptions, time
from GlobalDef import Account
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
		QueryConsult = "UPDATE `account_database` SET `password` = '%s' WHERE `name` = '%s' AND `password` = '%s' LIMIT 1" % (NewPassword, LoginName, Password)
		self.db.query(QueryConsult)
		return self.db.affected_rows() > 0
		
	def CheckAccountLogin(self, LoginName, Password):
		if not self.Ready:
			raise Exception('Database driver not ready!')
		self.Access.acquire()
		QueryConsult = "SELECT `name`, `password`, `BlockDate` FROM `account_database` WHERE `name` = '%s' LIMIT 1" % (self.db.escape_string(LoginName))
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
				#print "(!) Account %s blocked till %s tries to login." % (LoginName, row[2])
				return (Account.BLOCKED, tm.tm_year, tm.tm_mon, tm.tm_mday)
			else:
				return (Account.OK, )
		
		self.Access.release()
		return (Account.OK,)

"""DD = DatabaseDriver()
if DD.Initialize():
	print "ALL RIGHT"
	ok = DD.CheckAccountLogin("asdf", "zxcv")
	print ok
	print Account.reverse_lookup_without_mask(ok[0])
else:
	print "FAIL"
"""
