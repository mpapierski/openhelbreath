import struct, os
from Sockets import HelbreathSocket
from NetMessages import Packets

class BaseProtocolSocket(HelbreathSocket):
	def __init__(self, address, port, server_instance):
		super(BaseProtocolSocket, self).__init__(address = address, port = port)
		self.server = server_instance

class GateProtocol(BaseProtocolSocket):
	'''
		Gate server protocol class
	'''
	
	def pop_packet(self):
		packet = super(GateProtocol, self).pop_packet()
		
		if not packet:
			return False
		
		if len(packet) < 6:
			return False
		
		MsgID, MsgType = struct.unpack('<IH', packet[:6])
		packet = packet[6:]
		
		if MsgID == Packets.MSGID_RESPONSE_REGISTERGAMESERVER:
			GSID, = struct.unpack('<h', packet[:2])
			self.on_response_registergameserver(
				MsgType == Packets.DEF_MSGTYPE_CONFIRM,
				GSID
			)
		elif MsgID == Packets.MSGID_RESPONSE_REGISTERGAMESERVERSOCKET:
			self.on_response_registergameserversocket(self)
		else:
			print '%s gets unknown message: MsgID: 0x%08X MsgType: 0x%04X' % (self.__class__.__name__, MsgID, MsgType)
			
		return True
			
	def on_connect(self):
		'''
			Request game server registration
			MsgID: MSGID_REQUEST_REGISTERGAMESERVER
			MsgType: DEF_MSGTYPE_CONFIRM 
			Server Name - 10b
			Game server external address - 16b
			Port - u2
			Do I have configs? - bool
				Note: First login socket must tell login server that he
				does not have configs.
			Total maps - u1
			Server ID - u2
		'''
		
		connected = len(filter(lambda _: _.connected, self.server.logsockets)) 
		
		print 'Trying to register game server %s...' % self.server.server_name
		
		if connected > 1:
			header = struct.pack('<IH',
				Packets.MSGID_REQUEST_REGISTERGAMESERVERSOCKET,
				self.server.gsid
			)
			print 'Register game server socket'
		else:
			print 'Register game server main socket'
			header = struct.pack('<IH10s16sHBBH', 
				Packets.MSGID_REQUEST_REGISTERGAMESERVER, # MsgID
				Packets.DEF_LOGRESMSGTYPE_CONFIRM, # MsgType
				self.server.server_name, # Server name (10b)
				'127.0.0.1', # External address (16b)
				9001, # Port (u2)
				False, # Configs (bool)
				len(self.server.maps), # Total maps u1
				os.getpid(), # Server ID u2
			)
			
			for map in self.server.maps:
				header += struct.pack('<11s', map)
			
		self.send_msg(header)
		
	'''
		Callbacks
	'''
	def on_response_registergameserver(self, success, gsid = None):
		'''
			Handler for MSGID_RESPONSE_REGISTERGAMESERVER
			Fired when Game server registers first socket on gate server.
			@param server_response: (bool) True if server accepts us, False if not
			@param gsid: (int) Game server ID
		'''
	
	def on_response_registergameserversocket(self):
		'''
			Handle for MSGID_RESPONSE_REGISTERGAMESERVERSOCKET
			Fired when Game server register more than one sockets on gate server.
		'''
		
	def on_receive_config_item(self, data):
		'''
			Item config data
		'''
	
	def on_receive_config_builditem(self, data):
		'''
			Build item config data
		'''
		
	def on_receive_config_npc(self, data):
		'''
			NPC config data
		'''
		
	def on_receive_config_dupitem(self, data):
		'''
			Duplicate item config data
			TODO: it is not needed anymore
		'''
	
	def on_receive_config_magic(self, data):
		'''
			Magic config data
		'''
		
	def on_receive_config_noticement(self, data):
		'''
			Noticement data
		'''
		
	def on_receive_config_potion(self, data):
		'''
			Potion config data
		'''
		
	def on_receive_config_quest(self, data):
		'''
			Quest config data
		'''
		
	def on_receive_config_skill(self, data):
		'''
			Skill config data
		'''
		
	def on_receive_config_adminsettings(self, data):
		'''
			Admin settings config data
		'''
		
	def on_receive_config_settings(self, data):
		'''
			Settings config data
		'''
		
	def on_receive_config_npcitem(self, data):
		'''
			NPCItem config data
		'''