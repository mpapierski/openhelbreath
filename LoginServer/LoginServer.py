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

import socket, os, sys, select, struct, time, re, random
from Enum import Enum
from threading import Thread, Semaphore, Event
from NetMessages import Packets
from GlobalDef import DEF, Account, Logfile, Version
from Helpers import Callbacks, PutLogFileList, PutLogList
from Sockets import ServerSocket
from Database import DatabaseDriver
from collections import namedtuple
from Timer import TimerManager

nozeros = lambda x: x[0:x.find('\x00')] if x.find('\x00')>-1 else x
fillzeros = lambda txt, count: (txt + ("\x00" * (count-len(txt))))[:count]
packet_format = lambda x: nozeros(x) if type(x) != int else x

class CGameServer(object):
	def __init__(self, id, sock):
		self.AliveResponseTime = time.time()
		self.GSID = id
		self.socket = sock
		self.MapName = []
		self.GameServerSocket = []
		self.Data = {}
		self.Config = {}
		self.IsRegistered = False
		self.Database = None

class CLoginServer(object):
	def __init__(self):
		"""
			Initializing login server
		"""
		self.MainSocket = None
		self.GateServerSocket = None
		self.ListenAddress = ""
		self.ListenPort = 2748
		self.GateServerPort = 0
		self.GameServer = {}
		self.ListenToAllAddresses = True
		self.ListenPortDefault = True
		self.PermittedAddress = []
		self.MaxTotalUsers = 1000
		self.WorldServerName = "WS1"
		self.Clients = []
		self.ServerShutdownCount = 0
		self.Timers = TimerManager()
		self.Timers.register_timer(self.__gameserver_alive, 'gameserver_alive', 5.0, True)
		PutLogFileList("", Logfile.EVENTS)
		PutLogFileList("Starting new session...", Logfile.EVENTS)
		
	def CommandHandler(self, command):
		tok = command.split(" ")
		if len(tok)==0:
			return
		if tok[0].lower() == "list" and len(tok) == 2:
			if tok[1].lower() == "gameservers":
				print "Game server list:"
				for id in self.GameServer:
					print " - GSID: %d Name: %s Maps: %d Registered: %s SLSock: %d/%d" % (
								id,
								self.GameServer[id].Data['ServerName'],
								len(self.GameServer[id].MapName),
								["False","True"][self.GameServer[id].IsRegistered],
								len(self.GameServer[id].GameServerSocket),
								DEF.MAXSOCKETSPERSERVER)
					for s in self.GameServer[id].MapName:
						print "    * %s" % s
					print
					print self.GameServer[id].Data
				return
			elif tok[1].lower() == "clients":
				print "Client list:"
				for i in self.Clients:
					print i
				return
		elif tok[0].lower() == "update":
			self.SendUpdatedConfigToAllServers()
			return
		elif tok[0].lower() == "shutdown":
			self.ProcessShutdown()
			return
		elif tok[0].lower() == "help":
			print "usage: [command] [argument]"
			print "help\t\t: Print this help message"
			print "list arg\t: Show current clients or gameservers initialized (gameservers, clients)"
			print "shutdown\t: Send server shutdown announcement"
			print "update\t\t: Send updated configuration files to all servers"
			return
		print "(***) Unknown command: %s" % tok[0].upper()
		
	def DoInitialSetup(self):
		"""
			Loading main configuration, and initializing Database Driver
			(For now, its MySQL)
		"""
		if not self.ReadProgramConfigFile("LServer.cfg"):
			return False
		self.Database = DatabaseDriver()
		if not self.Database.Initialize():
			PutLogList("(!) DatabaseDriver initialization fails!")
			return False
		return True
		
	def GateServer_OnConnect(self, sender):
		"""
			Triggered when any client connects to Gate Server. Do nothing
		"""
		#print "(*) GateServer -> Accepted connection"
		pass
		
	def GateServer_OnDisconnected(self, sender):
		"""
			Triggered when any client disconnects from Gate Server.
			Check if Sender (ClientSocket class) is registered as sub-log-socket
			or Gate Server Socket. Unfortunatelly we can unregister sub-log-socket from
			registered Gate Server, but can't unload whole Game Server.
			Because Main GS socket disconnects at first.
			TODO: Inject Gate Server method in Sender's callbacks
		"""
		for i in self.GameServer.values():
			for j in i.GameServerSocket:
				if j == sender:
					PutLogList("(!) Lost connection to sub log socket on %s [GSID: %d]" % (i.Data['ServerName'],i.GSID), Logfile.ERROR)
					i.GameServerSocket.remove(sender)
					return
		GS = self.SockToGS(sender)
		if GS != None:
			PutLogList("(*) GateServer %s -> Lost connection" % (GS.Data['ServerName']), Logfile.ERROR)
		else:
			PutLogList("Lost unknown connection on GateServer (not registered? hack attempt?)", Logfile.ERROR)

		for id in self.GameServer:
			if self.GameServer[id] == GS:
				del self.GameServer[id]
				break
		
	def GateServer_OnListen(self, sender):
		"""
			When socket is ready to accept connections
		"""
		PutLogList("(*) GateServer -> Server open")
		
	
	def SockToGS(self, sender):
		"""
			Finding GameServer by Sender's class
			Returns: Instance of CGameServer class
		"""
		for i in self.GameServer.values():
			if i.socket == sender:
				return i
		for i in self.GameServer.values():
			for j in i.GameServerSocket:
				if j == sender:
					return i
		
				
	def GateServer_OnReceive(self, sender, size):
		"""
			Triggered when any data is available on Sock's buffer
		"""
		buffer = sender.receive(size)
		try:
			format = '<Bh'
			header_size = struct.calcsize(format)
			if len(buffer) < header_size:
				raise Exception
			s = struct.unpack(format, buffer[:header_size])
			Header = namedtuple('Header', 'cKey dwSize')._make(s)
			buffer = buffer[header_size:]
		except:
			sender.disconnect()
			return
			
		if Header.dwSize != size or size < 4 or Header.dwSize < 4:
			PutLogList("(!) %s Header.dwSize does not match buffer size. Hack!" % sender.address, Logfile.HACK)
			sender.disconnect()
			return

		if Header.cKey > 0:
			Decode = lambda buffer, dwSize, cKey: "".join(map(lambda n: (lambda asdf: chr(asdf & 255))((ord(buffer[n]) ^ (cKey ^ (dwSize - n))) - (n ^ cKey)), range(len(buffer))))
			buffer = Decode(buffer, Header.dwSize-3, Header.cKey)
				
		MsgID = struct.unpack('<L', buffer[:4])[0]
		buffer = buffer[4:]
		
		if MsgID == Packets.MSGID_REQUEST_REGISTERGAMESERVER:
			self.RegisterGameServer(sender, buffer)
			
		elif MsgID == Packets.MSGID_REQUEST_REGISTERGAMESERVERSOCKET:
			self.RegisterGameServerSocket(sender, buffer)
			
		elif MsgID == Packets.MSGID_GAMESERVERALIVE:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.GameServerAliveHandler(GS, buffer)
				
		elif MsgID == Packets.MSGID_REQUEST_PLAYERDATA:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.ProcessRequestPlayerData(sender, buffer, GS)

		elif MsgID == Packets.MSGID_SERVERSTOCKMSG:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.ServerStockMsgHandler(GS, buffer);

		elif MsgID in [Packets.MSGID_REQUEST_SAVEPLAYERDATALOGOUT, Packets.MSGID_REQUEST_SAVEPLAYERDATA_REPLY]:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.ProcessClientLogout(buffer, GS, True)
				
		elif MsgID == Packets.MSGID_REQUEST_NOSAVELOGOUT:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.ProcessClientLogout(buffer, GS, False)

		elif MsgID == Packets.MSGID_ENTERGAMECONFIRM:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.EnterGameConfirm(buffer, GS)

		elif MsgID == Packets.MSGID_GAMEMASTERLOG:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				PutLogFileList(buffer, Logfile.GM, True)

		elif MsgID in [Packets.MSGID_GAMEITEMLOG, Packets.MSGID_ITEMLOG]:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				PutLogFileList(buffer, Logfile.ITEM, True)

		elif MsgID == Packets.MSGID_GAMECRUSADELOG:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				PutLogFileList(buffer, Logfile.CRUSADE, True)

		elif MsgID == Packets.MSGID_REQUEST_SETACCOUNTWAITSTATUS:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.SetAccountServerChangeStatus(buffer, True)
				
		elif MsgID in [Packets.MSGID_REQUEST_CREATENEWGUILD, 
						Packets.MSGID_REQUEST_DISBANDGUILD,
						Packets.MSGID_REQUEST_UPDATEGUILDINFO_NEWGUILDSMAN,
						Packets.MSGID_REQUEST_UPDATEGUILDINFO_DELGUILDSMAN]:
			GS = self.SockToGS(sender)
			if GS != None and GS.IsRegistered:
				self.GuildHandler(MsgID, buffer, GS)
				
		else:
			if MsgID in Packets:
				PutLogFileList("MsgID: %s (0x%08X) %db * %s" % (Packets.reverse_lookup_without_mask(MsgID), MsgID, len(buffer), repr(buffer)), Logfile.PACKETGS)
			else:
				PutLogFileList("MsgID: 0x%08X %db * %s" % (MsgID, len(buffer), repr(buffer)), Logfile.PACKETGS)
				
	def GateServer_OnClose(self, sender, size):
		"""
			Triggered when Gate Server thread is closed
		"""
		PutLogList("(*) GateServer -> Server close")
		
	def InitServer(self):
		"""
			Load all HG configs and create sockets
			Returns: True if OK, False if fails
		"""
		if not self.bReadAllConfig():
			return False
		
		GateServerCB = {'onConnected': self.GateServer_OnConnect,
						'onDisconnected': self.GateServer_OnDisconnected,
						'onListen': self.GateServer_OnListen,
						'onReceive': self.GateServer_OnReceive,
						'onClose': self.GateServer_OnClose}

		MainSocketCB = {'onConnected': self.MainSocket_OnConnect,
						'onDisconnected': self.MainSocket_OnDisconnected,
						'onListen': self.MainSocket_OnListen,
						'onReceive': self.MainSocket_OnReceive,
						'onClose': self.MainSocket_OnClose}

		if self.ListenToAllAddresses:
			PutLogList("(!) permitted-address line not found in LServer.cfg. Server will be listening to all IPs!")

		if self.ListenPortDefault:
			PutLogList("(*) login-server-port line not found in LServer.cfg. Server will use port %d" % self.ListenPort)

		self.GateServerSocket = ServerSocket((self.ListenAddress, self.GateServerPort), GateServerCB)
		self.GateServerSocket.start()
		PutLogList("(*) Gate server successfully started!")

		self.MainSocket = ServerSocket((self.ListenAddress, self.ListenPort), MainSocketCB)
		self.MainSocket.start()
		PutLogList("(*) Login server sucessfully started!")
		
		return True
			
	def bReadAllConfig(self):
		"""
			Reading HG cfgs in order
		"""
		Files = ["Item.cfg", "Item2.cfg", "Item3.cfg", "Item4.cfg", "BuildItem.cfg",
				"DupItemID.cfg", "Magic.cfg", "noticement.txt", 
				"NPC.cfg", "Potion.cfg", "Quest.cfg", "Skill.cfg",
				"AdminSettings.cfg", "Settings.cfg"]
		self.Config = {}
		for n in Files:
			if not self.ReadConfig("Config/%s" % n):
				return False
		return True
		
	def ReadProgramConfigFile(self, cFn):
		"""
			Parse main configuration file
		"""
		if not os.path.exists(cFn) and not os.path.isfile(cFn):
			PutLogList("(!) Cannot open configuration file.")
			return False
			
		reg = re.compile('[a-zA-Z]')
		fin = open(cFn, 'r')
		try:
			for line in fin:
				if reg.match(line) == None:
					continue
					
				token = filter(lambda l: True if type(l) == int else (l.strip() != ""), map(lambda x: (lambda y: int(y) if y.isdigit() else y)(x.strip().replace('\t',' ').replace('\r', '').replace('\n','')), line.split('=')))
				
				if len(token)<2:
					continue
					
				if token[0] == "login-server-address":
					self.ListenAddress = token[1]
					PutLogList("(*) Login server address : %s" % (self.ListenAddress))
					
				if token[0] == "login-server-port":
					self.ListenPort = token[1]
					PutLogList("(*) Login server port : %d" % (self.ListenPort))
					if self.ListenPortDefault:
						self.ListenPortDefault = False
					
				if token[0] == "gate-server-port":
					self.GateServerPort = token[1]
					PutLogList("(*) Gate Server port : %d" % (self.GateServerPort))
					
				if token[0] == "permitted-address":
					if token[1] not in self.PermittedAddress:
						self.PermittedAddress += [token[1]]
						PutLogList("(*) IP [%s] added to permitted addresses list!" % (token[1]))
					if self.ListenToAllAddresses:
						self.ListenToAllAddresses = False
						
				if token[0] == "max-total-users":
					self.MaxTotalUsers = token[1]
					PutLogList("(*) Max total users allowed on server : %d" % self.MaxTotalUsers)
					
				if token[0] == "world-server-name":
					self.WorldServerName = token[1]
					PutLogList("(*) World Server Name : %s" % self.WorldServerName)
		finally:
			fin.close()
		return True
			
	def ReadConfig(self, FileName):
		"""
			Read contents of file to Config dict
		"""
		if not os.path.exists(FileName) and not os.path.isfile(FileName):
			PutLogList("(!) Cannot open configuration file [%s]." % FileName)
			return False
		key = FileName.split('/')[-1].split(".")[0]
		fin = open(FileName,'r')
		PutLogList("(*) Reading configuration file [%s] -> {'%s'}..." % (FileName, key))
		try:
			self.Config[key] = fin.read()
		finally:
			fin.close()
		return True
		
	def RegisterGameServer(self, sender, data):
		"""
			Registering new Game Server
		"""
		(ok, GSID, GS) = self.TryRegisterGameServer(sender, data)
		PacketID = Packets.DEF_MSGTYPE_REJECT if ok == False else Packets.DEF_MSGTYPE_CONFIRM
		SendData = struct.pack('<BhL2h', 0, 11, Packets.MSGID_RESPONSE_REGISTERGAMESERVER, PacketID, GSID) #cKey -> 0, dwSize = 1* 4b int + 2* 2b word
		sender.client.send(SendData)
		if GS != None:
			PutLogList("(*) Game Server registered at ID[%u]-[%u]. Maps: %s" % (GSID, GS.Data['InternalID'], ", ".join(GS.MapName)))
		else:
			PutLogList("(!) Game Server registration rejected! IP[%s]" % sender.address, Logfile.HACK)
		
	def FindNewGSID(self):
		"""
			Finding new GameServer
			TODO: Convert to lambda
		"""
		return len(self.GameServer.keys())+1
		
	def TryRegisterGameServer(self, sender, data):
		"""
			Read data from buffer and register HG
			TODO: Detect more security vuln
			Returns: Tuple ( OK/Fail, GS_ID/-1, CGameServer instance/None)
		"""
		global nozeros
		Read = {}
		Request = struct.unpack('h', data[:2])[0]
		if Request != Packets.DEF_LOGRESMSGTYPE_CONFIRM:
			PutLogList("Unknown Register Game Server Packet ID")
			return (False, -1, None)
		data = data[2:]
		Read['ServerName'] = nozeros(data[:10])
		Read['ServerIP'] = nozeros(data[10:26])
		Read['ServerPort'] = struct.unpack('h', data[26:28])[0]
		Read['ReceivedConfig'] = ord(data[28])
		Read['NumberOfMaps'] = ord(data[29])
		if Read['NumberOfMaps'] == 0:
			return (False, -1, None)

		Read['InternalID'] = struct.unpack('h', data[30:32])[0] #ord(data[30])
		
		if sender.address not in self.PermittedAddress and not self.ListenToAllAddresses:
			PutLogList("(!) %s is not in permitted address list and tries to register Game Server!" % sender.address, Logfile.HACK)
			return (False, -1, None)
			
		if (lambda gs_name: [] != filter(lambda x:x, map(lambda y: y.Data.get('ServerName','') == gs_name, self.GameServer.values())))(Read['ServerName']):
			IP = filter(lambda x: x.Data['ServerName'] == Read['ServerName'], self.GameServer.values())
			IP = IP[0].socket.address
			PutLogList("(!) %s tries to login already registered server named %s [Registered from IP: %s] !" % (Read['ServerIP'], Read['ServerName'], ""), Logfile.HACK)
			return (False, -1, None)
		
		NGSID = self.FindNewGSID()
		GS = CGameServer(NGSID, sender)
		GS.Data = Read
		data = data[32:]
		while len(data)>0:
			map_name = nozeros(data[:11])
			GS.MapName += [map_name]
			data = data[11:]
		if not GS.Data['ReceivedConfig']:
			self.SendConfigToGS(GS)
		self.GameServer[NGSID] = GS
		return (True, NGSID, GS)
		
	def SendMsgToGS(self, GS, data):
		"""
			Sending data to Game Server
		"""
		cKey = 0
		dwSize = len(data)+3
		Buffer = chr(cKey) + struct.pack('h', dwSize) + data
		if cKey > 0:
			for i in range(dwSize):
				Buffer[3+i] = chr(ord(Buffer[3+i]) + (i ^ cKey))
				Buffer[3+i] = chr(ord(Buffer[3+i]) ^ (cKey ^ (dwSize - i)))
		GS.socket.client.send(Buffer)
		
	def SendConfigToGS(self, GS):
		"""
			Send config to Game Server. Much shorter than in Arye's src!
		"""
		Order = (
					(Packets.MSGID_ITEMCONFIGURATIONCONTENTS, 'Item'),
					(Packets.MSGID_ITEMCONFIGURATIONCONTENTS, 'Item2'),
					(Packets.MSGID_ITEMCONFIGURATIONCONTENTS, 'Item3'),
					(Packets.MSGID_ITEMCONFIGURATIONCONTENTS, 'Item4'),
					(Packets.MSGID_BUILDITEMCONFIGURATIONCONTENTS, 'BuildItem'),
					(Packets.MSGID_DUPITEMIDFILECONTENTS, 'DupItemID'),
					(Packets.MSGID_MAGICCONFIGURATIONCONTENTS, 'Magic'),
					(Packets.MSGID_NOTICEMENTFILECONTENTS, 'noticement'),
					(Packets.MSGID_NPCCONFIGURATIONCONTENTS, 'NPC'),
					(Packets.MSGID_PORTIONCONFIGURATIONCONTENTS, 'Potion'),
					(Packets.MSGID_QUESTCONFIGURATIONCONTENTS, 'Quest'),
					(Packets.MSGID_SKILLCONFIGURATIONCONTENTS, 'Skill'), 
					(Packets.MSGID_ADMINSETTINGSCONFIGURATIONCONTENTS, 'AdminSettings'),
					(Packets.MSGID_SETTINGSCONFIGURATIONCONTENTS, 'Settings')
				)
				
		for packet_id, key in Order:
			if not key in self.Config:
				PutLogList("%s config not loaded!" % key, Logfile.ERROR)
				break
			SendCfgData = struct.pack('Lh', packet_id, 0) + self.Config[key]
			self.SendMsgToGS(GS, SendCfgData)

	def RegisterGameServerSocket(self, sender, data):
		"""
			Here we are adding socket to Game Server
		"""
		GSID = ord(data[0])
		PutLogList("(*) Trying to register socket on GS[%d]." % GSID)
		if not GSID in self.GameServer:
			print "(!) GSID is not registered!"
			return False
		self.GameServer[GSID].GameServerSocket += [sender]
		PutLogList("(*) Registered Socket(%d) GSID(%d) ServerName(%s)" % (len(self.GameServer[GSID].GameServerSocket), GSID, self.GameServer[GSID].Data['ServerName']))
		if len(self.GameServer[GSID].GameServerSocket) == DEF.MAXSOCKETSPERSERVER:
			self.GameServer[GSID].IsRegistered = True
			PutLogList("(*) Gameserver(%s) registered!" % (self.GameServer[GSID].Data['ServerName']))
			PutLogList("")
			
	def GameServerAliveHandler(self, GS, data):
		"""
			Game Server is sending us PING every 3 seconds.
			It contains MsgType (DEF_MSGTYPE_CONFIRM) and Total players connected
			Original Arye's src doesnt handle it very well
			TODO: Disconnecting not responding game servers
		"""
		if len(data)<4:
			PutLogList("GameServerAliveHandler: Size mismatch!")
			return	
		(MsgType, TotalPlayers) = struct.unpack('hh', data[:4])
		if MsgType == Packets.DEF_MSGTYPE_CONFIRM:
			GS.AliveResponseTime = time.time()
			
	def MainSocket_OnConnect(self, sender):
		PutLogList("(*) MainSocket-> Client accepted [%s]" % sender.address)
		
	def MainSocket_OnDisconnected(self, sender):
		PutLogList("(*) MainSocket -> Client disconnected")
		
	def MainSocket_OnListen(self, sender):
		PutLogList("(*) MainSocket -> Server open")
		
	def MainSocket_OnReceive(self, sender, size):
		PutLogList("(*) MainSocket -> Received %d bytes" % size)
		buffer = sender.receive(size)
		try:
			format = '<Bh'
			header_size = struct.calcsize(format)
			if len(buffer) < header_size:
				raise Exception
			s = struct.unpack(format, buffer[:header_size])
			Header = namedtuple('Header', 'cKey dwSize')._make(s)
			buffer = buffer[header_size:]
		except:
			PutLogList("[%s] Except in MainSocket_OnReceive" % sender.address, Logfile.HACK)
			sender.disconnect()
			return
			
		if Header.dwSize != size or size < 4 or Header.dwSize < 4:
			PutLogList("(!) %s Header.dwSize does not match buffer size. Hack!" % sender.address, Logfile.HACK)
			sender.disconnect()
			return

		if Header.cKey > 0:
			Decode = lambda buffer, dwSize, cKey: "".join(map(lambda n: (lambda asdf: chr(asdf & 255))((ord(buffer[n]) ^ (cKey ^ (dwSize - n))) - (n ^ cKey)), range(len(buffer))))
			buffer = Decode(buffer, Header.dwSize-3, Header.cKey)
				
		MsgID = struct.unpack('<L', buffer[:4])[0]
		buffer = buffer[4:]
		
		if MsgID == Packets.MSGID_REQUEST_LOGIN:
			self.ProcessClientLogin(sender, buffer)
		elif MsgID == Packets.MSGID_REQUEST_CHANGEPASSWORD:
			self.ChangePassword(sender, buffer)
		elif MsgID == Packets.MSGID_REQUEST_CREATENEWCHARACTER:
			self.CreateNewCharacter(sender, buffer)
		elif MsgID == Packets.MSGID_REQUEST_DELETECHARACTER:
			self.DeleteCharacter(sender, buffer)
		elif MsgID == Packets.MSGID_REQUEST_CREATENEWACCOUNT:
			self.CreateNewAccount(sender, buffer)
		elif MsgID == Packets.MSGID_REQUEST_ENTERGAME:
			self.ProcessClientRequestEnterGame(sender, buffer)
		else:
			if MsgID in Packets:
				PutLogFileList("MsgID: %s (0x%08X) %db * %s" % (Packets.reverse_lookup_without_mask(MsgID), MsgID, len(buffer), repr(buffer)), Logfile.PACKETMS)
			else:
				PutLogFileList("MsgID: (0x%08X) %db * %s" % (MsgID, len(buffer), repr(buffer)), Logfile.PACKETMS)
			
	def MainSocket_OnClose(self, sender):
		pass
		
	def SendMsgToClient(self, Sock, data, cKey = -1):
		"""
			Sending data to Client
		"""
		dwSize = len(data)+3
		buffer = data[:]
		if cKey == -1:
			cKey = random.randint(0, 255)
		if cKey > 0:
			buffer = map(ord, buffer)#list(data)
			for i in range(len(buffer)):#range(dwSize):
				buffer[i] = buffer[i] + (i ^ cKey)
				buffer[i] = buffer[i] ^ (cKey ^ (len(buffer) - i))
			buffer = "".join(map(lambda x: chr(x & 255) , buffer))
		buffer = chr(cKey) + struct.pack('h', len(buffer)+3) + buffer
		Sock.client.send(buffer)
		
	def ProcessClientLogin(self, sender, buffer):
		"""
			Processing Client Login
			Improvements from Arye's server:
			+ BlockDate is now used properly
			+ Check if client is trying to log on correct WS.
		"""
		try:
			format = '<h10s10s30s'
			format410 = '<h10s10s30sI32s32s32s'
			if len(buffer) == struct.calcsize(format):
				s = map(packet_format, struct.unpack(format, buffer))
				Packet = namedtuple('Packet', 'MsgType AccountName AccountPassword WS')._make(s)
			elif len(buffer) == struct.calcsize(format410):
				s = map(packet_format, struct.unpack(format410, buffer))
				Packet = namedtuple('Packet', 'MsgType AccountName AccountPassword WS Unk1int Unk2str Unk3str Unk4str')._make(s)
				print "(!) %s - %s request login with 4.10 client!" % (sender.address, Packet.AccountName)
			else:
				s = map(packet_format, struct.unpack(format, buffer[:struct.calcsize(format)]))
				Packet = namedtuple('Packet', 'MsgType AccountName AccountPassword WS')._make(s)
		except:
			SendData = struct.pack('<Lh3iB', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_REJECT, 0, 0, 0, 1)
			self.SendMsgToClient(sender, SendData)
			return
			
		if Packet.WS != self.WorldServerName:
			PutLogList("(!) Player tries to enter unknown World Server : %s" % Packet.WS, Logfile.HACK)
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER)
			self.SendMsgToClient(sender, SendData)
			return
			
		OK = self.Database.CheckAccountLogin(Packet.AccountName, Packet.AccountPassword)
		if OK[0] == Account.OK:
			PutLogList("(*) Login success: %s" % Packet.AccountName)
			SendData = struct.pack('<L3hB12s', Packets.MSGID_RESPONSE_LOG, Packets.DEF_MSGTYPE_CONFIRM,
												Version.UPPER, Version.LOWER,
												0, #account status
												'') #dates, converted to 12 * \0x00
			ChLst = self.GetCharList(Packet.AccountName, Packet.AccountPassword)
			SendData += ChLst
			self.SendMsgToClient(sender, SendData)
			
		elif OK[0] == Account.WRONGPASS:
			PutLogList( "(!) Wrong password: Account[ %s ] - Correct Password[ %s ] - Password received[ %s ]" % (Packet.AccountName, OK[2], OK[1]), Logfile.ERROR)
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_PASSWORDMISMATCH)
			self.SendMsgToClient(sender, SendData)
			
		elif OK[0] == Account.NOTEXISTS:
			PutLogList("(!) Account does not exists: %s" % Packet.AccountName, Logfile.ERROR)
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT)
			self.SendMsgToClient(sender, SendData)
			
		elif OK[0] == Account.BLOCKED:
			PutLogList("(!) Account %s blocked until %d-%d-%d and tries to login!" % (Read['AccountName'], OK[1], OK[2], OK[3]), Logfile.ERROR)
			SendData = struct.pack('<Lh3i', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_REJECT, 
												OK[1], OK[2], OK[3], #Y-m-d
												0) #Account Status
			self.SendMsgToClient(sender, SendData)
			
	def ChangePassword(self, sender, buffer):
		global packet_format
		try:
			format = '<h10s10s10s10s'
			if len(buffer) != struct.calcsize(format):
				raise Exception
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType Login Password NewPass1 NewPass2')._make(s)
		except:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			return

		OK = self.Database.CheckAccountLogin(Packet.Login, Packet.Password)
		
		if Packet.NewPass1 != Packet.NewPass2 or len(Packet.NewPass1) < 8 or len(Packet.NewPass2) < 8:
			PutLogList("(!) Password changed on account %s (%s -> %s) FAIL! (Password confirmation)" % (Packet.Login, Packet.Password, Packet.NewPass1))
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_CHANGEPASSWORD, Packets.DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL)
			self.SendMsgToClient(sender, SendData)
			return
			
		if OK[0] == Account.WRONGPASS:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_CHANGEPASSWORD, Packets.DEF_LOGRESMSGTYPE_PASSWORDMISMATCH)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Password changed on account %s (%s -> %s) FAIL! (Password mismatch)" % (Packet.Login, Packet.Password, Packet.NewPass1))
			return
			
		if OK[0] != Account.OK:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_CHANGEPASSWORD, Packets.DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Password changed on account %s (%s -> %s) FAIL! (%s)" % (Packet.Login, Packet.Password, Packet.NewPass1, Account.reverse_lookup_without_mask(OK[0])))
			return
			
		if self.Database.ChangePassword(Packet.Login, Packet.Password, Packet.NewPass1):
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_CHANGEPASSWORD, Packets.DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(*) Password changed on account %s (%s -> %s) SUCCESS!" % (Packet.Login, Packet.Password, Packet.NewPass1))
		else:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_CHANGEPASSWORD, Packets.DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Password changed on account %s (%s -> %s) FAIL! (Database failed)" % (Packet.Login, Packet.Password, Packet.NewPass1))
	
	def CreateNewCharacter(self, sender, buffer):
		global packet_format
		try:
			format = '<h10s10s10s30s11B'
			if len(buffer) != struct.calcsize(format):
				raise Exception
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType PlayerName AccountName AccountPassword WS Gender SkinCol HairStyle HairCol UnderCol Str Vit Dex Int Mag Agi')._make(s)
		except:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			return
			
		OK = self.Database.CheckAccountLogin(Packet.AccountName, Packet.AccountPassword)
		if OK[0] != Account.OK or Packet.PlayerName == "" or Packet.WS != self.WorldServerName:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Wrong account data on creating new character!", Logfile.HACK)
			return
			
		if self.Database.CharacterExists(Packet.PlayerName):
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_ALREADYEXISTINGCHARACTER)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Character %s already exists." % Packet.PlayerName, Logfile.HACK)
			return
			
		CharList = self.Database.GetAccountCharacterList(Packet.AccountName, Packet.AccountPassword)
		Stat = [getattr(Packet, x) for x in ['Str','Vit','Dex','Int','Mag','Agi']]
		print Stat
		if filter(lambda x: x not in [10,11,12,13,14], Stat) < 6: #test if requested Stats are not in valid values
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Stat values not in [10, 11, 12, 13, 14]", Logfile.HACK)
			return
		
		if reduce(lambda a,b: a+b, Stat) != 70: #if stats count does not compare 70
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Stat values %d/70!" % (reduce(lambda a,b: a+b, Stat)), Logfile.HACK)
			return
			
		if len(CharList) > 4: #more than 4 chars?
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Account %s tries make to more than 4 characters!" % Packet.AccountName, Logfile.HACK)
			return
		
		if not self.Database.CreateNewCharacter(Packet):
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create new character -> Create new character failed at CreateNewCharacter!", Logfile.HACK)
		else:
			SendData = struct.pack('<Lh10s',Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED,
											Packet.PlayerName)
			SendData += self.GetCharList(Packet.AccountName, Packet.AccountPassword)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(*) Create new character -> Create new character success on account %s [CharName: %s ]!" % (Packet.AccountName, Packet.PlayerName))

	def GetCharList(self, account_name, account_password):
		global fillzeros
		CharList = self.Database.GetAccountCharacterList(account_name, account_password)
		Buffer = chr(len(CharList))		
		for Char in CharList:
			Tmp = struct.pack('<10sB6h2i6h12s10s',
							Char['char_name'],
							1, #wtf?
							Char['Appr1'], Char['Appr2'], Char['Appr3'], Char['Appr4'],
							Char['Gender'],
							Char['Skin'],
							Char['Level'],
							Char['Exp'],
							Char['Strength'], Char['Vitality'], Char['Dexterity'], Char['Intelligence'], Char['Magic'], Char['Agility'],
							"", #will be converted to 12 * \0x00 -> Logout date
							Char['MapLoc'])
			Buffer += Tmp
		return Buffer
		
	def DeleteCharacter(self, sender, buffer):
		global packet_format
		try:
			format = '<h10s10s10s30s'
			if len(buffer) != struct.calcsize(format):
				raise Exception
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType CharName AccountName AccountPassword WS')._make(s)
		except:
			SendData = struct.pack('Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER)
			self.SendMsgToClient(sender, SendData)
			return
			
		if Packet.WS != self.WorldServerName or not self.Database.DeleteCharacter(Packet.AccountName, Packet.AccountPassword, Packet.CharName):
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER)
			self.SendMsgToClient(sender, SendData)
			return
		PutLogList("Character deleted success! [ %s ] Account[%s]" % (Packet.CharName, Packet.AccountName))
		SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_CHARACTERDELETED, 1)
		SendData += self.GetCharList(Packet.AccountName, Packet.AccountPassword)
		self.SendMsgToClient(sender, SendData)
		
	def CreateNewAccount(self, sender, buffer):
		global nozeros
		global packet_format
		try:
			format = '<h10s10s50s10s10si2h17s28s45s20s50s'
			if len(buffer) != struct.calcsize(format):
				raise Exception
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType AccountName AccountPassword Mail Gender AccountAge Unk1 Unk2 Unk3 AccountCountry AccountSSN AccountQuiz AccountAnswer CmdLine')._make(s)
		except:
			print "Exception CreateNewAccount CLoginServer"
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED)
			self.SendMsgToClient(sender, SendData)
			return
		
		OK = self.Database.CreateNewAccount(Packet.AccountName, Packet.AccountPassword, Packet.Mail, Packet.AccountQuiz, Packet.AccountAnswer, sender.address)
		if OK == Account.OK:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(*) Create account success [ %s/%s ]." % (Packet.AccountName, Packet.Mail))
		elif OK == Account.FAIL:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create account fails [ %s ]. Unknown error occured!" % Packet.AccountName, Logfile.HACK)
		elif OK == Account.EXISTS:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_LOG, Packets.DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT)
			self.SendMsgToClient(sender, SendData)
			PutLogList("(!) Create account fails [ %s ]. Account already exists" % Packet.AccountName, Logfile.HACK)

	def ProcessClientRequestEnterGame(self, sender, buffer):
		try:
			global packet_format
			format = '<h10s10s10s10si30s120s'
			if len(buffer) != struct.calcsize(format):
				raise Exception
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType PlayerName MapName AccountName AccountPassword Level WS CmdLine')._make(s)
		except:
			SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_DATADIFFERENCE)
			self.SendMsgToClient(sender, SendData)
			return

		if Packet.WS != self.WorldServerName:
			PutLogList("(!) Player tries to enter game with unknown World Server : %s" % Packet.WS)
			SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_DATADIFFERENCE)
			self.SendMsgToClient(sender, SendData)
			return
			
		OK = self.Database.CheckAccountLogin(Packet.AccountName, Packet.AccountPassword)
		if OK[0] != Account.OK:
			SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_DATADIFFERENCE)
			self.SendMsgToClient(sender, SendData)
			return
		
		Ch = self.Database.GetAccountCharacterList(Packet.AccountName, Packet.AccountPassword)
		Found = False
		for C in Ch:
			if C['char_name'] == Packet.PlayerName:
				Found = True
		
		if Found:

			GS = self.IsMapAvailable(Packet.MapName)
			(InUse, ID) = self.IsAccountInUse(Packet.AccountName)

			if Packet.MsgType == Packets.DEF_ENTERGAMEMSGTYPE_NEW:
				if GS == False or self.GameServer[GS['GSID']].IsRegistered == False:
					PutLogList("(!) Player %s is stuck at %s !" % (Packet.PlayerName, Packet.MapName))
					SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_GAMESERVERNOTONLINE)
				else:
					if InUse:
						SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_PLAYING)
					else:
						self.Clients += [{
										'AccountName': Packet.AccountName,
										'AccountPassword': Packet.AccountPassword,
										'CharName': Packet.PlayerName,
										'Level': Packet.Level,
										'ClientIP': sender.address,
										'ID': GS['GSID'],
										'IsPlaying': False,
										'Time': None,
										'IsOnServerChange': False,
										'ForceDisconnRequestTime': None}]
						
						SendData = struct.pack('<Lh16sh20s', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_CONFIRM, 
																GS['IP'], GS['Port'],
																"") #ServerName?
						PutLogList("(*) Client enter game : %s" % Packet.PlayerName)
				self.SendMsgToClient(sender, SendData)

			elif Packet.MsgType == Packets.DEF_ENTERGAMEMSGTYPE_NOENTER_FORCEDISCONN:
					if InUse and Packet.AccountName == self.Clients[ID]['AccountName'] and Packet.AccountPassword == self.Clients[ID]['AccountPassword'] and self.Clients[ID]['IsPlaying'] == True:
						if GS != False:
							self.RequestForceDisconnect(self.GameServer[self.Clients[ID]['ID']], ID, 10)
							PutLogList("(*) Client force logout: %s" % Packet.PlayerName)
						else:
							self.Clients.remove(self.Clients[ID])
						SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_FORCEDISCONN)
						self.SendMsgToClient(sender, SendData)
					else:
						#SAFEDELETE(ClientSocket[ClientID]);
						print "TODO: DEF_ENTERGAMEMSGTYPE_NOENTER_FORCEDISCONN delete ClientSocket[] (?)"

			elif Packet.MsgType == Packets.DEF_ENTERGAMEMSGTYPE_CHANGINGSERVER:
				# Removed ip check - Aryes made request here to getpeeraddress and compare with self.clients
				if InUse and Packet.AccountName == self.Clients[ID]['AccountName'] and Packet.AccountPassword == self.Clients[ID]['AccountPassword'] and Packet.PlayerName == self.Clients[ID]['CharName'] and self.Clients[ID]['IsOnServerChange'] == True:
					if GS != False:
						self.Clients[ID]['ID'] = GS['GSID']
						self.Clients[ID]['Time'] = time.localtime()
						self.Clients[ID]['IsOnServerChange'] = False
						self.Clients[ID]['IsPlaying'] = True
						SendData = struct.pack('<Lh16sh20s', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_CONFIRM, GS['IP'], GS['Port'], "")
						PutLogList("(*) Client change server : %s" % Packet.PlayerName)
					else:
						SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_GAMESERVERNOTONLINE)
						self.Clients.remove(self.Clients[ID])
					self.SendMsgToClient(sender, SendData)
				else:
					#SAFEDELETE(ClientSocket[ClientID]);
					print "TODO: DEF_ENTERGAMEMSGTYPE_CHANGINGSERVER delete ClientSocket[] (?)"

			else:
				#SAFEDELETE(ClientSocket[ClientID]);
				print "TODO: Unknown ProcessClientRequestEnterGame message type - delete ClientSocket[] (?)"
		else:
			SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_DATADIFFERENCE)
			self.SendMsgToClient(sender, SendData)
			
	def IsMapAvailable(self, MapName):
		for GS in self.GameServer.values():
			if not GS.IsRegistered:
				return False
			if MapName in GS.MapName:
				return {'IP':GS.Data['ServerIP'], 'Port': GS.Data['ServerPort'], 'GSID': GS.GSID}
		return False
		
	def IsAccountInUse(self, AccountName):
		for C in self.Clients:
			if C['AccountName'] == AccountName:
				return True
		return False

	def ProcessRequestPlayerData(self, sender, buffer, GS):
		try:
			global packet_format
			format = '<h10s10s10s15sB'
			if len(buffer) != struct.calcsize(format):
				print "(!) RequestPlayerData size mismatch!"
				raise Exception				
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType CharName AccountName AccountPassword Address AccountStatus')._make(s)
		except:
			SendData = SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_PLAYERDATA, Packets.DEF_LOGRESMSGTYPE_REJECT, "")
			self.SendMsgToGS(GS, SendData)
			return
		
		Found = False
		CharInfoSize = None
		(InUse, ID) = self.IsAccountInUse(Packet.AccountName)
		Client = self.Clients[ID]
		if InUse:
			if Client['CharName'] != Packet.CharName or Client['AccountName'] != Packet.AccountName or Client['AccountPassword'] != Packet.AccountPassword:
				PutLogList("(!) Wrong data: Account[%s/%s] CharName[%s/%s] IP[%s/%s]" % (
								Packet.AccountName,
								Client['AccountName'],
								Packet.AccountPassword,
								Client['AccountPassword'],
								Packet.CharName,
								Client['CharName']), Logfile.HACK)
			elif Client['ClientIP'] != "127.0.0.1" and Client['ClientIP'] != Packet.Address:
				PutLogList("(!) IP mismatch: Account(%s) IP[%s/%s]" % (
								Packet.AccountName,
								Packet.Address,
								Client['ClientIP']), Logfile.HACK)
			else:
				CharInfoSize = self.GetCharacterInfo(Packet.AccountName, Packet.AccountPassword, Packet.CharName)
				if len(CharInfoSize) != 0:
					self.Clients[ID]['IsOnServerChange'] = False;
					Found = True
		if not Found:
			# Sending this message to Aryes HGServer causes HG crash - That Needs fix
			PutLogList("(!) HG server is requesting not logged player! HACK!", Logfile.HACK)
			SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_PLAYERDATA, Packets.DEF_LOGRESMSGTYPE_REJECT, Packet.CharName)
			self.SendMsgToGS(GS, SendData)
			self.Clients.remove(self.Clients[ID])
		else:
			SendData = struct.pack('<Lh', Packets.MSGID_RESPONSE_PLAYERDATA, Packets.DEF_LOGRESMSGTYPE_CONFIRM)
			SendData += CharInfoSize
			self.SendMsgToGS(GS, SendData)

	def GetCharacterInfo(self, AccountName, AccountPassword, CharName):
		OK = self.Database.GetCharacter(AccountName, AccountPassword, CharName)
		if OK == False:
			"OK == False"
			return
		Ch = OK['Content']
		
		Data = struct.pack('<10s2b10s2h5B20sbih7Bi100s',
									CharName,
									0, #Account Status - outdated
									Ch['GuildID'], #Guild Status - outdated
									Ch['MapLoc'],
									Ch['LocX'], Ch['LocY'],
									Ch['Gender'],
									Ch['Skin'],
									Ch['HairStyle'],
									Ch['HairColor'],
									Ch['Underwear'],
									Ch['GuildName'],
									Ch['GuildRank'],
									Ch['HP'],
									Ch['Level'],
									Ch['Strength'],
									Ch['Vitality'],
									Ch['Dexterity'],
									Ch['Intelligence'],
									Ch['Magic'],
									Ch['Agility'],
									Ch['Luck'],
									Ch['Exp'],
									Ch['MagicMastery'])
		
		for each in OK['Skill']:
			for key, value in each.iteritems():
				if key == "SkillMastery":
					Data += struct.pack('B', value)
					
		Data += struct.pack('<10s2iB3i', 
									Ch['Nation'],
									Ch['MP'],
									Ch['SP'],
									0, # LU-pool - outdated
									Ch['EK'],
									Ch['PK'],
									Ch['RewardGold'])
		
		for each in OK['Skill']:
			for key, value in each.iteritems():
				if key == "SkillSSN":
					Data += struct.pack('i', value)
		
		Data += struct.pack('<4x2B4iB4i20s3h3iB3ihBiB2i10siB4ihB', #4x = 4 byte padding
									Ch['Hunger'],
									Ch['AdminLevel'],
									Ch['LeftShutupTime'],
									Ch['LeftPopTime'],
									Ch['Popularity'],
									Ch['GuildID'], # changed to I (unsigned int) previously h (short)-
									Ch['DownSkillID'] & 255,
									Ch['CharID'],
									Ch['ID1'],
									Ch['ID2'],
									Ch['ID3'],
									str(Ch['BlockDate']) if Ch['BlockDate'] != None else "0000-00-00 00:00:00",
									Ch['QuestNum'],
									Ch['QuestCount'],
									Ch['QuestRewType'],
									Ch['QuestRewAmmount'],
									Ch['Contribution'],
									Ch['QuestID'],
									Ch['QuestCompleted'],
									Ch['LeftForceRecallTime'],
									Ch['LeftFirmStaminarTime'],
									Ch['EventID'],
									Ch['LeftSAC'],
									Ch['FightNum'],
									Ch['FightDate'],
									Ch['FightTicket'],
									Ch['LeftSpecTime'],
									Ch['WarCon'],
									Ch['LockMapName'],
									Ch['LockMapTime'],
									Ch['CruJob'],
									Ch['CruConstructPoint'],
									Ch['CruID'],
									Ch['LeftDeadPenaltyTime'],
									Ch['PartyID'],
									Ch['GizonItemUpgradeLeft'],
									len(OK['Item']))
		
		for each in OK['Item']:
			Data += struct.pack('<20sih3iB4hiB2hi',
									each['ItemName'],
									each['Count'],
									each['ItemType'],
									each['ID1'],
									each['ID2'],
									each['ID3'],
									each['Color'],
									each['Effect1'],
									each['Effect2'],
									each['Effect3'],
									each['LifeSpan'],
									each['Attribute'],
									each['ItemEquip'],
									each['ItemPosX'],
									each['ItemPosY'],
									each['ItemID'])
									
		Data += struct.pack('<xB', len(OK['Bank'])) #Padding (1 byte), Bank items count
		for each in OK['Bank']:
			Data += struct.pack('<20sih3iB4h2i', 
									each['ItemName'],
									each['Count'],
									each['ItemType'],
									each['ID1'],
									each['ID2'],
									each['ID3'],
									each['Color'],
									each['Effect1'],
									each['Effect2'],
									each['Effect3'],
									each['LifeSpan'],
									each['Attribute'],
									each['ItemID'])

		Data += struct.pack('<10s', Ch['Profile'])
		return Data
		
	def ServerStockMsgHandler(self, GS, buffer):
		"""
			Write rest of GSM's (only GSM_DISCONNECT now)
		"""
		buffer = buffer[2:]
		global packet_format
		while len(buffer)>0:
			ID = ord(buffer[0])
			buffer = buffer[1:]
			if ID == Packets.GSM_DISCONNECT:
				s=map(packet_format, struct.unpack('<10s', buffer[:10]))
				buffer=buffer[10:]
				Packet = namedtuple('Packet', 'PlayerName')._make(s)
				ok = False
				for i in self.Clients:
					if i['CharName'] == Packet.PlayerName:
						self.Clients[self.Clients.index(i)]['IsPlaying'] = False
						#self.Clients.remove(i) - do not delete client here! - sloppy disconnect code in aryes loginserv
						ok = True
				if not ok:
					PutLogList("(!!!) Unknown player disconnected [%s] !" % Packet.PlayerName)
				else:
					PutLogList("(!!!) Character[%s] disconnected from game server [ %s ]." % (Packet.PlayerName, GS.Data['ServerName']))
					
			elif ID == Packets.GSM_REQUEST_FINDCHARACTER:
				SendBuffer = buffer[:25]
				buffer = buffer[25:]
				InternalID = ord(SendBuffer[-1])
				PutLogList("(***) GSM_REQUEST_FINDCHARACTER InternalID=%d" % (InternalID))
				SendData=struct.pack('<Lh25s', MSGID_SERVERSTOCKMSG, DEF_MSGTYPE_CONFIRM, buffer)
				ok = False
				for i in self.GameServer.keys():
					if i == InternalID:
						self.SendMsgToGS(self.GameServer[i], SendData)
						ok = True
				if not ok:
					print "NOT OK."

	def SavePlayerData(self, buffer, GS):
		global packet_format
		fmt = "<h10s10s10s"
		s=map(packet_format, struct.unpack(fmt, buffer[:struct.calcsize(fmt)]))
		Header = namedtuple("Header", "MsgType CharName AccountName AccountPassword")._make(s)
		buffer = buffer[struct.calcsize(fmt)+1:]
		Data = self.DecodeSavePlayerDataContents(buffer)
		if self.Database.SavePlayerContents(Header.CharName, Header.AccountName, Header.AccountPassword, Data):
			PutLogList("(!) Player [ %s ] data contents saved !" % Header.CharName)
		else:
			PutLogList("(!!!) Player [ %s ] data contents not saved !" % Header.CharName)

	def DecodeSavePlayerDataContents(self, buffer):
		global packet_format
		Values = "wYear wMonth wDay wHour wMinute wSecond m_cLocation m_cMapName " + \
								"m_sX m_sY m_cGuildName m_iGuildGuid m_cGuildRank " + \
								"m_iHP m_iMP m_iSP m_iLevel m_iRating m_iStr m_iVit " + \
								"m_iDex m_iInt m_iMag m_iAgi m_iLuck m_iExp m_iEnemyKillCount " + \
								"m_iPKCount m_iRewardGold m_iDownSkillIndex m_sCharIDnum1 " + \
								"m_sCharIDnum2 m_sCharIDnum3 m_cSex m_cSkin m_cHairStyle m_cHairColor " + \
								"m_cUnderwear m_iHungerStatus m_iTimeLeft_ShutUp m_iTimeLeft_Rating " + \
								"m_iTimeLeft_ForceRecall m_iTimeLeft_FirmStaminar m_iAdminUserLevel m_iBlockDate " + \
								"m_iQuest m_iQuestID m_iCurQuestCount m_iQuestRewardType m_iQuestRewardAmount " + \
								"m_iContribution m_iWarContribution m_bIsQuestCompleted m_iSpecialEventID " + \
								"m_iSuperAttackLeft m_iFightzoneNumber m_iReserveTime m_iFightZoneTicketNumber " + \
								"m_iSpecialAbilityTime m_cLockedMapName m_iLockedMapTime " + \
								"m_iCrusadeDuty m_dwCrusadeGUID m_iConstructionPoint m_iDeadPenaltyTime " + \
								"m_iPartyID m_iGizonItemUpgradeLeft m_iSpecialAbilityTime2 " + \
								"m_sAppr1 m_sAppr2 m_sAppr3 m_sAppr4 m_iApprColor MagicMastery"
								
		format = "<h5B10s10s2h20s2h3ihi7B4ib3i6B4iB20s4h3iBihBiBi10siB4ih6i100s"
		SkillsFormat = "<24B24I"
		ContentSize = struct.calcsize(format)
		SkillsSize = struct.calcsize(SkillsFormat)
		p = map(packet_format, struct.unpack(format, buffer[:ContentSize])) #Decode player contents + add profile
		Content = namedtuple('Content', Values)._make(p) #Make named structure with player contents
		Skills = struct.unpack(SkillsFormat,buffer[ContentSize:ContentSize + SkillsSize]) #Skills [24*Skill%, 24*SkillSSN]
		Index = ContentSize + SkillsSize + 4
		NItems = ord(buffer[Index])
		Items = []
		if NItems > 0:
				for I in range(NItems):
						IndexForItem = (471 + (I*60))
						fmt = "<20sih3iB4hiB2hI"
						Item = map(packet_format, struct.unpack(fmt, buffer[IndexForItem:IndexForItem + struct.calcsize(fmt)]))
						Item = namedtuple('Item', "m_cName m_dwCount m_sTouchEffectType m_sTouchEffectValue1 m_sTouchEffectValue2 m_sTouchEffectValue3 m_cItemColor m_sItemSpecEffectValue1 m_sItemSpecEffectValue2 m_sItemSpecEffectValue3 m_wCurLifeSpan m_dwAttribute m_bIsItemEquipped X Y ItemUniqueID")._make(Item)
						Items += [Item]

		Index = 471+(NItems*60)
		NBankItems = ord(buffer[Index])
		BankItems = []
		if NBankItems > 0:
				for I in range(NBankItems):
						IndexForItem = (Index+1+(I*55))
						fmt = "<20sih3ib4h2i"
						Item = map(packet_format, struct.unpack(fmt, buffer[IndexForItem:IndexForItem + 55]))
						Item = namedtuple('Item', 'm_cName m_dwCount m_sTouchEffectType m_sTouchEffectValue1 m_sTouchEffectValue2 m_sTouchEffectValue3 m_cItemColor m_sItemSpecEffectValue1 m_sItemSpecEffectValue2 m_sItemSpecEffectValue3 m_wCurLifeSpan m_dwAttribute ItemUniqueID')._make(Item)
						BankItems += [Item]
					   
		Index += (NBankItems*55)+1
		return {'Player': Content, 'Items': Items, 'BankItems': BankItems, 'Skills': Skills, 'Profile': buffer[Index:]}
		
	def IsAccountInUse(self, AccName):
		for i in range(len(self.Clients)):
			if self.Clients[i]['AccountName'] == AccName:
				return (True, i)
		return (False, -1)
		
	def EnterGameConfirm(self, buffer, GS):
		try:
			global packet_format
			format = '<h10s10s10s16si'
			if len(buffer) != struct.calcsize(format):
				raise Exception				
			s = map(packet_format, struct.unpack(format, buffer))
			Packet = namedtuple('Packet', 'MsgType AccountName AccountPassword ServerName IP Level')._make(s)
		except:
			#TODO: Force logout player ?
			return
			
		ok = False
		GSID = -1
		for id in self.GameServer:
			if self.GameServer[id].Data['ServerName'] == Packet.ServerName:
				ok = True
				GSID = id
				
		if not ok:
			PutLogList("(!) Wrong data: Game server ID: [ %s ] ClientIP[ %s ] not found!" % (Packet.ServerName, Packet.IP), Logfile.HACK)
			return
		
		(InUse, ID) = self.IsAccountInUse(Packet.AccountName)
		
		if InUse:
			Client = self.Clients[ID]
			if Client['Level'] == Packet.Level and Client['AccountName'] == Packet.AccountName:
				if Client['AccountPassword'] != Packet.AccountPassword or Client['Level'] != Packet.Level:
					PutLogList("(!!!) Wrong data: Account(%s) pwd[%s/%s] Level[%d/%d] IP[%s/%s] Char[%s] GSID[%d/%d]" % (
									Packet.AccountName,
									Packet.AccountPassword,
									Client['AccountPassword'],
									Packet.Level,
									Client['Level'],
									Client['CharName'],
									Packet.IP,
									Client['ClientIP'],
									GSID,
									Client['ID']), Logfile.HACK)
					self.RequestForceDisconnect(GS, ID, 10)
					return #REJECT
				if Client['ClientIP'] != "127.0.0.1" and Packet.IP != Client['ClientIP']:
					PutLogList("(!!!) Client IP mismatch: Account(%s) IP[%s/%s]" % (
									Packet.AccountName,
									Packet.IP,
									Client['ClientIP']), Logfile.HACK)
					self.RequestForceDisconnect(GS, ID, 10)
					return #REJECT

				# Need to add mapname in Packet to do a check if player is entering active zone
				"""
				changeGS = self.IsMapAvailable(Packet.MapName)
				if changeGS == False or self.GameServer[changeGS['GSID']].IsRegistered == False:
					PutLogList("(!) Player %s is stuck at %s !" % (Packet.PlayerName, Packet.MapName))
					SendData = struct.pack('<LhB', Packets.MSGID_RESPONSE_ENTERGAME, Packets.DEF_ENTERGAMERESTYPE_REJECT, Packets.DEF_REJECTTYPE_GAMESERVERNOTONLINE)
					self.SendMsgToClient(sender, SendData)
				else:
				"""
				self.Clients[ID]['IsPlaying'] = True
				self.Clients[ID]['Time'] = time.localtime()
				PutLogList("(*) Set character(%s) Account[%s] status: playing." % (Client['CharName'], Client['AccountName']))
			else:
				PutLogList("Unknown data 1", Logfile.HACK)
				print Packet
		else:
			PutLogList("Unknown data 2", Logfile.HACK)
			print Packet

	def ProcessClientLogout(self, buffer, GS, bSave):
		global packet_format
		try:
			fmt = "<h10s10s10sc"
			s=map(packet_format, struct.unpack(fmt, buffer[:struct.calcsize(fmt)]))
			Packet = namedtuple('Packet', 'MsgType PlayerName AccountName AccountPassword CountLogout')._make(s)
			buffer = buffer[struct.calcsize(fmt):]
		except:
			PutLogFileList("(!) [GameServer IP: %s] Unable to save player data. Packet mismatch!" % GS.socket.address, Logfile.HACK)
			return
		(InUse, ID) = self.IsAccountInUse(Packet.AccountName)
		if InUse:
			Client = self.Clients[ID]
			if Client['AccountPassword'] == Packet.AccountPassword and Client['AccountName'] == Packet.AccountName and Client['CharName'] == Packet.PlayerName:
				if bSave:
					Data = self.DecodeSavePlayerDataContents(buffer)
					if self.Database.SavePlayerContents(Packet.PlayerName, Packet.AccountName, Packet.AccountPassword, Data):
						PutLogList("(*) Player [ %s ] Account [ %s ] data saved properly." % (Packet.PlayerName, Packet.AccountName))
					else:
						PutLogList("(!) Player [ %s ] data contents not saved !" % Packet.PlayerName)
				else:
					PutLogList("(*) Player [ %s ] Account [ %s ] logout with no save." % (Packet.PlayerName, Packet.AccountName))

				if Packet.CountLogout:
					self.Clients.remove(self.Clients[ID])
				else:
					self.Clients[ID]['IsOnServerChange'] = True
					self.Clients[ID]['Time'] = time.localtime()
					SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_SAVEPLAYERDATA_REPLY, 0, Packet.PlayerName)
					self.SendMsgToGS(GS, SendData)
			else:
				PutLogList("(!) Server change data-error for Character[ %s ]" % Packet.PlayerName, Logfile.HACK)
				PutLogList("(!) Wrong data: Character[ %s/%s ] AcctName[ %s/%s ] AcctPwd[ %s/%s ]" % (
								Packet.PlayerName,
								Client['CharName'],
								Packet.AccountName,
								Client['AccountName'],
								Packet.AccountPassword,
								Client['AccountPassword']), Logfile.HACK)
		else:
			PutLogList("(!) Server change data-error for Character[ %s ] - Account not in use!" % Packet.PlayerName, Logfile.HACK)
			
	def RequestForceDisconnect(self, GS, ID, Count):
		Client = self.Clients[ID]
		if Client == None:
			return
		if self.GameServer[Client['ID']] == None:
			self.Clients[ID]['ForceDisconnRequestTime'] = time.localtime()
			return
		SendData = struct.pack('Lh10s', Packets.MSGID_REQUEST_FORCEDISCONECTACCOUNT, Count, Client['AccountName'])
		self.SendMsgToGS(GS, SendData)
		if (Client['ForceDisconnRequestTime'] == 0):
			self.Clients[ID]['ForceDisconnRequestTime'] = time.localtime()

	def SendUpdatedConfigToAllServers(self):
		PutLogList("(*) Updating configuration files...")
		if not self.bReadAllConfig():
			PutLogList("(!) Could not read configuration files!")
		else:
			PutLogList("(*) Sending updated configuration files to all servers...")
			SendData = struct.pack('L', Packets.MSGID_UPDATECONFIGFILES)
			for i in self.GameServer:
				self.SendMsgToGS(self.GameServer[i], SendData)
				self.SendConfigToGS(self.GameServer[i])
			PutLogList("(*) All server configs are updated!")

	def SetAccountServerChangeStatus(self, buffer, bIsOnServerChange):
		global packet_format
		try:
			fmt = "<h10s"
			if len(buffer) != struct.calcsize(fmt):
				raise Exception
			s = map(packet_format, struct.unpack(fmt, buffer))
			Packet = namedtuple('Packet', 'MsgType AccountName')._make(s)
		except:
			return
		(InUse, ID) = self.IsAccountInUse(Packet.AccountName)
		if InUse:
			self.Clients[ID]['IsOnServerChange'] = bIsOnServerChange
			
	def ProcessShutdown(self):
		PutLogList("(!) Server shutdown process started...")
		self.ServerShutdownCount = 0
		self.Timers.register_timer(self.__shutdown_timer, 'shutdown_timer', 10.0, True)

	def __shutdown_timer(self):
		self.ServerShutdownCount += 1
		if self.ServerShutdownCount < 6:
			SendData = struct.pack('<Lhh', Packets.MSGID_SENDSERVERSHUTDOWNMSG, 0, 1)
			PutLogList("(!) Sending server shutdown announcement - %d!" % self.ServerShutdownCount)
		else:
			SendData = struct.pack('L', Packets.MSGID_GAMESERVERSHUTDOWNED)
			PutLogList("(!) Shutting down all the servers!")
			
		for i in self.GameServer:
			if self.GameServer[i].IsRegistered:
				self.SendMsgToGS(self.GameServer[i], SendData)
				
		if self.ServerShutdownCount == 6:
			return False
		return True
		
	def __gameserver_alive(self):
		print "Total servers connected: %d" % (len(self.GameServer.values()))
		for v in self.GameServer.values():
			if v.AliveResponseTime - time.time() > 10000:
				PutLogList("(*) Game Server : %s@%s:%d (%d maps) is not responding!" % (v.Data['ServerName'], v.Data['ServerIP'], v.Data['ServerPort'], len(v.MapName)))
				for SL in v.GameServerSocket:
					SL.disconnect()
				v.socket.disconnect()
				self.GameServer.remove(v)

	def GuildHandler(self, MsgID, buffer, GS):
		MsgType = struct.unpack('h', buffer[:2])
		buffer = buffer[2:]
		
		global packet_format
		Packet = None
		if MsgID == Packets.MSGID_REQUEST_CREATENEWGUILD:
			fmt = '<10s10s10s20s10s5x' #HG makes 60b packet, but I get 65. wtf?
			Data = map(packet_format, struct.unpack(fmt, buffer))
			Packet = namedtuple('Packet', 'CharName AccountName AccountPassword GuildName GuildLoc')._make(Data)
			(OK, GUID) = self.Database.CreateNewGuild(*Data)
			print (OK, GUID)
			if OK:
				SendData = struct.pack('<Lh10sI', Packets.MSGID_RESPONSE_CREATENEWGUILD, Packets.DEF_LOGRESMSGTYPE_CONFIRM, Packet.CharName, GUID)
			else:
				SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_CREATENEWGUILD, Packets.DEF_LOGRESMSGTYPE_REJECT, Packet.CharName)
			self.SendMsgToGS(GS, SendData)
			
		elif MsgID == Packets.MSGID_REQUEST_DISBANDGUILD:
			fmt = '<10s10s10s20s'
			Data = map(packet_format, struct.unpack(fmt, buffer[:struct.calcsize(fmt)]))
			Packet = namedtuple('Packet', 'CharName AccountName AccountPassword GuildName')._make(Data)
			if self.Database.DisbandGuild(*Data):
				SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_DISBANDGUILD, Packets.DEF_LOGRESMSGTYPE_CONFIRM, Packet.CharName)
			else:
				SendData = struct.pack('<Lh10s', Packets.MSGID_RESPONSE_DISBANDGUILD, Packets.DEF_LOGRESMSGTYPE_REJECT, Packet.CharName)
			self.SendMsgToGS(GS, SendData)
			
		if Packet != None:
			print Packet
