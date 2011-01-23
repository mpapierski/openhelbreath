from xapian import UnimplementedError
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
	CACHE = {}
	
	def __init__(self, attributes, endianess = '<', initial_data_list = [], **initial_data):
		import struct
		self.definition = attributes
		self.attributes = []
		self.endianess = endianess
		
		for attribute in attributes:
			if len(attribute) == 2:
				# Standard attribute
				key, format = attribute
				self.attributes.append(
					dict(
						type = 'attribute',
						key = key,
						format = format,
						value = initial_data.get(key)
					)
				)
			elif len(attribute) == 3:
				# Array
				key, listdef, count_key = attribute
				self.attributes.append(
					dict(
						type = 'array',
						count_key = count_key,
						key = key,
						format = listdef,
						value = initial_data.get(key)
					)
				)
		self.__initialised = True
		
	def __struct_factory(self, format):
		# Caching magic
		import struct
		if format not in Struct.CACHE:
			Struct.CACHE[format] = struct.Struct(format)
		return Struct.CACHE[format]
	
	def serialize(self, attributes_list = None):
		# Generate format according to defined attributes
		format = ''
		values = []
		
		if not attributes_list:
			attributes_list = self.attributes
			
		for attribute in attributes_list:
			if attribute['type'] == 'attribute':
				format += attribute['format']
				if attribute['format'][-1] == 'x':
					# Skip every padding value
					continue
				values.append(attribute['value'])
			elif attribute['type'] == 'array':
				times = None # How many times we should repeat array format
				
				if isinstance(attribute['count_key'], (basestring, )):
					count_attr, = filter(lambda a: a['key'] == attribute['count_key'], self.attributes)
					times = count_attr['value']
				else:
					times = attribute['count_key']
					
				#format += 
				(array_format, array_values) = self.serialize(attribute['format'].attributes)# * times
				format += array_format * times
				for array_value in attribute['value']:
					# Each array in struct-array
					values += array_value
				
		return (format, values)
		
	def pack(self):
		(format, values) = self.serialize()
		struct = self.__struct_factory(self.endianess + format)
		return struct.pack(*values)
	
	def unpack(self, buffer):
		format = '' # Temporary format for each data element
		
		data = []
		ref_list = [] # Reference to attributes
		
		for attribute in self.attributes + [{'type': 'array', 'format': None}]:
			if attribute['type'] == 'attribute':
				format += attribute['format']
				ref_list += [attribute]
				
			elif attribute['type'] == 'array':
				if format:
					struct_obj = self.__struct_factory(self.endianess + format)
					
					# Unpack set of data
					data_tmp = struct_obj.unpack(buffer[:struct_obj.size])

					# Cut unpacked data off the buffer
					buffer = buffer[struct_obj.size:]
					
					data.append(data_tmp) # Unpacked data sets
					
					format = ''
					
					for ref, unpacked_data in zip(ref_list, data_tmp):
						setattr(self, ref['key'], unpacked_data)
					
					ref_list = []
				
				if not attribute['format']:
					continue
				
				(array_format, array_value) = attribute['format'].serialize()
				
				# Compiled struct object for array element
				
				times = None # How many times decode array elements
				
				if isinstance(attribute['count_key'], (basestring, )):
					count_attr, = filter(lambda a: a['key'] == attribute['count_key'], self.attributes)
					times = count_attr['value']
				else:
					times = attribute['count_key']
				
				array = [] # Decoded array elements
				
				struct_obj = self.__struct_factory(self.endianess + array_format)
				while times:
					data_tmp = struct_obj.unpack(buffer[:struct_obj.size])
					buffer = buffer[struct_obj.size:]
					
					# Clean padding zeros from strings (if any)
					data_tmp = map(strip_zeros, data_tmp) 
					
					array.append(data_tmp)
					times -= 1
					
				data.append(array)
				
				setattr(self, attribute['key'], array)
				
		return data
		
		#if len(buffer) != self.size:
		#	raise struct.error, 'struct len %d, data size %d' % (len(buffer), self.size)
		
		#attributes = list(self.struct_obj.unpack(buffer))
		#for attribute in self.attributes:
		#	if attribute['format'][-1] == 'x':
		#		continue
		#	attribute['value'] = attributes.pop(0)
					
	def __getattr__(self, key):
		# Getting struct attribute
		try:
			attr, = filter(lambda a: a['key'] == key, self.attributes)
		except ValueError as e:
			raise AttributeError, key
		
		if attr['type'] == 'attribute':		
			if attr['format'][-1] == 's':
				return strip_zeros(attr['value']) # We dont want those \x00's
		
		return attr['value'] 
	
	def __setattr__(self, key, value):
		# Setting struct attribute
		
		if not self.__dict__.has_key('_Struct__initialised'):  # this test allows attributes to be set in the __init__ method
			return dict.__setattr__(self, key, value)
		try:
			attr, = filter(lambda a: a['key'] == key, self.attributes)
		except ValueError as e:
			raise AttributeError, key
		
		if attr['type'] == 'attribute':
			if attr['format'][-1] == 'x':
				raise AttributeError, key
			
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
		('value2', '4x'),
		('value3', '10s'))

	d = Struct(
		format,
		value1 = 666,
		value3 = 'dupa.8'
	)
	
	d2 = Struct(
		format,
	) 
	
	print 'packed %r' % d.pack()
	
	#d2.unpack(d.pack())
	#assert d2.value1 == d.value1
	#assert d2.value2 == d.value2
	#assert d2.value3 == d.value3
	
	
	# Struct array test
	item = Struct(
		(('id', 'b'),
		('name', '770s'),
		('attr', 'L'),
		('pad', '10x')))
	
	chargen = lambda:Struct(
		(('name', '10s'),
		('count', 'I'),
		('items', item, 'count'),
		('text', '15s'),
		)
	)
	
	
	char = chargen()
	
	char.name = 'drajwer'
	char.count = 3
	char.text = '12345'
	char.items = [[0, 'test1', 7777], [1, 'test2', 8888], [2, 'test3', 9999]]
	serialized = char.pack()
	
	char2 = chargen()
	
	print 'unpacked', char2.unpack(serialized)
	
	print 'decoded', char2.name, char2.count, char2.text, char2.count
	print 'items', char2.items
	assert char.name == char2.name
	assert char.count == char2.count
	print 't %r %r' % (char.text, char2.text)
	assert char.text == char2.text
	assert char.items == char2.items