import struct, os
from Sockets import HelbreathSocket
import NetMessages
import Packets
from Helpers import strip_zeros

class GateSocket(HelbreathSocket):
	'''
		Gate server protocol class
	'''
	def __init__(self, address, port):
		super(GateSocket, self).__init__(
			address = address,
			port = port
		)
		self.setblocking(False)
		
	def pop_packet(self):
		packet = super(GateSocket, self).pop_packet()
		
		if not packet:
			return False
		
		if len(packet) < 6:
			return False
		
		MsgID, MsgType = struct.unpack('<IH', packet[:6])
		packet = packet[6:]
		
		if MsgID == NetMessages.MSGID_RESPONSE_REGISTERGAMESERVER:
			packet = Packets.RESPONSE_REGISTER_GAMESERVER.unpack(packet)
			self.on_response_registergameserver(
				MsgType == NetMessages.DEF_MSGTYPE_CONFIRM,
				gsid = packet.server_id # "GSID"
			)
		elif MsgID == NetMessages.MSGID_NOTICEMENTFILECONTENTS:
			self.on_receive_config_noticement(noticement = packet)
		elif MsgID == NetMessages.MSGID_RESPONSE_REGISTERGAMESERVERSOCKET:
			self.on_response_registergameserversocket(self)
		elif MsgID == NetMessages.MSGID_RESPONSE_PLAYERDATA:
			self.__response_playerdata(packet)
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
		self.send_packet(
			Packets.REQUEST_REGISTER_GAMESERVER,
			server_name = server_name,
			address = address,
			port = port,
			received_configs = False,
			map_count = len(maps),
			maps = map(
				lambda map_name: dict(
					map_name = map_name
				),
				maps
			),
			server_id = os.getpid()
		)
		
	def do_register_gameserversocket(self, gsid):
		'''
			Register game server sub socket in gate server
		'''
		
		header = struct.pack('<IH',
			NetMessages.MSGID_REQUEST_REGISTERGAMESERVERSOCKET,
			gsid
		)
		
		self.send_msg(header)
		
	def do_request_playerdata(self, char_name, account_name, account_password, address):
		print 'do_request_playerdata'
		fmt = '<IH'
		fmt += '10s' # character name
		fmt += '10s' # account name
		fmt += '10s' # account password
		fmt += '15s' # address
		fmt += 'x' # 1b padding, always zero. "Account Status"
		print address, type(address)
		data = struct.pack(fmt,
			NetMessages.MSGID_REQUEST_PLAYERDATA,
			NetMessages.DEF_MSGTYPE_CONFIRM,
			char_name,
			account_name,
			account_password,
			address
		)
		
		self.send_msg(data)
	
	def do_entergame_confirm(self, account_name, account_password, server_name, address, level):
		self.send_packet(
			Packets.ENTERGAME_CONFIRM,
			account_name = account_name,
			account_password = account_password,
			server_name = server_name,
			client_ip = address,
			level = level
		)
		
	'''
		Parsers
	'''
	
	def __response_playerdata(self, packet):
		# TODO: parse rest of values items and bankitems ...
		player_data = Packets.RESPONSE_PLAYERDATA.unpack(packet)
		print player_data.get_dict()

		self.on_response_playerdata(
			char_name = player_data.char_name,
			player_data = player_data
		)
		
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
		
	def on_response_playerdata(self, char_name, player_data):
		'''
			Handle for MSGID_RESPONSE_PLAYERDATA
			Fired when gate server gives us serialized player data
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
		
	def on_receive_config_noticement(self, noticement):
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