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
		self.server_name = 'Test'
		self.maps = ['aresden', 'elvine', 'default']
		self.clients = []
		self.logsockets = []
		
		
	def initialize(self):
		for i in range(5):
			socket = GateSocket(
				address = '192.168.1.245',
				port = 6502,
				server_instance = self
			)
			socket.on_response_registergameserver = self.on_response_registergameserver
			self.logsockets += [socket]
			
		self.logsockets[0].connect()
		
	def loop(self):
		rinput = filter(lambda sock: sock.connected, self.logsockets)
		winput = filter(lambda sock: sock.connecting or sock.write_buffer, self.logsockets)
		
		(rlist, wlist, elist) = select.select(rinput, winput, [], 0.5)
		for socket in rlist:
			n = socket.recv()
			if not n:
				socket.on_disconnect()
				socket.close()
				
			while socket.pop_packet():
				pass
			
		for socket in wlist:
			if socket.connecting:
				socket.connecting = False
				socket.connected = True
				socket.on_connect()
				
			n = socket.flush()
	
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