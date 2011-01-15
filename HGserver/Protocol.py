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
			
	'''
		Actions
	'''
	
	def do_register_gameserver(self, server_name, address, port, maps):
		'''
			Register game server main socket in gate server
		'''	
		header = struct.pack('<IH10s16sHBBH', 
			Packets.MSGID_REQUEST_REGISTERGAMESERVER, # MsgID
			Packets.DEF_LOGRESMSGTYPE_CONFIRM, # MsgType
			server_name, # Server name (10b)
			address, # External address (16b)
			port, # Port (u2)
			False, # Configs (bool)
			len(maps), # Total maps u1
			os.getpid(), # Server ID u2
		)
				
		for map in maps:
			print map
			header += struct.pack('<11s', map)
			
		self.send_msg(header)
		
	def do_register_gameserversocket(self, gsid):
		'''
			Register game server sub socket in gate server
		'''
		
		header = struct.pack('<IH',
			Packets.MSGID_REQUEST_REGISTERGAMESERVERSOCKET,
			gsid
		)
		
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