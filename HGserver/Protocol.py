import struct, os
from Sockets import HelbreathSocket
from NetMessages import Packets
from Helpers import strip_zeros

class GateProtocol(HelbreathSocket):
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
		elif MsgID == Packets.MSGID_NOTICEMENTFILECONTENTS:
			self.on_receive_config_noticement(noticement = packet)
			
		elif MsgID == Packets.MSGID_RESPONSE_REGISTERGAMESERVERSOCKET:
			self.on_response_registergameserversocket(self)
		elif MsgID == Packets.MSGID_RESPONSE_PLAYERDATA:
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
			Packets.MSGID_REQUEST_PLAYERDATA,
			Packets.DEF_MSGTYPE_CONFIRM,
			char_name,
			account_name,
			account_password,
			address
		)
		
		self.send_msg(data)
	
	def do_entergame_confirm(self, account_name, account_password, server_name, address, level):
		print 'do_entergame_confirm'
		fmt = '<IH'
		fmt += '10s' # Account name
		fmt += '10s' # Account password
		fmt += '10s' # Server name
		fmt += '16s' # Client IP
		fmt += 'I' # Level
		
		data = struct.pack(fmt,
				Packets.MSGID_ENTERGAMECONFIRM,
				Packets.DEF_MSGTYPE_CONFIRM,
				account_name,
				account_password,
				server_name,
				address,
				level
		)
		
		self.send_msg(data)
		
	'''
		Parsers
	'''
	
	def __response_playerdata(self, packet):
		# TODO: parse rest of values items and bankitems ...
		
		packet_size = struct.calcsize(fmt)
		
		fields = (
			'char_name',
			'map_name',
			'x',
			'y',
			'sex',
			'skin',
			'hair_style',
			'hair_color',
			'underwear',
			'guild_name',
			'guild_rank',
			'hp',
			'level',
			'str',
			'vit',
			'dex',
			'int',
			'mag',
			'chr',
			'luck',
			'exp',
			'magic_mastery',
			'skill_mastery',
			'location',
			'mp',
			'sp',
			'ek_count',
			'pk_count',
			'reward_gold',
			'skill_ssn',
			'hunger_status',
			'admin_user_level',
			'timeleft_shutup',
			'timeleft_rating',
			'rating',
			'guild_guid',
			'down_skill_index',
			'char_id',
			'char_idnum1',
			'char_idnum2',
			'char_idnum3',
			'block_date',
			'questnum',
			'questcount',
			'questrewtype',
			'questrewammount',
			'contribution',
			'questid',
			'questcompleted',
			'leftforcerecalltime',
			'leftfirmstaminartime',
			'eventid',
			'leftsac',
			'fightnum',
			'fightdate',
			'fightticket',
			'leftspecialtime',
			'warcon',
			'lockedmapname',
			'lockedmaptime',
			'crujob',
			'cruconstructpoint',
			'cruid',
			'leftdeadpenaltytime',
			'partyid',
			'gizonitemupgradeleft'
		)

		playerrawdata = struct.unpack(fmt, packet[:packet_size])
		print playerrawdata
		player_data = zip(fields, playerrawdata)
		print player_data
		player_data = dict(player_data)

		for key in ('map_name', 'char_name', 'location', 'lockedmapname', 'guild_name'):
			player_data[key] = strip_zeros(player_data[key])
		
		player_data['skill_ssn'] = struct.unpack('<24I', player_data['skill_ssn'])
		print player_data['skill_ssn']
		self.on_response_playerdata(
			char_name = player_data['char_name'],
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