import struct
from Sockets import HelbreathSocket
from NetMessages import Packets

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
		
		if packet == Packets.MSGID_RESPONSE_REGISTERGAMESERVER:
			self.on_response_registergameserver(MsgType == Packets.DEF_MSGTYPE_CONFIRM)			
		else:
			print '%s gets unknown message: MsgID: 0x%08X MsgType: 0x%04X' % (self.__class__.__name__, MsgID, MsgType)
			
	def on_response_registergameserver(self, success):
		'''
			Handler for MSGID_RESPONSE_REGISTERGAMESERVER
			@param server_response: (bool) True if server accepts us, False if not
		'''