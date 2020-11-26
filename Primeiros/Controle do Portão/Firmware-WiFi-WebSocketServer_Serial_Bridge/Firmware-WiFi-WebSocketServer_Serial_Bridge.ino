#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <WebSocketsServer.h>
#include <Hash.h>
/*
***TROUBLESHOOTING
* Se não for possível conectar, mas a rede existir, abra a página de configuração e insira novamente as credenciais(ssid, pass) de sua rede
*/


const char* MY_NAME = "Portao";
const char* SSID = "Maicão";
const char* PASS = "1234567@8";

#define DEBUG true

WebSocketsServer webSocket = WebSocketsServer(81);

void setup(){
  Serial.begin(57600);
  
  WiFi.hostname(MY_NAME);
  
  WiFiManager wifiManager;
  wifiManager.autoConnect(SSID,PASS);
  
  if(DEBUG) Serial.print("Connected! IP address: ");
  if(DEBUG) Serial.println(WiFi.localIP());

 WiFi.softAP(SSID,PASS); 
 webSocket.begin();
 webSocket.onEvent(wsServerEvent);
}

void loop(){
  webSocket.loop();
}

void wsServerEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
        String data="";
        if(type==WStype_TEXT) {

                for (int i = 0; i < length; i++) data+= (char)payload[i];
                Serial.print(data);

        }
        else if(type== WStype_DISCONNECTED) {
                if (DEBUG) Serial.printf("[WSc] Disconnected!\n");
        }
        else if(type==WStype_CONNECTED)      {
                if (DEBUG) Serial.printf("[WSc] Connected to url: %s\n",  payload);

        }

}
