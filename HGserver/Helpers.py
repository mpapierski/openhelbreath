strip_zeros = lambda data: \
	(data[:data.index('\x00')] if '\x00' in data else data) \
		if isinstance(data, basestring) else \
	data

class Array2d():
	def __init__(self, (w, h)):
		self.a={}
		self.w = w
		self.h = h
		
	def __getitem__(self, v):
		assert isinstance(v, tuple)
		(x,y) = v
		return self.a[x][y]
		
	def __setitem__(self, key, v):
		assert isinstance(key, tuple)
		if key >= (self.w, self.h):
			raise IndexError, 'list index out of range'
		(x,y) = key
		if x not in self.a:
			self.a[x]={}
		self.a[x][y]=v
		
class Struct(object):
	attributes = []
	endianess = '<'
	
	def __init__(self, attributes, endianess = '<'):
		import struct
		self.attributes = []
		self.endianess = endianess
		
		struct_format = endianess
		
		for key, format in attributes:
			self.attributes.append(
				dict(
					key = key,
					format = format,
					value = None
				)
			)
			struct_format += format
								
		
		# TODO: as struct.Struct is compiled here
		# we should have a little factory here
		# which caches all struct.Struct instances
		
		self.struct_obj = struct.Struct(struct_format)
		self.__initialised = True
		
	size = property(lambda self: self.struct_obj.size)
	
	def pack(self):
		return self.struct_obj.pack(*map(lambda a: a['value'], self.attributes))
	
	def unpack(self, buffer):
		if len(buffer) != self.size:
			raise struct.error, 'struct len %d, data size %d' % (len(buffer), self.size)
		
		attributes = self.struct_obj.unpack(buffer)
		for attribute, new_value in zip(self.attributes, attributes):
			attribute['value'] = new_value
				
		
	def __getattr__(self, key):
		try:
			attr, = filter(lambda a: a['key'] == key, self.attributes)
		except ValueError as e:
			raise AttributeError, key
		
		if attr['format'][-1] == 's':
			return strip_zeros(attr['value'])
		
		return attr['value'] 
	
	def __setattr__(self, key, value):
		if not self.__dict__.has_key('_Struct__initialised'):  # this test allows attributes to be set in the __init__ method
			return dict.__setattr__(self, key, value)
		try:
			attr, = filter(lambda a: a['key'] == key, self.attributes)
		except ValueError as e:
			raise AttributeError, key
		
		# TODO: format and value type check
		
		attr['value'] = value
		
if __name__ == '__main__':
	# Ensure that zeros will be always strip'd
	assert strip_zeros('openhelbreath\x00\x00\x00\x00') == 'openhelbreath'
	assert strip_zeros('openhelbreath') == 'openhelbreath'
	assert strip_zeros(1325) == 1325
	
	t = Array2d((100, 100))
	t[0,0] = 100
	t[99, 99] = 100
	ok = True
	try:
		t[100, 100] = 100
		t[100, 100] += 100
	except IndexError as e:
		ok = False
		
	assert not ok
	
	format = (('value1', 'I'),
		('value2', 'I'),
		('value3', '10s'))

	d = Struct(
		format
	)
	print 'size', d.size
	
	d.value1 = 31337
	d.value2 = 69
	d.value3 = 'dupa.8'

	d2 = Struct(
		format
	) 
	
	d2.unpack(d.pack())
	
	assert d2.value1 == d.value1
	assert d2.value2 == d.value2
	assert d2.value3 == d.value3