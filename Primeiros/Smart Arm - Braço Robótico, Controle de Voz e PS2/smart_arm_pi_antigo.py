# -*- coding: latin-1 -*-
import paho.mqtt.client as mqtt 

mqtt_broker_host = '192.168.1.15' #"127.0.0.1" 
mqtt_broker_port = 1883
mqtt_keepalive_secs = 60

subTopic = 'hiper'
pubTopic = 'smart_arm'

test_input = "lado direito"

direita =["direita","lado direito"]
esquerda =["esquerda","lado esquerdo"]
parar = ["parar","pare","chega","frear"]
cima = ["cima", "para cima","levantar","subir","sobe","suba"]
baixo = ["baixo", "para baixo", "abaix","desc"]
garra = ["pulso","garra","mão"]
base = ["base","braço"]
cotovelo =["meio, cotovelo"]
abrir = ["abr","solt"]
fechar = ["fech","trav","prend"]
continuar = ["continu","mais", "de novo","novamente"]
voltar = ["volt","menos","desfaz"]

last_msg_sent = ""


def publish(msg,topic=pubTopic):
	mqttc.publish(topic,msg,qos=0,retain=False) 

def on_message(mqttc, obj, msg):
	print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
	input=str(msg.payload)
	process(input)

def found(what,there):
	#Returns whether 'what' was found in 'there' or not

	if type(what)!=list:
		return (what in there)
	else:
		for i in what:
			if i in there:
				return True
	return False
	
def send(msg):
	print("Sending " + msg)
	publish(msg)
	last_msg_sent = msg

def process(input):
	print("Processing query:"+ input)
    #Assuming single word	
	if not ' ' in  input:
		if found(cima,input):
			send(">base.pitch(90)")
		elif found(baixo,input):
			send(">base.pitch(-90)")

	if found(continuar,input):
		send(last_msg_sent)
	elif found(esquerda,input):
		send(">base.yaw(-100)")
	elif found(direita,input):
		send(">base.yaw(100)")
	elif found(parar,input):
		send(">base.stop()")

	elif found(garra,input):
		if found(abrir,input):
			send(">drop()")
		elif found(fechar,input):
			send(">grip()")



mqttc = mqtt.Client()
mqttc.on_message = on_message
# Uncomment to enable debug messages
# mqttc.on_log = on_log
mqttc.connect(mqtt_broker_host, mqtt_broker_port, mqtt_keepalive_secs) 
mqttc.subscribe(subTopic, 0)

mqttc.loop_forever()
