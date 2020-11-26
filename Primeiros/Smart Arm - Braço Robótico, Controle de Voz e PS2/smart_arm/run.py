import paho.mqtt.client as mqtt 
import data
import os
import numpy as np
import classifier
import actions as act
import json

mqtt_broker_host = '127.0.0.1' #"127.0.0.1" 
mqtt_broker_port = 1000
mqtt_keepalive_secs = 60

subTopic = 'hiper'
pubTopic = 'smart_arm'

last_msg_sent = ""
ignore_next_input = False

appId = ""

def publish(msg,topic=pubTopic):
	global ignore_next_input
	mqttc.publish(topic,msg,qos=0,retain=False)
	if topic==subTopic:
		ignore_next_input = True

'''
def on_message(mqttc, obj, msg):
	global ignore_next_input
	if ignore_next_input:
		ignore_next_input = False
		return
	#print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
	input=msg.payload.decode('UTF-8')
	process(input)
'''
#mqtt callback, called upon mqtt message arrival
def on_message(mqttc, obj, msg):
	global ignore_next_input
	if ignore_next_input:
		ignore_next_input = False
		return
	#msg is binary, we'll decode it with accent support 
	payload=msg.payload.decode('utf-8')
	print(payload)
	#Important! Forgetting quotes will raise JSONDecodeError: Expecting value
	j = json.loads(payload)

	if not "appId" in j:
		return
	global appId
	appId = j["appId"]
	process(payload,j)



def found(what,there):
	#Returns whether 'what' was found in 'there' or not

	if type(what)!=list:
		return (what in there)
	else:
		for i in what:
			if i in there:
				return True
	return False


def send(msg,topic=pubTopic):
	print("Sending " + msg)
	publish(msg,topic)
	if("stop" in msg): return
	global last_msg_sent
	last_msg_sent = msg

def sendTTS(msg,topic=subTopic):
	response = {"tts":msg,"appId":appId}
	#generate json-fortmatted str from python dict
	global last_msg_sent
	last_msg_sent = msg
	j = json.dumps(response)
	publish(j,topic)


def send_reversed(intent):
	if len(intent)<3:
		return
	else:
		send(act.get_cmd(act.get_opposite(intent)))

def process_user_cmd(cmd):
	if(cmd=="stop"): send(act.get_cmd("stop"))



def process(input,json_input):
	#simple filter
	if len(input.replace(' ',''))<2:
		return

	print("Processing query:"+ str(input))

	if("cmd" in json_input):
		process_user_cmd(json_input["cmd"])
		return

	if("stt" in json_input):
		input = json_input["stt"]
	else:
		return

	intent = classifier.predict(input)

	if intent =='repeat':
		#sendTTS(last_msg_sent,appId)
		send(last_msg_sent)

	elif intent =='reverse':
		send_reversed(act.last_hw_intent)
	
	if intent in act.utterances.keys():
		txt=act.get_random_utterance(intent)
		j = '{\"tts\":\"'+txt+'\"}'
		#publish(j,subTopic)
		sendTTS(txt)

	if intent in act.hardware_intents:
		send(act.get_cmd(intent))


def on_connect():
	publish('{\"tts\":\"Bem-vindo de volta, senhor!\"}',subTopic)

if __name__=='__main__':
	mqttc = mqtt.Client()
	mqttc.on_message = on_message
	# Uncomment to enable debug messages
	# mqttc.on_log = on_log
	mqttc.connect(mqtt_broker_host, mqtt_broker_port, mqtt_keepalive_secs)
	#mqttc.on_connect = on_connect
	mqttc.subscribe(subTopic, 0)

	#process(5)

	mqttc.loop_forever()
