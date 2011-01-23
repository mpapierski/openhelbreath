import time

class TimerManager(object):
	def __init__(self):
		self.timers = []
	
	def invoke(self, name, function, delay_time, *args, **kwargs):
		# Delayed call
		if name is None:
			name = function.__name__
			
		self.timers += [
			dict(
				name = name,
				timer = False,
				timestamp = time.time(),
				function = function,
				delay_time = delay_time,
				args = args,
				kwargs = kwargs
			)
		]
		
	def register_timer(self, name, function, delay_time, *args, **kwargs):
		# Register continous timer
		if name is None:
			name = function.__name__

		self.timers += [
			dict(
				name = name,
				timer = True,
				timestamp = time.time(),
				function = function,
				delay_time = delay_time,
				args = args,
				kwargs = kwargs
			)
		]
		
	def process_all(self):
		# Process all timers
		t = time.time()
		for timer in self.timers:
			delta = t - timer['timestamp']
			if delta >= timer['delay_time']:
				timer['function'](*timer['args'], **timer['kwargs'])
				timer['timestamp'] = t
				if not timer['timer']:
					self.timers.remove(timer)
		
def test(msg):
	print msg
	
if __name__ == '__main__':
	t = TimerManager()
	t.register_timer('test msg', test, 1.0, msg = 'msg1')
	t.invoke('test', test, 2.0, msg = 'msg2')
	t.invoke('test', test, 3.0, msg = 'msg3')
	while True:
		t.process_all()
		time.sleep(0.5)
		