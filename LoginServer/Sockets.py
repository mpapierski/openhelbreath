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
import socket, select, sys, copy
from threading import Thread
from Helpers import  Callbacks

class ServerSocket(Thread):
	def __init__(self, (host, port), callbacks):
		"""
			Initializing server thread
		"""
		Thread.__init__(self)
		self.host, self.port = host, port
		self.backlog = 5
		self.size = 8192
		self.server = None
		self.threads = []
		self.callbacks = Callbacks(callbacks)
		self.callbacks['onDisconnected'] += [self.client_disconnect] #injecting own disconnect callback
		self.running = False

	def __del__(self):
		self.server.close() #propably useless

	def close_server(self):
		"""
			Disconnect ppl connected
		"""
		for i in self.threads:
			if i.isAlive():
				i.disconnect()
				i.join()
				self.threads.remove(i)
				
		self.server.close()
		self.callbacks('onClose', self)

	def open_socket(self):
		"""
			Make socket ready for connections
		"""
		try:
			self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) #important!
			self.server.bind((self.host, self.port))
			self.server.listen(1)
			
		except socket.error, (value,message):
			if self.server:
				self.server.close()
			print "Could not open socket: " + message
			sys.exit(1)
		self.callbacks('onListen', self)
		
	def client_disconnect(self, which):
		"""
			Here is the injected callback for Disconnecting.
			Simply we are removing thread that just stopped
		"""
		if which in self.threads:
			self.threads.remove(which)
		
	def run(self):
		self.open_socket()
		input = [self.server,sys.stdin]
		self.running = True
		while self.running:
			inputready, outputready, exceptready = select.select(input, [], [])
			for s in inputready:
				if s == self.server:
					c = ClientSocket(self.server.accept(), self)
					c.start()
					self.threads += [c]
				elif s == sys.stdin: 
					junk = sys.stdin.readline() 
					self.running = False
		self.server.close()
		for c in self.threads:
			c.join()

class ClientSocket(Thread):
	def __init__(self, (client, address), parent):
		Thread.__init__(self)
		self.client = client
		self.address = address[0]
		self.size = 1024
		self.buffer = ""
		self.parent = parent
		#self.callbacks = copy.deepcopy(self.parent.callbacks)
		CB = dict(self.parent.callbacks.items())
		self.callbacks = Callbacks(CB)

	def disconnect(self):
		if self.running:
			self.running = False
			self.client.close()
		self.callbacks('onDisconnected', self)
		
	def receive(self, bytes):
		tmp=self.buffer[:bytes]
		self.buffer = self.buffer[bytes:]
		return tmp

	def run(self):
		self.running = True
		self.callbacks('onConnected', self)
		while self.running:
			data = self.client.recv(self.size)
			if data:
				self.buffer += data
				self.callbacks('onReceive', self, len(data))
			else:
				break
		self.disconnect()
