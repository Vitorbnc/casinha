# -*- coding: latin-1 -*-
import paho.mqtt.client as mqtt
import json

mqtt_broker_host = '192.168.1.15'  # "127.0.0.1"
mqtt_broker_port = 1883
mqtt_keepalive_secs = 60

subTopic = 'hiper'
buffer = ""
filePath = "log.txt"


def on_message(mqttc, obj, msg):
    #print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    #raw_in = str(msg.payload).replace('\0', '').replace('\'','\"')
    #json_in = json.loads(raw_in,encoding='latin-1')
    #data = json_in["stt"]
    data =(msg.payload).decode('utf-8')
    #print(data)
    data+='\n'
    global buffer
    buffer = buffer + data
    with open(filePath,'a') as f:
        f.write(data)
    with open(filePath) as f:
        print("------------------------- \n")   
        print(f.read())
	

def found(what,there):
	#Returns whether 'what' was found in 'there' or not

	if type(what)!=list:
		return (what in there)
	else:
		for i in what:
			if i in there:
				return True
	return False
	



mqttc = mqtt.Client()
mqttc.on_message = on_message
# Uncomment to enable debug messages
# mqttc.on_log = on_log
mqttc.connect(mqtt_broker_host, mqtt_broker_port, mqtt_keepalive_secs) 
mqttc.subscribe(subTopic, 0)

mqttc.loop_forever()
