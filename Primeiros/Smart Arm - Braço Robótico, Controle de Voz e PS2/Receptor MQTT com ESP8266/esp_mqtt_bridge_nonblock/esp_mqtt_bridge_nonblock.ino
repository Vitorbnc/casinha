//#include <ESP8266WiFi.h> // esp8266
#include <WiFi.h>
#include <PubSubClient.h>
//#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

HardwareSerial uart2(2);

// Update these with values suitable for your network.
const char* mqtt_server = "192.168.0.20";

const char* inTopic = "smart_arm";
const char* outTopic = "debug";

const char* ssid     = "MySSID";
const char* password = "12345678";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

String mqttData="";

void callback(char* topic, byte* payload, unsigned int length) {
//  if(debug) {
        //  String tmp=""; tmp+= "MQTT message received at topic "; tmp+=topic;
        //  uart.println(tmp);
        //  }
        mqttData ="";
        //currentTopic ="";
        //currentTopic+=topic;
        for (int i = 0; i < length; i++) {
                mqttData+=(char)payload[i];
        }
        uart2.print(mqttData);
        Serial.print(mqttData);
}

void reconnect() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(inTopic, "Device connected");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
    }
  }
}
void setup_wifi(){
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(250000);
  uart2.begin(250000, SERIAL_8N1, 16, 17);
  //uart2.begin(250000);
 
  
 setup_wifi();
    // WiFiManager wifiManager;
   //wifiManager.autoConnect("Smart Arm AP");

  client.setServer(mqtt_server, 1000);
  client.setCallback(callback);
}

char c;
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  /*
  if(uart2.available()){
     String s = uart2.readStringUntil('\n');
     Serial.println(s);
  }
  if(Serial.available()){
     String s = Serial.readStringUntil('\n');
     uart2.println(s);
  }
  */
  while(uart2.available()) {
    c = uart2.read();
    Serial.write(c);
    uart2.write(c); //echoing input
  }
  while(Serial.available()) uart2.write((char)Serial.read());
}
