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