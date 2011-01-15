import struct
from Sockets import HelbreathSocket
from Helpers import strip_zeros
from NetMessages import Packets

class ClientSocket(HelbreathSocket):
	'''
		Gate server protocol class
	'''
	
	def __init__(self, instance):
		'''
			No need for address and port
		'''
		super(ClientSocket, self).__init__(
			address = None,
			port = None,
			instance = instance
		)
		self.setblocking(False)
	
	def pop_packet(self):
		packet = super(ClientSocket, self).pop_packet()
		
		if not packet:
			return False
		
		if len(packet) < 6:
			return False
		
		MsgID, MsgType = struct.unpack('<IH', packet[:6])
		packet = packet[6:]
		
		if MsgID == Packets.MSGID_REQUEST_INITPLAYER:
			print '%r %db' % (packet, len(packet))
			fmt = '<10s' # char_name
			fmt += '10s' # account_name
			fmt += '10s' # account password
			fmt += '?' # is observer mode ?
			packet_len = struct.calcsize(fmt)
			
			(char_name, account_name, account_password, is_observer_mode, ) = \
				map(strip_zeros, struct.unpack(fmt, packet[:packet_len]))
				
			print char_name, account_name, account_password, is_observer_mode
			self.on_request_initplayer(
				char_name = char_name,
				account_name = account_name,
				account_password = account_password,
				is_observer_mode = is_observer_mode,
				client = self						
			)
		else:
			print 'Client packet. MsgID: 0x%08X MsgType: 0x%04X' % (MsgID, MsgType)
		
	def on_request_initplayer(self, char_name, account_name, account_password, is_observer_mode, client):
		pass