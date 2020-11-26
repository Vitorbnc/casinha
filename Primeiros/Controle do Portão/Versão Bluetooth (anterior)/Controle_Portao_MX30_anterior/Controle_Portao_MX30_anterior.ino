#include <SoftwareSerial.h>

//PIN do bluetooth: 1119


//Hardware pins

//Fake button press output
const int relay = 3;

//Closed sensor, active low
const int sw_closed = 6;

const int led = 13;

const int bt_disable = 9;

SoftwareSerial bluetooth(11, 10); // RX, TX

//--------
//Protocol: 
//  {xxx} - xxx is the desired command
// Implemented:
//  {btn} - fake button press
//  {kal} - keep-alive
//  {ace} - auto close enabled
//  {acd} - auto close disabled
//--------

//Keep alive wait time
const int KEEPALIVE_TIME = 6000; 
const int DATA_SIZE = 8;

//Incoming serial data buffer 
char buffer[DATA_SIZE];

//Last keep alive check time
unsigned long lastKeepAliveTime;

bool gotKeepAlive = false;
bool useAutoClose = false;
bool btRestarted = false;


void setup(){
  //115200 was error prone with software serial
  bluetooth.begin(57600);
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(sw_closed,INPUT);
  pinMode(bt_disable,OUTPUT);
  digitalWrite(bt_disable,LOW);
}

void fakeButton(){
  digitalWrite(relay,HIGH);
  delay(333);
  digitalWrite(relay,LOW);
}

void serialBridge(){
  while(bluetooth.available())
  Serial.write(bluetooth.read());
    
  while(Serial.available())
  bluetooth.write(Serial.read());
}

void blinkLed(){
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}

void autoResetBt(){
  if(gotKeepAlive or btRestarted)
    return;
  else{
    digitalWrite(bt_disable,HIGH);
    delay(1000);
    digitalWrite(bt_disable,LOW);
    btRestarted = true;
  }
}

void autoClose(){
  
  bool closed = !digitalRead(sw_closed);

  if(closed)
    useAutoClose = false;
   
  else if(useAutoClose and !gotKeepAlive){
    fakeButton();
    useAutoClose = false;
  }
 
}

//--------
//Protocol: 
//  {xxx} - xxx is the desired command
// Implemented:
//  {btn} - fake button press
//  {kal} - keep-alive
//  {ace} - auto close enabled
//  {acd} - auto close disabled
//--------
void handleData(){
  
  //int strncmp ( const char * str1, const char * str2, size_t num );
    //return 0 if there's an exact match
    if(strncmp(buffer,"btn",3)==0)
      fakeButton();
      
    else if(strncmp(buffer,"kal",3)==0){
      gotKeepAlive = true;
      btRestarted = false;
      lastKeepAliveTime = millis(); 
    }
    else if(strncmp(buffer,"ace",3)==0){
      useAutoClose = true;
    }
    else if(strncmp(buffer,"acd",3)==0){
      useAutoClose = false;
    }

    //Clear buffer
    for(char i:buffer)
      i=' '; 
    
}
void loop(){
    //serialBridge();
    
    //Serial.readBytesUntil(character, buffer, length)
    if(bluetooth.read()=='{'){
      bluetooth.readBytesUntil('}',buffer,DATA_SIZE);
      Serial.println(buffer);
      handleData();
    }
              
    if(millis()-lastKeepAliveTime>KEEPALIVE_TIME)
      gotKeepAlive = false; 
      
    autoClose();
    autoResetBt();
     
}

