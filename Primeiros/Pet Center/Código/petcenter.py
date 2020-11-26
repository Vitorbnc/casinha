from flask import Flask, render_template
from flask_ask import Ask, statement, question, session 
import requests
import json
import paho.mqtt.client as mqtt 

app = Flask(__name__)
ask = Ask(app,'/')

mqtt_broker_host = 'iot.eclipse.org' #"127.0.0.1"
mqtt_broker_port = 1883
mqtt_keepalive_secs = 60

mqtt_default_topic = 'petcenter'

# The callback for when the client receives a CONNACK response from the mqtt server. 
def on_connect(client, userdata, flags, rc): 
	print("Connected with result code "+str(rc)+'\n') 

def quick_pub(msg,topic):
	#client = mqtt.Client(transport="websockets") 
	client = mqtt.Client()
	client.on_connect = on_connect 
	client.connect(mqtt_broker_host, mqtt_broker_port, mqtt_keepalive_secs) 
	client.publish(topic,msg,qos=0,retain=False) 
	client.disconnect() 

@ask.launch 
def petcenter_launch(): 
   welcome_msg = render_template("welcome") 
   return question(welcome_msg).reprompt(welcome_msg)


@ask.intent("feed") 
def petcenter_feed(pet_type):
	if pet_type == None:
		pet_type = "pet"
	print("Feeding a : " + str(pet_type) +' right now \n')
	quick_pub('{\'cmd\':\'feed\'}',mqtt_default_topic) 
	msg = render_template("feed_response") 
	return statement(msg) 
    

@ask.intent("play")
def petcenter_play(pet_type):
	if pet_type == None:
		pet_type = "pet"
	print("Entertaining a : " + str(pet_type) +" right now \n")
	quick_pub('{\'cmd\':\'play\'}',mqtt_default_topic)
	msg = render_template("play_response", pet_type = pet_type)
	return statement(msg) 


@ask.intent('AMAZON.HelpIntent')
def help():
    help_text = render_template('help')
    return question(help_text).reprompt(help_text)


@ask.intent('AMAZON.StopIntent')
def stop():
    bye_text = render_template('bye')
    return statement(bye_text)


@ask.intent('AMAZON.CancelIntent')
def cancel():
    bye_text = render_template('bye')
    return statement(bye_text)


@ask.session_ended
def session_ended():
    return "{}", 200


if __name__ == "__main__": 
    app.run(debug=True) #default is localhost, port is 5000

	#app.run(debug=True,ssl_context='adhoc') #this will run with https
	#app.run(host='0.0.0.0') #this will make app visible to external requests
	#app.run(debug=True,port=80)  