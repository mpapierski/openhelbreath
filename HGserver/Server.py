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
import select

import Settings
from Sockets import ServerSocket
from Protocol import GateProtocol

class GateSocket(GateProtocol):
	def __init__(self, address, port, server_instance):
		super(GateSocket, self).__init__(address = address, port = port, server_instance = server_instance)
		self.setblocking(False)
	
class Server(object):
	'''
		New game server
		2011 Drajwer
	'''
	
	def __init__(self):
		self.server_name = ''
		self.maps = []
		self.clients = []
		self.logsockets = []
		
	def read_config(self):
		# JSON configuration reader
		import json
		
		config = json.load(open('settings.cfg'))
		self.server_name = str(config['CONFIG']['game-server-name'])
		self.address = str(config['CONFIG']['game-server-address'])
		self.port = int(config['CONFIG']['game-server-port'])
		
		self.log_server_address = str(config['CONFIG']['log-server-address'])
		self.gate_server_port = int(config['CONFIG']['gate-server-port'])

		self.maps = map(str, config['MAPS'])
		return True
	
	def initialize(self):
		if not self.read_config():
			return False
		
		for i in range(5):
			socket = GateSocket(
				address = self.log_server_address,
				port = self.gate_server_port,
				server_instance = self
			)
			socket.on_response_registergameserver = self.on_response_registergameserver
			socket.on_connect = self.on_logsocket_connected
			socket.on_disconnect = self.on_logsocket_connection_lost
			
			self.logsockets += [socket]
			
		self.logsockets[0].connect()
		
		return True
		
	def loop(self):
		rinput = filter(lambda sock: sock.connected, self.logsockets)
		winput = filter(lambda sock: sock.connecting or sock.write_buffer, self.logsockets)
		
		(rlist, wlist, elist) = select.select(rinput, winput, [], 0.5)
		
		for socket in rlist:
			if socket in self.logsockets:
				n = socket.recv()
				if not n:
					socket.on_disconnect(socket)
					socket.close()
					
				while socket.pop_packet():
					pass
			
		for socket in wlist:
			if socket.connecting:
				socket.connecting = False
				socket.connected = True
				socket.on_connect(socket)
				
			n = socket.flush()
	
	def on_logsocket_connected(self, logsocket):
		'''
			Request game server registration
		'''
		
		#How many connected sockets we have?
		connected = len(filter(lambda _: _.connected, self.logsockets)) 
		
		if connected > 1:
			print 'Trying to register game server socket'
			logsocket.do_register_gameserversocket(
				gsid = self.gsid
			)
		else:
			print 'Trying to register game server %s...' % self.server_name
			logsocket.do_register_gameserver(
				server_name = self.server_name,
				address = self.address,
				port = self.gate_server_port,
				maps = self.maps
			)
			
	def on_logsocket_connection_lost(self, logsocket):
		print 'Lost connection to gate server on socket-%d' % self.logsockets.index(logsocket)
		if not filter(lambda _: _.connected, self.logsockets):
			print 'Lost connection to gate server!'
	
	def on_response_registergameserver(self, success, gsid = None):
		if not success:
			print 'Game server %s registration rejected!' % self.server_name
			return
		
		self.gsid = gsid
		
		print 'Game server %s registration success! (GSID:%r)' % (self.server_name, gsid)
		
		for i, socket in enumerate(self.logsockets):
			if not socket.connected:
				print 'Connecting gate server socket-%d!' % (i, )
				socket.connect()