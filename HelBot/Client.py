from NetMessages import Packets
from Socket import clientSocket
from threading import Thread
from collections import namedtuple
from Timer import TimerManager
import struct
import random
import time

nozeros = lambda x: x[0:x.find('\x00')] if x.find('\x00')>-1 else x
fillzeros = lambda txt, count: (txt + ("\x00" * (count-len(txt))))[:count]
packet_format = lambda x: nozeros(x) if type(x) != int else x

class XSocket(clientSocket):
	def Write(self, MsgID, MsgType, data, cKey = -1):
		dwSize = len(data)+3
		buffer = struct.pack('<Lh', MsgID, MsgType) + data[:]

		if cKey == -1:
			cKey = random.randint(0, 255)
			
		if cKey > 0:
			buffer = map(ord, buffer)#list(data)
			for i in range(len(buffer)):#range(dwSize):
				buffer[i] = buffer[i] + (i ^ cKey)
				buffer[i] = buffer[i] ^ (cKey ^ (len(buffer) - i))
			buffer = "".join(map(lambda x: chr(x & 255) , buffer))
		buffer = chr(cKey) + struct.pack('h', len(buffer)+3) + buffer
		self.sock.send(buffer)

class Helbreath():
	def __init__(self, Cfg):
		self.Config = Cfg
		self.AutoMSG = 0
		
	def Login(self):
		self.AutoMSG = Packets.MSGID_REQUEST_LOGIN
		self.LSock = XSocket({'host': self.Config['IP'], 'port': self.Config['Port'], 'onConnect': self.LSock_Connect, 'onDisconnect': self.LSock_Disconnect, 'onRead': self.LSock_Read})
		self.LoggedIn = False
		self.Status = 0
		self.char_list = []
		self.LSock.Active = True
		self.LSock.join()
		self.Timers = TimerManager()
		del self.LSock
		
		return self.Status
		
	def EnterGame(self):
		if not self.LoggedIn:
			return False
		self.LSock = XSocket({'host': self.Config['IP'], 'port': self.Config['Port'], 'onConnect': self.LSock_Connect, 'onDisconnect': self.LSock_Disconnect, 'onRead': self.LSock_Read})
		self.AutoMSG = Packets.MSGID_REQUEST_ENTERGAME
		self.Status = False
		self.LSock.Active = True
		self.LSock.join()
		del self.LSock
		if self.Status == False:
			return False
		else:
			self.LSock = XSocket({'host': self.Status[0], 'port': self.Status[1], 'onConnect': self.LSock_Connect, 'onDisconnect': self.LSock_Disconnect, 'onRead': self.LSock_Read})
			self.AutoMSG = Packets.MSGID_REQUEST_INITPLAYER
			self.Status = False
			self.LSock.Active = True
			return True
	def run(self):
		ok=Acc.Login()
		if ok == Packets.DEF_MSGTYPE_CONFIRM:
			print "Logged in."
			if Acc.EnterGame() == False:
				print "Unable to log into game server."
			else:
				print "Logged into game server."
		else:
			print "Could not login."
			
	def LSock_Connect(self, sender):
		#global Config
		#print "Connected to login server at %s:%d" % (Config['IP'], Config['Port'])
		if self.AutoMSG == Packets.MSGID_REQUEST_LOGIN:
			self.LSock.Write(Packets.MSGID_REQUEST_LOGIN, 0, struct.pack('<10s10s30s', self.Config['Account'], self.Config['Password'], self.Config['WorldServerName']))
		elif self.AutoMSG == Packets.MSGID_REQUEST_ENTERGAME:
			chr = None
			for c in self.char_list:
				if c.CharName == self.Config['CharName']:
					chr = c
					break
			self.Player = chr
			self.LSock.Write(Packets.MSGID_REQUEST_ENTERGAME, Packets.DEF_ENTERGAMEMSGTYPE_NEW, struct.pack('<10s10s10s10si30s120s', self.Config['CharName'], chr.MapLoc, self.Config['Account'], self.Config['Password'], chr.Level, self.Config['WorldServerName'],""))

		elif self.AutoMSG == Packets.MSGID_REQUEST_INITPLAYER:
			self.LSock.Write(Packets.MSGID_REQUEST_INITPLAYER, 0, struct.pack('<10s10s10s?20s', self.Player.CharName, self.Config['Account'],self.Config['Password'], False, ""))

			
	def LSock_Disconnect(self, sender):
		pass
		
	def LSock_Read(self, sender, data):
		self.Status = "error"
		while len(data) > 0:
			format = '<Bh'
			header_size = struct.calcsize(format)
			if len(data) < header_size:
				raise Exception
			s = struct.unpack(format, data[:header_size])
			Header = namedtuple('Header', 'cKey dwSize')._make(s)
			size = len(data)
			data = data[header_size:]
			buffer = data[:Header.dwSize-3]
			data = data[Header.dwSize-3:]

			if Header.cKey > 0:
				Decode = lambda buffer, dwSize, cKey: "".join(map(lambda n: (lambda asdf: chr(asdf & 255))((ord(buffer[n]) ^ (cKey ^ (dwSize - n))) - (n ^ cKey)), range(len(buffer))))
				buffer = Decode(buffer, Header.dwSize-3, Header.cKey)
			
			self.Status = 0
			
			MsgID = struct.unpack('<L', buffer[:4])[0]
			buffer = buffer[4:]
			if MsgID == Packets.MSGID_RESPONSE_LOG:
				self.OnAccountLogin(buffer)
				sender.disconnect()
			elif MsgID == Packets.MSGID_RESPONSE_ENTERGAME:
				self.OnResponseEnterGame(buffer)
				sender.disconnect()
			#elif MsgID in [Packets.MSGID_REQUEST_INITDATA, Packets.MSGID_RESPONSE_INITPLAYER]:
			elif MsgID == Packets.MSGID_RESPONSE_INITPLAYER:
				self.InitPlayerResponseHandler(buffer)
			elif MsgID == Packets.MSGID_RESPONSE_INITDATA:
				#self.RequestInitDataHandler(buffer)
				self.InitDataResponseHandler(buffer)
			elif MsgID == Packets.MSGID_RESPONSE_NOTICEMENT:
				self.ResponseNoticementHandler(buffer)
			else:
				#if MsgID in Packets:
				#	print "MsgID: %s" % (Packets.reverse_lookup_without_mask(MsgID))
				#else:
				print "MsgID: 0x%08X %db" % (MsgID, len(data))
	def RequestNoticement(self):
		try:
			f = open("CONTENTS\\contents1000.txt", "r")
			try:
				fs = len(f.read())
			finally:
				f.close()
		except:
			fs = 0
			
		self.LSock.Write(Packets.MSGID_REQUEST_NOTICEMENT, 0, struct.pack('<L', fs))
		
	def ResponseNoticementHandler(self, buffer):
		
		MsgType = struct.unpack('<h', buffer[:2])[0]
		buffer=buffer[2:]
		if MsgType == Packets.DEF_MSGTYPE_CONFIRM:
			pass
		elif MsgType == Packets.DEF_MSGTYPE_REJECT:
			print buffer
			f = open("CONTENTS\\contents1000.txt", "w")
			try:
				f.write(buffer)
			finally:
				f.close()
			
	def InitDataResponseHandler(self, buffer):
		print "Data response: %d " % len(buffer)
		self.RequestNoticement()
		self.Timers.register_timer(self.__checkconnection, 'check_conn', 8.0, True)
		
	def __checkconnection(self):
		t = int(time.time())
		self.LSock.Write(Packets.MSGID_COMMAND_CHECKCONNECTION, 0, struct.pack('<L', t))
		
	def InitPlayerResponseHandler(self, buffer):
		MsgType = struct.unpack('<h', buffer[:2])[0]
		if MsgType == Packets.DEF_MSGTYPE_CONFIRM:
			self.LSock.Write(Packets.MSGID_REQUEST_INITDATA, 0, struct.pack('<10s10s10s?20s', self.Player.CharName, self.Config['Account'], self.Config['Password'], False, ""))
		elif MsgType == Packets.DEF_MSGTYPE_REJECT:
			print "Reject in init data handler"
			self.LSock.disconect()
			
	def OnResponseEnterGame(self, buffer):
		global packet_format
		MsgType = struct.unpack('<h', buffer[:2])[0]
		buffer=buffer[2:]
		if MsgType == Packets.DEF_ENTERGAMERESTYPE_REJECT:
			self.Status = False
			return
		elif MsgType == Packets.DEF_ENTERGAMERESTYPE_CONFIRM:
			self.Status = True
			fmt = "<16sh"
			fmt_s = struct.calcsize(fmt)
			self.Status = map(packet_format, struct.unpack(fmt, buffer[:fmt_s]))
			return
		else:
			print Packets.reverse_lookup_without_mask(MsgType)
			self.Status = False

	def OnAccountLogin(self, buffer):
		
		MsgType = struct.unpack('<h', buffer[:2])[0]
		buffer=buffer[2:]
		
		self.Status = MsgType
		
		if MsgType == Packets.DEF_MSGTYPE_CONFIRM:
			print "Account %s login ok... Retrieving character list." % self.Config['Account']
			account_fmt = "<2H13xb" #12x -> dates -> can skip
			account_size = struct.calcsize(account_fmt)
			account = struct.unpack(account_fmt, buffer[:account_size])
			buffer = buffer[account_size:]
			account = namedtuple('Account','LowerVersion UpperVersion CharCount')._make(account)
			char_format = "<10sx12xhi6h4x10x10s"
			char_size=struct.calcsize(char_format)
			character = namedtuple('Character','CharName Level Exp Str Vit Dex Int Mag Chr MapLoc')
			char_list = []
			for c in range(account.CharCount):
				tmp=buffer[:char_size]
				buffer=buffer[char_size:]
				tmp=map(packet_format, struct.unpack(char_format, tmp))
				char_list += [character._make(tmp)]
			self.char_list = char_list
			self.LoggedIn = True
			return True
		elif MsgType == Packets.DEF_LOGRESMSGTYPE_REJECT:
			print "Account %s blocked!" % self.Config['Account']
			return False
		elif MsgType == Packets.DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
			print "Account %s password mismatch!" % self.Config['Password']
			return False
		elif MsgType == Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
			print "Account %s does not exists!" % self.Config['Account']
			return False
		elif MsgType == Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER:
			print "Account %s: World server is not activated" % (self.Config['Account'])
			return False
		else:
			print Packets.reverse_lookup_without_mask(MsgType)
			return False
			
Acc = Helbreath({'IP': '212.191.65.218', 'Port': 2848, 'WorldServerName': 'WS1', 'Account': 'Drajwer', 'Password': 'openhb', 'CharName': 'Drajwer'})
Acc.run()
