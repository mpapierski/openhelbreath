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
import socket, select, random, struct
from Helpers import Callbacks

class Socket(object):
	"""
		Object wrapper for socket
	"""
	read_buffer = ''
	write_buffer = ''
	instance = None
	def __init__(self, address = '', port = '', callbacks = {}, instance = None):
		self.address, self.port, self.callbacks = address, port, callbacks
		self.connecting = False
		self.connected = False
		if instance:
			self.instance = instance
			self.connected = True
			return

		try:
			self.instance = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.address = address
			self.port = port
		except socket.error as msg:
			sys.stderr.write("[ERROR] %s\n" % msg[1])

	def recv(self, bytes = 32767):
		buffer = self.instance.recv(bytes)
		self.read_buffer += buffer
		return len(buffer)

	def send(self, data):
		'''
			Don't directly send data. In non blocking sockets it could not be safe
		'''
		self.write_buffer += data

	def flush(self):
		'''
			Flush data directly
			This is called only ONCE when the descriptor is marked as writeable
		'''
		bytes = self.instance.send(self.write_buffer)
		self.write_buffer = self.write_buffer[bytes:]
		return bytes

	def connect(self):
		return self.connect()

	def fileno(self):
		return self.instance.fileno() if self.instance else None

	def bind(self):
		self.instance.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.instance.bind((self.address, self.port))

	def listen(self, max = 1):
		self.instance.listen(max)

	def accept(self, socketcls):
		(conn, addr) = self.instance.accept()
		s = socketcls(instance = conn)
		(s.address, s.port) = addr
		return s

	def close(self):
		self.connected = False
		if not self.instance:
			return
		del self.instance
		self.instance = None

	def setblocking(self, v):
		self.instance.setblocking(v)

	def read(self, bytes):
		'''
			Pop data from read_buffer with exact length = bytes
		'''
		if len(self.read_buffer) < bytes:
			return ''
		data = self.read_buffer[:bytes]
		self.read_buffer = self.read_buffer[bytes:]
		return data

class HelbreathSocket(Socket):
	def send_msg(self, data):
		dwSize = len(data) + 3
		buffer = data[:]
		cKey = random.randint(0, 255)
		if cKey > 0:
			buffer = map(ord, buffer)
			for i in range(len(buffer)):
				buffer[i] = buffer[i] + (i ^ cKey)
				buffer[i] = buffer[i] ^ (cKey ^ (len(buffer) - i))
			buffer = ''.join(map(lambda x: chr(x & 255) , buffer))

		buffer = chr(cKey) + struct.pack('<H', len(buffer) + 3) + buffer
		self.send(buffer)

	def pop_packet(self):
		if len(self.read_buffer) < 3:
			return False
		try:
			(key, size) = struct.unpack('<BH', self.read(3))
		except:
			return False

		buffer = self.read(size - 3)

		if key:
			Decode = lambda buffer, dwSize, cKey: "".join(map(lambda n: (lambda asdf: chr(asdf & 255))((ord(buffer[n]) ^ (cKey ^ (dwSize - n))) - (n ^ cKey)), range(len(buffer))))
			buffer = Decode(buffer, size - 3, key)

		return buffer



class ServerSocket(object):
	server = None

	def __init__(self, (address, port), callbacks, socketcls):
		self.address, self.port = address, port
		self.size = 8192
		self.callbacks = Callbacks(callbacks)
		self.socket_list = []
		self.open_socket()
		self.socketcls = socketcls

	def close(self):
		"""
			Disconnect ppl connected
		"""
		for socket in self.socket_list:
			socket.close()
		self.close()
		self.callbacks('onClose', self)

	def open_socket(self):
		"""
			Make socket ready for connections
		"""
		try:
			self.server = Socket(address = self.address, port = self.port)
			self.server.setblocking(False)
			self.server.bind()
			self.server.listen(10)
		except socket.error, (value, message):
			print '[ERROR] %s\n' % message
			self.close()
		self.callbacks('onListen', self)

	def fileno(self):
		return self.server.fileno()

	def on_accept(self):
		'''
			Fired when self.server is on readlist
		'''
		c = self.server.accept(socketcls = self.socketcls)
		c.setblocking(False)
		c.parent = self
		self.socket_list.append(c)
		self.callbacks('onConnected', c)

	def on_read(self, client):
		bytes = 0
		try:
			bytes = client.recv(self.size)
		except socket.error, (value, message):
			bytes = 0

		if not bytes:
			self.callbacks('onDisconnected', client)
			self.socket_list.remove(client)
			return

		self.callbacks('onReceive', client)

		# In case  when client gets closed in callback
		if not client.fileno():
			self.callbacks('onDisconnected', client)
			self.client_list.remove(client)
