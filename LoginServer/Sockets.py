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
from threading import Thread, Semaphore
from Helpers import  Callbacks

ClientLocker = Semaphore()

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
		self.running = False
		self.callbacks = Callbacks(callbacks)
		self.socket_list = []

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
			self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
			self.server.bind((self.host, self.port))
			self.server.listen(10)
		except socket.error, (value,message):
			if self.server:
				self.server.close()
			print "Could not open socket: " + message
			sys.exit(1)
		self.callbacks('onListen', self)
	
	def run(self):
		global ClientLocker
		self.open_socket()
		self.running = True
		while self.running:
			ClientLocker.acquire()
			input = [self.server]
			input += self.socket_list
			ClientLocker.release()
			try:
				inputready, outputready, exceptready = select.select(input, [], [])
			except:
				pass
			for s in inputready:
				if s == self.server:
					newclient = ClientSocket(self.server.accept())
					ClientLocker.acquire()
					self.socket_list.append(newclient)
					ClientLocker.release()
					self.callbacks('onConnected', newclient)
				else:
					try:
						data = s.client.recv(1024*32)
					except:
						data = ""
					if data == "":
						self.callbacks('onDisconnected', s)
						ClientLocker.acquire()	
						self.socket_list.remove(s)
						ClientLocker.release()
					else:
						self.callbacks('onReceive', s, data)	
		self.server.close()

class ClientSocket(object):
	def __init__(self, (client, address)):
		self.client = client
		self.address = address[0]
		self.buffer = ""
		
	def disconnect(self):
		global ClientLocker
		ClientLocker.acquire()
		self.client.close()
		ClientLocker.release()
		
	def fileno(self):
		return self.client.fileno()