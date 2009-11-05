import socket, select
from threading import Thread

class clientSocket(Thread):
	def __init__(self, data):
		if not ('host' in data and 'port' in data):
			raise ValueError
		Thread.__init__(self)
		self.fActive=False
		self.data = data
		self.sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		self.send_proc = self.tcp_send
		self.recv_proc = self.tcp_recv
		self.connection=(self.data['host'], self.data['port'])
		events = ['onConnect','onConnecting','onDisconnect', 'onRead', 'onError','onFinish']
		for event in events:
			if event not in self.data:
				self.data[event]=None
	def tcp_send(self, data):
		self.sock.send(self, data)
		#print("TCP SEND : %s"% data)

	def udp_send(self, data):
		self.sock.sendto(data, self.connection)

	def tcp_recv(self, count):
		return self.sock.recv(count)

	def udp_recv(self, count):
		asdf = self.sock.recvfrom(count)
		print asdf
		return asdf[0]

	def __del__(self):
		self.sock.close()
		print("Socket destructor!")
		
	def send(self, data):
		if self.fActive == False:
			return
		try:
			self.send_proc(data)
		except socket.error, e:
			self.data['onError'](self, e) if self.data['onError'] != None else None
			
	def connect_to(self, where=()): 
		try:
			self.data['onConnecting'](self) if self.data['onConnecting'] != None else None
			self.sock.connect(self.connection)
		except socket.gaierror, e:
			self.data['onError'](self, e) if self.data['onError'] != None else None
			#sys.exit(1)
			return False
		except socket.error, e:
			self.data['onError'](self, e) if self.data['onError'] != None else None
			return False
		
		self.data['onConnect'](self) if self.data['onConnect'] != None else None
		while self.fActive:
			a, b, c = select.select([self.sock], [], [])
			for s in a:
				data = s.recv(1024*32)

				if not data:
					self.onDisconnect()
					break
				self.data['onRead'](self, data) if self.data['onRead'] != None else None

	def connect(self,where=()):
		if where!=():
			self.connection=where
		self.start()
	   
	def run(self):
		self.connect_to()
		self.data['onFinish'](self) if self.data['onFinish'] != None else None

	def onDisconnect(self):
		self.fActive=False
		self.sock.close()
		self.data['onDisconnect'](self) if self.data['onDisconnect'] != None else None

	def disconnect(self):
		self.onDisconnect()

	def getActive(self):
		return self.fActive

	def setActive(self, value):
		self.fActive = value
		self.start() if self.fActive else self.disconnect()
	
	Active = property(getActive, setActive)
