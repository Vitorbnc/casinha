//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Enable/disable debug messages
#define DEBUG false


// Update these with values suitable for your network.
const char* ssid = "SSID";
const char* password = "PASS";
const char* mqtt_server = "iot.eclipse.org";
const int mqtt_port = 1883;

//topic to subscribe
const char* inTopic = "petcenter"; 
//topic to publish
const char* outTopic = "petcenter";

//Serial baud rate
const int baud = 115200;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  if (DEBUG) Serial.println();
  if (DEBUG) Serial.print("Connecting to ");
  if (DEBUG) Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (DEBUG) Serial.print(".");
  }

  if (DEBUG) Serial.println("");
  if (DEBUG) Serial.println("WiFi connected");
  if (DEBUG) Serial.println("IP address: ");
  if (DEBUG) Serial.println(WiFi.localIP());
}

//Will be called once a message is received
void callback(char* topic, byte* payload, unsigned int length) {
  if (DEBUG) Serial.print("Message arrived [");
  if (DEBUG) Serial.print(topic);
  if (DEBUG) Serial.print("] ");
  for (int i = 0; i < length; i++) {
     Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    if (DEBUG) Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      if (DEBUG) Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, "hello world");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      if (DEBUG) Serial.print("failed, rc=");
      if (DEBUG) Serial.print(client.state());
      if (DEBUG) Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(baud);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

//Not used, will send hello world every 2 secs
void sendTestMsg(){
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    if (DEBUG) Serial.print("Publish message: ");
    if (DEBUG) Serial.println(msg);
    client.publish(outTopic, msg);
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
