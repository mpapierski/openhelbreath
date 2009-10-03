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
class Enum(object):
	"""
		Representing Enumerating type
		Usage:
			IncomingPackets = Enum({"GGRecvMsg":0x000a, "GGWelcome":0x0001})
	"""
	def __init__(self, enums = {}):
		self.__lookup = enums
		self.__reverse_lookup = {}
		for k, v in self.__lookup.iteritems():
			self.__reverse_lookup[v] = k
	
	def __getattr__(self, key):
		"""
			For using as described below:
				if zxcv == Enum.asdf: (...)
			Returns: value for 'key' element
		"""
		if not self.__lookup.has_key(key):
			raise AttributeError
		return self.__lookup[key]
	
	def reverse_lookup(self, value):
		"""
			Looking for key by value
			E.reverse_lookup(0x0001) - returns asdf
			Returns: key for element with 'value' value
		"""
		attributes = []
		for x in self.__reverse_lookup.keys():
			if int(x) & int(value):
				attributes.append(self.__reverse_lookup[x])
		return ",".join(attributes)
	
	def reverse_lookup_without_mask(self,value):
		if not self.__reverse_lookup.has_key(value):
			raise AttributeError(value)
		return self.__reverse_lookup[value]
	
	def __contains__(self, value):
		"""
			Checking if 'value' key is in Enum
			if 0x001 in E:
				[...]
		"""
		return self.__reverse_lookup.has_key(value)
		
	def items(self):
		return self.__lookup
