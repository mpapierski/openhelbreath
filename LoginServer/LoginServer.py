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

import socket, os, sys, select, struct, time, re
from Enum import Enum
from threading import Thread, Semaphore, Event
from NetMessages import Packets
from GlobalDef import DEF
from Helpers import Callbacks
from Sockets import ServerSocket

class CGameServer(object):
	def __init__(self, clientsocket):
		self.AliveResponseTime = time.time()
		self.socket = clientsocket
		self.MapName = []
		self.GameServerSocket = []
		self.Data = {}
		self.Config = {}

class CLoginServer(object):
	def __init__(self):
		self.MainSocket = None
		self.GateServerSocket = None
		self.ListenAddress = ""
		self.GateServerPort = 0
		self.ListenToAllAddresses = True
		self.PermittedAddress = []
		
	def DoInitialSetup(self):
		if not self.ReadProgramConfigFile("LoginServer/LServer.cfg"):
			return False
		print "(!) Connecting to mySql database..."
		print "-Connection to mySQL database was sucessfully established!"
		return True
		
	def GateServer_OnConnect(self, sender):
		print "(*) GateServer -> Accepted connection"
		
	def GateServer_OnDisconnected(self, sender):
		print "(*) GateServer -> Lost connection"
		
	def GateServer_OnListen(self, sender):
		print "(*) GateServer -> Server open"
		
	def GateServer_OnReceive(self, sender, size):
		print "(*) GateServer -> Received %d bytes" % size
		
	def GateServer_OnClose(self, sender, size):
		print "(*) GateServer -> Server close"
		
	def InitServer(self):
		if not self.bReadAllConfig():
			return False
		print "(!) Done!"
		GateServerCB = {'onConnected': self.GateServer_OnConnect,
						'onDisconnected': self.GateServer_OnDisconnected,
						'onListen': self.GateServer_OnListen,
						'onReceive': self.GateServer_OnReceive,
						'onClose': self.GateServer_OnClose}
		self.GateServerSocket = ServerSocket((self.ListenAddress, self.GateServerPort), GateServerCB)
		if self.ListenToAllAddresses:
			print "(!) permitted-address line not found on config., server will be listening to all IPs!"
		self.GateServerSocket.start()
		print "-Login server sucessfully started!"
		return True
		
	def bReadAllConfig(self):
		Files = ["Item.cfg", "Item2.cfg", "Item3.cfg", "BuildItem.cfg",
				"DupItemID.cfg", "Magic.cfg", "noticement.txt", 
				"NPC.cfg", "Potion.cfg", "Quest.cfg", "Skill.cfg",
				"AdminSettings.cfg", "Settings.cfg"]
		self.Config = {}
		for n in Files:
			if not self.ReadConfig("LoginServer/Config/%s" % n):
				return False
		return True
		
	def ReadProgramConfigFile(self, cFn):
		if not os.path.exists(cFn) and not os.path.isfile(cFn):
			print "(!) Cannot open configuration file."
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
					print "(*) Login server address : %s" % (self.ListenAddress)
					
				if token[0] == "login-server-port":
					self.ListenPort = token[1]
					print "(*) Login server port : %d" % (self.ListenPort)
					
				if token[0] == "gate-server-port":
					self.GateServerPort = token[1]
					print "(*) Gate Server port : %d" % (self.GateServerPort)
					
				if token[0] == "permitted-address":
					self.PermittedAddress += [token[1]]
					print "(*) IP [%s] added to permitted addresses list!" % (token[1])
					if self.ListenToAllAddress:
						self.ListenToAllAddress = False
		finally:
			fin.close()
		return True
			
	def ReadConfig(self, FileName):
		if not os.path.exists(FileName) and not os.path.isfile(FileName):
			print "(!) Cannot open configuration file [%s]." % FileName
			return False
		key = FileName.split(".")[-2]
		fin = open(FileName,'r')
		try:
			self.Config[key] = fin.read()
		finally:
			fin.close()
		return True
