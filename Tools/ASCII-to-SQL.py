""" 
    This file is part of OpenHelbreath.

    OpenHelbreath is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenHelbreath is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
import sys
import traceback
import os
import MySQLdb
import _mysql_exceptions
import time
import array
import re
import hashlib

# Config
cAccountDir	= "C:\\Users\H2\\Desktop\\sHelbreath\\Tools\\Account\\Account"
cCharacterDir	= "C:\\Users\\H2\\Desktop\\sHelbreath\\Tools\\Account\\Character"
MySQL_Auth = {'host' : '192.168.1.50', 'port': 3306, 'user': 'test', 'passwd': 'test', 'db': 'playerdb'}

# Variables
sVersion = "0.40"
iTotalAcct = 0
iTotalChar = 0
iTotalAcctAdd = 0
iTotalCharAdd = 0
iTotalAcctFail = 0
iTotalCharFail = 0
iCountSQLAcctErr = 0
iCountSQLCharErr = 0
iCountDupeAcct = 0
iCountDupeChar = 0
iCountInvalidAcct = 0
iCountInvalidChar = 0

# Start Python Script
def PutSQL(cQuery):
	'''
	desc
	'''
	sqlFile = open('ASCII-Import.sql', 'a')
	if not (cQuery == ""):	
		sqlFile.write('%s\n' % (cQuery))	
	sqlFile.close()

def PutLog(cMsg, bDisplay = True):
	'''
	desc
	'''
	if bDisplay:
		print cMsg
	logfile = open('ConvertLog.txt', 'a')
	if not (cMsg == ""):	
		logfile.write('%s - %s\n' % (time.asctime(time.localtime()), cMsg))	
	logfile.close()

def Terminate(cString):
	'''
	desc
	'''
	PutLog("(!) Termination: %s" % cString)
	PutLog("")
	raw_input("Press ENTER to QUIT")

def ConvertComplete(cString):
	'''
	desc
	'''
	PutLog("")		
	PutLog("Finished : %s" % cString)
	PutLog("")
	# Show Stats
	# Create a thorough log file
	PutLog("----------")		
	PutLog("Statistics")
	PutLog("----------")
	PutLog("")
	PutLog("Account")	
	PutLog("%d of %d accounts converted" % (iTotalAcctAdd, iTotalAcct))
	PutLog("%d duplicate accounts rejected" % (iCountDupeAcct))
	PutLog("%d account rejected due to SQL error" % (iCountSQLAcctErr))
	PutLog("%d corrupt account file" % (iCountInvalidAcct))
	PutLog("")
	PutLog("Character")	
	PutLog("(*) %d of %d characters converted" % (iTotalCharAdd, iTotalChar))
	PutLog("    xyz pre-existing characters")
	PutLog("    xyz corrupt character file")
	PutLog("    xyz orphaned characters")
	PutLog("")
	PutLog("Items")
	PutLog(" TODO LATER")
	
	PutLog("Review log file for more detailed statistics")
	PutLog("Check Sql file for import dump")	
	raw_input("Press ENTER to QUIT")

def iFileCount(dir_name, subdir, *args):
	'''
	desc
	'''
	fileCount = 0
	for file in os.listdir(dir_name):
		dirfile = os.path.join(dir_name, file)
		if os.path.isfile(dirfile):
			if len(args) == 0:
				fileCount += 1
			else:
				if os.path.splitext(dirfile)[1][1:] in args:
					fileCount += 1
		# recursively access file names in subdirectories
		elif os.path.isdir(dirfile) and subdir:
			fileCount += iFileCount(dirfile, subdir, *args)
	return fileCount

def dirEntries(dir_name, subdir, *args):
	'''
	Return a list of file names found in directory 'dir_name'
	If 'subdir' is True, recursively access subdirectories under 'dir_name'.
	Additional arguments, if any, are file extensions to match filenames. Matched
		file names are added to the list.
	If there are no additional arguments, all files found in the directory are
		added to the list.
	Example usage: fileList = dir_list(r'H:\TEMP', False, 'txt', 'py')
		Only files with 'txt' and 'py' extensions will be added to the list.
	Example usage: fileList = dir_list(r'H:\TEMP', True)
		All files and all the files in subdirectories under H:\TEMP will be added
		to the list.
	'''
	fileList = []
	for file in os.listdir(dir_name):
		dirfile = os.path.join(dir_name, file)
		if os.path.isfile(dirfile):
			if len(args) == 0:
				fileList.append(dirfile)
			else:
				if os.path.splitext(dirfile)[1][1:] in args:
					fileList.append(dirfile)
		# recursively access file names in subdirectories
		elif os.path.isdir(dirfile) and subdir:
			fileList += dirEntries(dirfile, subdir, *args)
	return fileList

def bDoesUserContinue():
	while 1:
		sInput = raw_input("Are you sure you want to continue? (Y/N):")
		print
		if (sInput == "Y") or (sInput == "y"):
			return True
		if (sInput == "N") or (sInput == "n"):
			return False

def main():
	global iTotalAcct, iTotalAcctFail, iTotalAcctAdd, iCountSQLAcctErr, iCountDupeAcct, iCountInvalidAcct
	global iTotalChar, iTotalCharFail, iTotalCharAdd, iCountSQLCharErr, iCountDupeChar, iCountInvalidChar

	PutLog("OpenHelbreath ASCII-to-SQL Convertion Tool (Version: %s)" % sVersion)
	PutLog("Copyright (C) 2009 by Hypnotoad")
	PutLog("This program comes with ABSOLUTELY NO WARRANTY.")
	PutLog("This is free software, and you are welcome to redistribute it under certain conditions.")
	PutLog("")
	# Check if user Account/Character directories are valid
	if (cAccountDir == ""):
		Terminate("(!) Error: Location of Account files unspecified!")
		return False;					
	else:
		if not os.path.exists(cAccountDir):
			Terminate("(!) Error: Account Directory (%s) does not exist!" % cAccountDir)
			return False
		else:
			iTotalAcct = iFileCount(cAccountDir, True, 'txt')
	if (cCharacterDir == ""):
		Terminate("(!) Error: Location of Character files unspecified!")
	else:
		if not os.path.exists(cCharacterDir):
			Terminate("(!) Error: Character Directory (%s) does not exist!" % cCharacterDir)
			return False
		else:
			iTotalChar = iFileCount(cCharacterDir, True, 'txt')		
	PutLog("(*) %d Account found - %d Character found" % (iTotalAcct, iTotalChar))

	if iTotalAcct == 0 and iTotalChar == 0:
		ConvertComplete("No character or account files to convert")
		return True
	
	# Check if SQL connection is available
	PutLog("(*) Connecting to MySQL database...")
	try:
		db = MySQLdb.connect(**MySQL_Auth)
	except _mysql_exceptions.OperationalError as (E_No, E_Str):
		Terminate("(!) MySQL ERROR #%d - %s!" % (E_No, E_Str))
		return False	
	except:
		Terminate("(!) Unhandled MySQL error")
		return False

	PutLog("(*) Connection to MySQL database was successfully established!")

	# Check if current SQL tables are valid and usable
	db.query("SHOW TABLES FROM playerdb LIKE 'account_database';")
	r = db.store_result()
	if not r.fetch_row():
		Terminate("(!) MySQL error: Table 'account_database' corrupt or invalid")
		return False

	db.query("SHOW TABLES FROM playerdb LIKE 'char_database'; ")
	r = db.store_result()
	if not r.fetch_row():
		Terminate("(!) MySQL error: Table 'char_database' corrupt or invalid")
		return False

	aFileName = []
	aExisting_acct = []
	aNew_acct = []
	db.query("SELECT name FROM account_database")
	r = db.store_result()
	if r.num_rows() == 0:
		PutLog("")
		PutLog("ASCII-to-SQL Convertion Tool will add all files to the database.")
		PutLog("Characters without an account will not be added and become orphaned.")
		PutLog("The ASCII *.txt files will not be deleted and must be removed manually.")
		PutLog("")
	else:
		PutLog("")
		PutLog("ASCII-to-SQL Convertion Tool will ONLY add NEW accounts/characters.")
		PutLog("Characters without an account will not be added and become orphaned.")
		PutLog("Pre-existing Accounts will not be deleted or modified.")
		PutLog("Characters with both an SQL DB and ASCII file account will not be added.")
		PutLog("The ASCII *.txt files will not be deleted and must be removed manually.")
		PutLog("")
		# - Add existing accounts to an array
		while True:
			row = r.fetch_row()
			if row == ():
				break
			aExisting_acct += row[0]

	if bDoesUserContinue() == False:
		Terminate("User Request")
		return False

	PutSQL("-- --------------------------------------------")
	PutSQL("-- OpenHelbreath ASCII-to-SQL Convertion Import")
	PutSQL("-- --------------------------------------------")

	PutLog("(*) Begin converting account files...")
	aFileName = dirEntries(cAccountDir, True, 'txt')
	reg = re.compile('[a-zA-Z]')
	for each in aFileName:
		if not os.path.exists(each) and not os.path.isfile(each):
			iTotalAcctFail += 1
			iCountInvalidAcct += 1
			PutLog("(!) Corrupt account file '%s' - file not found" % (each), False)
			continue
		fin = open(each, 'r')
		sName = ""
		sPassword = ""
		sQuiz = ""
		sAnswer = ""
		sRealName = ""
		sGender = ""
		sEmail = ""
		sLoginIpAddress = ""
		try:                
			for line in fin:
				if reg.match(line) == None:
					continue

				token = filter(lambda l: True if type(l) == str else (l.strip() != ""), map(lambda x: (lambda y: str(y) if y.isdigit() else y)(x.strip().replace('\t',' ').replace('\r', '').replace('\n','')), line.split('=')))

				if len(token)<2:
					continue

				"""
				-----------------------------------------------------------------------------------------
				SQL Field	ASCII field			Formatting Changes/Notes
				-----------------------------------------------------------------------------------------
				name		account-name			
				password 	account-password		encrypted to sha1
				CreateDate	Time(2003/5/10/11/15)  		Changed to time of conversion 
				Quiz		account-Quiz			
				Answer		account-Answer			
				RealName	account-RealName		
				Gender		account-Gender			Male->M;Female->F
				Email		account-Email			fix length
				ValidDate	account-valid-date/time		field unused in ASCII servers (removed)
				LoginIpAddress	IP(213.119.173.239)		removed until user logs in
				-----------------------------------------------------------------------------------------
				ASCII fields dropped Old:
				account-change-password, account-Age, account-Birth-Year, account-Birth-Month, 
				account-Birth-Day, account-SSN, account-created-by, account-change-password 
				"""

				if token[0] == "account-name":
					sName = token[1]

				if token[0] == "account-password":
					# sPassword = token[1]
					sPassword = hashlib.sha1(token[1]).hexdigest()

				if token[0] == "account-Quiz":
					sQuiz = token[1]

				if token[0] == "account-Answer":
					sAnswer = token[1]

				if token[0] == "account-RealName":
					sRealName = token[1]

				if token[0] == "account-Gender":
					if token[1] == "Male":
						sGender = "M"
					elif token[1] == "Female":
						sGender = "F"

				if token[0] == "account-Email":
					sEmail = token[1]

		finally:
			fin.close()

		#if if has minimum required fields
		# if not curropted += 1
		if (sName == "") or (sPassword == ""):
			iTotalAcctFail += 1
			iCountInvalidAcct += 1
			PutLog("(!) Corrupt account entry '%s' - name or password invalid" % (sName))
			PutLog("%s: Corrupt account Name(%s) or Password(%s)" % (each, sName, sPassword), False)
		else:
			sQuery = "INSERT INTO `playerdb`.`account_database` (`name` ,`password` ,`AccountID` ,`LoginIpAddress` ,`IsGMAccount` ,`CreateDate` ,`LoginDate`,`LogoutDate` ,`BlockDate` ,`RealName` ,`Gender` ,`Email`, `CharRecord` ,`Quiz` ,`Answer` ,`ValidDate`)"+ \
					"VALUES ('%s', '%s', NULL , '', '0', NOW(), '0000-00-00 00:00:00', '0000-00-00 00:00:00', '0000-00-00 00:00:00', '%s', '%s', '%s', '', '%s', '%s', '0000-00-00 00:00:00');" % (sName, sPassword, sRealName, sGender, sEmail, sQuiz, sAnswer)
			PutSQL(sQuery)
			
			try:
				i = aExisting_acct.index(sName)
			except ValueError:
				i = -1 # no match
			if i == -1:
				try:
					iTotalAcctAdd += 1
					PutLog("(*) Account '%s' added" % sName, False)
					db.query(sQuery)
				except:
					iTotalAcctFail += 1
					iCountSQLAcctErr += 1
					PutLog("(!) MySQL import error '%s'" % (sName))
					PutLog("%s: MySQL import error Name(%s) and sQuery(%s)" % (each, sName, sQuery), False)
			else:
				PutLog("(!) Duplicate account entry '%s' - Account already exists" % sName)
				PutLog("%s: Duplicate account entry Name(%s)" % (each, sName), False)
				iTotalAcctFail += 1
				iCountDupeAcct += 1
	PutLog("(*) ...Done!")

	PutLog("")
	PutLog("(*) Begin converting character files...")
	aFileName = dirEntries(cCharacterDir, True, 'txt')
	reg = re.compile('[a-zA-Z]')
	for each in aFileName:
		if not os.path.exists(each) and not os.path.isfile(each):
			iTotalCharFail += 1
			iCountInvalidChar += 1
			PutLog("(!) Corrupt character file '%s' - file not found" % (each), False)
			continue
		fin = open(each, 'r')
		#variables
		sAccount_name = sChar_name = sProfile = sNation = sGuildName = sGuildID = sGuildRank = sMapLoc = sLocX = sLocY = ""
		sHP = sMP = sSP = sLevel = sPopularity = sStr = sVit = sDex = sInt = sMag = sAgi = sLuck = sExp = sID1 = sID2 = sID3 = ""
		sGender = sSkin = sHairStyle = sHairColor = sUnderwear = sHunger = sEK = sPK = sRewardGold = sDownSkillID = sLeftShutupTime = ""
		sApprColor = sAppr1 = sAppr2 = sAppr3 = sAppr4 = sPartyID = sMagicMastery = sLeftPopTime = sLeftForceRecallTime = sLeftFirmStaminarTime = ""
		sLeftDeadPenaltyTime = sGizonItemUpgradeLeft = sLeftSAC = sLeftSpecTime = sAdminLevel = sBlockDate = sQuestNum = sQuestID = sQuestCount = ""
		sQuestRewType = sQuestRewAmmount = sQuestcompleted = sContribution = sWarCon = sEventID = sFightNum = sFightDate = sFightTicket = ""
		sLockMapName = sLockMapTime = sCruJob = sCruID = sCruConstructPoint = ""
		try:
			for line in fin:
				if reg.match(line) == None:
					continue

				token = filter(lambda l: True if type(l) == str else (l.strip() != ""), map(lambda x: (lambda y: str(y) if y.isdigit() else y)(x.strip().replace('\t',' ').replace('\r', '').replace('\n','')), line.split('=')))

				if len(token)<2:
					continue
				"""
				---------------------------------------------------------------------------------
				SQL Field	ASCII field			Formatting Changes/Notes
				---------------------------------------------------------------------------------
				LastSaveDate	file-saved-date			2005 1 23 22 19 -> 0000-00-00 00:00:00 (removed)
				account_name	account-name
				char_name	character-name
				Profile		character-profile 		
				Nation		character-location
				GuildName	character-guild-name
				GuildID		character-guild-GUID
				GuildRank	character-guild-rank
				MapLoc		character-loc-map
				LocX		character-loc-x
				LocY		character-loc-y
				HP		character-HP
				MP		character-MP
				SP		character-SP
				Level		character-LEVEL
				Popularity	character-RATING
				Strength	character-STR
				Vitality	character-VIT
				Dexterity	character-DEX
				Intelligence	character-INT
				Magic		character-MAG
				Agility		character-CHARISMA
				Luck		character-LUCK
				Exp		character-EXP
				ID1		character-IDnum1
				ID2		character-IDnum2
				ID3		character-IDnum3
				Gender		sex-status
				Skin		skin-status
				HairStyle	hairstyle-status
				HairColor	haircolor-status
				Underwear	underwear-status
				Hunger		hunger-status
				EK		character-EK-Count
				PK		character-PK-Count
				RewardGold	character-reward-gold
				DownSkillID	character-downskillindex
				LeftShutupTime	timeleft-shutup
				ApprColor	appr-color
				Appr1		appr1
				Appr2		appr2
				Appr3		appr3
				Appr4		appr4
				PartyID		party-id
				MagicMastery	magic-mastery
				LeftPopTime	timeleft-rating
				LeftForceRecallTime	timeleft-force-recall
				LeftFirmStaminarTime	timeleft-firm-staminar
				LeftDeadPenaltyTime	dead-penalty-time	
				GizonItemUpgradeLeft	gizon-item-upgade-left
				LeftSAC		super-attack-left
				LeftSpecTime	special-ability-time 
				AdminLevel	admin-user-level                        make adjustment to account
				BlockDate	penalty-block-date 			0 0 0 -> 0000-00-00 00:00:00
				QuestNum	character-quest-number 
				QuestID		character-quest-ID     
				QuestCount	current-quest-count
				QuestRewType	quest-reward-type      
				QuestRewAmmount	quest-reward-amount
				Questcompleted	character-quest-completed 
				Contribution	character-contribution	
				WarCon		character-war-contribution
				EventID		special-event-id 
				FightNum	reserved-fightzone-id 			changed from 0 0 0 -> 3 fields
				FightDate		above
				FightTicket		above	
				LockMapName	locked-map-name	
				LockMapTime	locked-map-time
				CruJob			crusade-job 
				CruID			crusade-GUID 
				CruConstructPoint	construct-point
				---------------------------------------------------------------------------------
				New:		CharID, CreateDate
				OLD:		character-LU_Pool
				error: 		Somehow Charisma got changed to Agility
				Rating changed to Popular
				QuestRewAmmount	 - typo
				---------------------------------------------------------------------------------
				"""
				if token[0] == "account-name":
					sAccount_name = token[1]
				if token[0] == "character-name":
					sChar_name = token[1]
				if token[0] == "character-profile":
					sProfile = token[1]
				if token[0] == "character-location":
					sNation = token[1]
				if token[0] == "character-guild-name":
					sGuildName = token[1]
				if token[0] == "character-guild-GUID":
					sGuildID = token[1]
				if token[0] == "character-guild-rank":
					sGuildRank = token[1]
				if token[0] == "character-loc-map":
					sMapLoc = token[1]
				if token[0] == "character-loc-x":
					sLocX = token[1]
				if token[0] == "character-loc-y":
					sLocY = token[1]
				if token[0] == "character-HP":
					sHP = token[1]
				if token[0] == "character-MP":
					sMP = token[1]
				if token[0] == "character-SP":
					sSP = token[1]
				if token[0] == "character-LEVEL":
					sLevel = token[1]
				if token[0] == "character-RATING":
					sPopularity = token[1]
				if token[0] == "character-STR":
					sStr = token[1]
				if token[0] == "character-VIT":
					sVit = token[1]
				if token[0] == "character-DEX":
					sDex = token[1]
				if token[0] == "character-INT":
					sInt = token[1]
				if token[0] == "character-MAG":
					sMag = token[1]
				if token[0] == "character-CHARISMA":
					sAgi = token[1]
				if token[0] == "character-LUCK":
					sLuck = token[1]
				if token[0] == "character-EXP":
					sExp = token[1]
				if token[0] == "character-IDnum1":
					sID1 = token[1]
				if token[0] == "character-IDnum2":
					sID2 = token[1]
				if token[0] == "character-IDnum3":
					sID3 = token[1]
				if token[0] == "sex-status":
					sGender = token[1]
				if token[0] == "skin-status":
					sSkin = token[1]
				if token[0] == "hairstyle-status":
					sHairStyle = token[1]
				if token[0] == "haircolor-status":
					sHairColor = token[1]
				if token[0] == "underwear-status":
					sUnderwear = token[1]
				if token[0] == "hunger-status":
					sHunger = token[1]
				if token[0] == "character-EK-Count":
					sEK = token[1]
				if token[0] == "character-PK-Count":
					sPK = token[1]
				if token[0] == "character-reward-gold":
					sRewardGold = token[1]
				if token[0] == "character-downskillindex":
					sDownSkillID = token[1]
				if token[0] == "timeleft-shutup":
					sLeftShutupTime = token[1]
				if token[0] == "appr-color":
					sApprColor = token[1]
				if token[0] == "appr1":
					sAppr1 = token[1]
				if token[0] == "appr2":
					sAppr2 = token[1]
				if token[0] == "appr3":
					sAppr3 = token[1]
				if token[0] == "appr4":
					sAppr4 = token[1]
				if token[0] == "party-id":
					sPartyID = token[1]
				if token[0] == "magic-mastery":
					sMagicMastery = token[1]
				if token[0] == "timeleft-rating":
					sLeftPopTime = token[1]
				if token[0] == "timeleft-force-recall":
					sLeftForceRecallTime = token[1]
				if token[0] == "timeleft-firm-staminar":
					sLeftFirmStaminarTime = token[1]
				if token[0] == "dead-penalty-time":
					sLeftDeadPenaltyTime = token[1]
				if token[0] == "gizon-item-upgade-left":
					sGizonItemUpgradeLeft = token[1]
				if token[0] == "super-attack-left":
					sLeftSAC = token[1]
				if token[0] == "special-ability-time":
					sLeftSpecTime = token[1]
				if token[0] == "admin-user-level":
                                        #do acct sql here - trigger bool 
					sAdminLevel = token[1]
				if token[0] == "penalty-block-date":
                                        # convert 
					sBlockDate = token[1]
				if token[0] == "character-quest-number":
					sQuestNum = token[1]
				if token[0] == "character-quest-ID":
					sQuestID = token[1]
				if token[0] == "current-quest-count":
					sQuestCount = token[1]
				if token[0] == "quest-reward-type":
					sQuestRewType = token[1]
				if token[0] == "quest-reward-amount":
					sQuestRewAmmount = token[1]
				if token[0] == "character-quest-completed":
					sQuestcompleted = token[1]
				if token[0] == "character-contribution":
					sContribution = token[1]
				if token[0] == "character-war-contribution":
					sWarCon = token[1]
				if token[0] == "special-event-id":
					sEventID = token[1]
				if token[0] == "reserved-fightzone-id":
                                        #multiple here FightNum, FightDate, and FightTicket
					sFightNum = token[1]
					sFightDate = token[1]
					sFightTicket = token[1]
				if token[0] == "locked-map-name":
					sLockMapName = token[1]
				if token[0] == "locked-map-time":
					sLockMapTime = token[1]
				if token[0] == "crusade-job":
					sCruJob = token[1]
				if token[0] == "crusade-GUID":
					sCruID = token[1]
				if token[0] == "construct-point":
					sCruConstructPoint = token[1]
		finally:
			fin.close()

	PutLog("(*) ...Done!")

	ConvertComplete("Success!")

try:
	main()
except:
	PutLog("")
	PutLog("Unexpected error (version: %s)" % sVersion)
	PutLog(sys.exc_info())
	PutLog(traceback.print_exc())
	raw_input("Press ENTER to QUIT")
