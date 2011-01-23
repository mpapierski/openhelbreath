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
import select, random, time
from threading import Thread, Semaphore

import Settings
from Sockets import ServerSocket
from Protocol import GateProtocol
from Client import ClientSocket
from Timer import TimerManager

class GateSocket(GateProtocol):
	def __init__(self, address, port):
		super(GateSocket, self).__init__(address = address, port = port)
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
		self.serversocket = None
		self.noticement = ''
		self.event_thread_alive = False
		self.event_thread = False
		
		# Guards...
		
		self.clients_guard = Semaphore()
		
	def stop_and_cleanup(self):
		# Called when someone interrupts main thread
		self.event_thread_alive = False
		self.event_thread.join()
		
	def read_config(self):
		# JSON configuration reader
		import json, os
		from HBMap import HBMap
		config = json.load(open('settings.cfg'))
		self.server_name = str(config['CONFIG']['game-server-name'])
		self.address = str(config['CONFIG']['game-server-address'])
		self.port = int(config['CONFIG']['game-server-port'])
		
		self.log_server_address = str(config['CONFIG']['log-server-address'])
		self.gate_server_port = int(config['CONFIG']['gate-server-port'])
		
		self.maps = {}
		
		for map_name, options in config['MAPS'].items():
			map_name = str(map_name)
			print 'Initializing map %s...' % (map_name, )
			file_name = os.path.join(os.path.dirname(__file__), 'MAPDATA', options['amd'])
			
			if not os.path.exists(file_name):
				print 'Failure. Map %s does not exists.' % (map_name, )
				continue
			try:
				amd = HBMap(file_name)
			except Exception as e:
				print 'Failure. %s.' % (e, )
				continue
			print 'OK! SIZE(%d, %d)' % (amd.MAPSIZEX, amd.MAPSIZEY)
			self.maps[map_name] = config['MAPS'][map_name]
			self.maps[map_name]['amd'] = amd
		return True
	
	def initialize(self):
		if not self.read_config():
			return False
		
		for i in range(5):
			socket = GateSocket(
				address = self.log_server_address,
				port = self.gate_server_port
			)
			
			self.setup_callbacks_gate(socket)
	
			self.logsockets += [socket]
			
		self.logsockets[0].connect()
		
		self.serversocket = ServerSocket(
			(self.address, self.port),
			socketcls = ClientSocket
		)
		
		self.serversocket.on_listen = self.on_gameserver_listen
		self.serversocket.open_socket()
		
		return True
		
	def loop(self):
		# TODO: wrap around all clients_guard dependent code 
		rinput = filter(lambda sock: sock.connected, self.logsockets)
		self.clients_guard.acquire()
		rinput += self.clients
		self.clients_guard.release()
		
		rinput += [self.serversocket]

		winput = filter(lambda sock: sock.connecting or sock.write_buffer, self.logsockets)
		winput += filter(lambda sock: sock.write_buffer, self.clients)
		
		(rlist, wlist, elist) = select.select(rinput, winput, [], 0.5)
		
		for socket in rlist:
			if socket in self.logsockets:
				n = socket.recv()
				if not n:
					socket.on_disconnect(socket)
					socket.close()
					continue
													
				while socket.pop_packet():
					# Why would we even disconnect gate socket?
					# Just do nothing
					pass 
			
			self.clients_guard.acquire()
			
			if socket in self.clients:
				n = socket.recv()
				if not n:
					socket.on_disconnect(socket)
					socket.close()
					self.clients.remove(socket)
					continue
									
				while socket.pop_packet():
					print 'Pop packet', socket.fileno()
					if not socket.fileno():
						socket.on_disconnect(socket)
						self.clients.remove(socket)
			
			self.clients_guard.release()
			
			if socket == self.serversocket:
				c = self.serversocket.accept(socketcls = ClientSocket)
				c.setblocking(False)
				self.clients_guard.acquire()
				try:
					c.id = max(map(lambda client: client.id, self.clients)) + 1
				except ValueError as e:
					c.id = 0
				
				self.clients.append(c)
				self.setup_callbacks_client(c)
				c.on_connect(c)
				self.clients_guard.release()
				
		for socket in wlist:
			if socket.connecting:
				socket.connecting = False
				socket.connected = True
				socket.on_connect(socket)
				
			n = socket.flush()
	
	def event_loop(self):
		# Event thread main entry function
		self.timers.process_all()

	def timer_connected_players(self):
		self.clients_guard.acquire() 
		print '(O) Players connected:', len(self.clients)
		self.clients_guard.release()
		
	def on_server_registered(self):
		self.timers = TimerManager()
		self.timers.register_timer(None, self.timer_connected_players, 1.0)
		
		def thread_ep(server_instance):
			# Thread entry point
			server_instance.event_thread_alive = True
			while server_instance.event_thread_alive:
				server_instance.event_loop()
				time.sleep(0.1)
				
		self.event_thread = Thread(target = thread_ep, args = (self, ))
		self.event_thread.start()
		
	'''
		Socket events
	'''
	
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
				port = self.port,
				maps = self.maps.keys()
			)
			
	def on_logsocket_connection_lost(self, logsocket):
		'''
			Fired when gate server socket lost connection
		'''
		
		print 'Lost connection to gate server on socket-%d' % self.logsockets.index(logsocket)
		if not filter(lambda _: _.connected, self.logsockets):
			print 'Lost connection to gate server!'
	
	def on_gameserver_listen(self):
		print 'Game server socket is working!'
		
	def on_client_connect(self, client):
		print 'Client connected!'
	
	def on_client_disconnect(self, client):
		print 'Client disconnected!'

	'''
		Communication
	'''
	
	
	def getlogsocket(self):
		# TODO : Filter only connected logsockets?
		return random.choice(self.logsockets)
		
	'''
		Functions
	'''
	
	def setup_callbacks_gate(self, logsocket):
		'''
			Setup callbacks on gate socket
		'''
		logsocket.on_response_registergameserver = self.on_response_registergameserver
		logsocket.on_connect = self.on_logsocket_connected
		logsocket.on_disconnect = self.on_logsocket_connection_lost
		logsocket.on_response_playerdata = self.on_response_playerdata
		
		# Configs
		
		logsocket.on_receive_config_noticement = self.on_receive_config_noticement		

	def setup_callbacks_client(self, client):
		'''
			Setup callbacks on client socket
		'''
		client.on_connect = self.on_client_connect
		client.on_disconnect = self.on_client_disconnect
		
		client.on_request_noticement = self.client_on_request_noticement
		client.on_request_initplayer = self.client_on_request_initplayer
		client.on_request_initdata = self.client_on_request_initdata
		client.on_request_fullobjectdata = self.client_on_request_fullobjectdata
		
	def delete_client(self, client):
		# TODO: options etc
		client.close()
		if client in self.clients:
			self.clients.remove(client)
		
	'''
		Gate server handlers
	'''
	
	def on_receive_config_noticement(self, noticement):
		self.noticement = noticement.rstrip()
	
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
				
		self.on_server_registered()
			
	def on_response_playerdata(self, char_name, player_data):
		try:
			client, = filter(lambda _: _.char_name, self.clients)
		except ValueError as e:
			print '(O) Got unknown player data %r' % char_name
			return
		
		if not player_data:
			print '(HACK?) Not existing character(%s) data request! Rejected!' % (char_name, )
			self.delete_client(client)
			return
		
		if player_data['map_name'] not in self.maps:
			print 'Player stuck on not existing map "%s" !' % (player_data['map_name'], )
			self.delete_client(client)
			return
		
		maploc = self.maps[player_data['map_name']]
		
		if (player_data['x'], player_data['y']) not in maploc:
			player_data['x'], player_data['y'] = random.choice(maploc['initial-points'])
			print '%s new initial point is', player_data['x'], player_data['y']
			
		client.player_data = player_data
		client.map = maploc
				
		client.do_response_initplayer(success = True)
		
		# TODO : when you call it with success = False client will get 
		# 'World server full try other server'. Player limit could be 
		# implemented.
		
		self.getlogsocket().do_entergame_confirm(
			account_name = client.account_name,
			account_password = client.account_password,
			server_name = self.server_name,
			address = client.address,
			level = player_data['level']
		)
		
		print '(TestLog) Enter Game Confirm Level: %d' % player_data['level']
		
	'''
		Client socket handlers
	'''
	
	def client_on_request_initplayer(self, char_name, account_name, account_password, is_observer_mode, client):
		print 'Request init player'
		print char_name, account_name, account_password, is_observer_mode
		
		client.char_name = char_name
		client.account_name = account_name
		client.account_password = account_password
		
		self.getlogsocket().do_request_playerdata(
			char_name = char_name,
			account_name = account_name,
			account_password = account_password,
			address = client.address
		)
		
	def client_on_request_initdata(self, char_name, account_name, account_password, client):
		if client.char_name != char_name:
			print '(!) Error!', self.char_name, '!=', char_name
			self.delete_client(client)
			return
		client.do_playercharactercontents()
		client.do_response_initdata()
		
	def client_on_request_noticement(self, client, file_size):
		# Ignore client size of noticement data stored on disk and always
		# send new noticement.
		client.send_noticement(self.noticement)
				
	def client_on_request_fullobjectdata(self, client, object_id):
		print 'request fullobjectdata req:%d client:%d' % (object_id, client.id)
		try:
			obj, = filter(lambda _: _.id == object_id, self.clients)
		except ValueError as e:
			print '(!) Client requests full data from unknown object.'
			self.delete_client(client)
			return
		
		self.do_event_motion('stop', obj)