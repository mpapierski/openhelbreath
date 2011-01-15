strip_zeros = lambda data: \
	(data[:data.index('\x00')] if '\x00' in data else data) \
		if isinstance(data, basestring) else \
	data

if __name__ == '__main__':
	# Ensure that zeros will be always strip'd
	assert strip_zeros('openhelbreath\x00\x00\x00\x00') == 'openhelbreath'
	assert strip_zeros('openhelbreath') == 'openhelbreath'
	assert strip_zeros(1325) == 1325