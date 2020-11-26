import os
from random import randint
commands_path = 'data/commands.txt'
commands_path = os.path.join(os.path.dirname(__file__), commands_path)

utterances_path = 'data/utterances.md'
utterances_path = os.path.join(os.path.dirname(__file__), utterances_path)


last_hw_intent = "stop"


def load_cmds():
	intents = []
	cmds = []
	# Take special care with files or strings containing accents or characters like 'Ã§'. Open in binary mode and decode them with byte_array_object.decode('utf-8')
	with open(commands_path, 'r+b') as f:
		for line in f:
			line = line.decode('UTF-8')
			x, y = line.replace('\n', '').replace('\r', '').split(';')
			intents.append(x.lower())
			cmds.append(y)
		return(intents, cmds)


hardware_intents, cmds = load_cmds()
# print(intents)
# print(cmds)


def get_cmd(intent):
	global last_hw_intent
	last_hw_intent = intent
	cmd = cmds[hardware_intents.index(intent)]
	return cmd


def get_opposite(input):
	intent = input
	if 'left' in input:
		intent = input.replace('left', 'right')
	elif 'right' in input:
		intent = input.replace('right', 'left')
	elif 'up' in input:
		intent = input.replace('up', 'down')
	elif 'down' in input:
		intent = input.replace('down', 'up')
	elif 'close' in input:
		intent = input.replace('close', 'open')
	elif 'open' in input:
		intent = input.replace('open', 'close')
	
	return intent

def load_utterances():
	utterances = {}
	# Take special care with files or strings containing accents or characters like 'Ã§'. Open in binary mode and decode them with byte_array_object.decode('utf-8')
	with open(utterances_path, 'r+b') as f:
		key =''
		for line in f:
			line = line.decode('UTF-8').lower()
			print(line)
			if '#' in line:
				key = line.replace('#','').replace('\n', '').replace('\r', '').replace(' ','')
				utterances[key] = []
			else:
				utterances[key].append(line.replace('\n', '').replace('\r', ''))
		return(utterances)

utterances = load_utterances()

def get_random_utterance(label):
	i = randint(0,len(utterances[label])-1)
	return utterances[label][i]