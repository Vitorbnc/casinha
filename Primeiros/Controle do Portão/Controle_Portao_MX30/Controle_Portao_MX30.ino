#include <SoftwareSerial.h>
#include <CircularList.h>
//PIN do bluetooth: 1119
/*
 * TROUBLESHOOTING
 * Gate opens after manually closed when autoclose is enabled -> check the closure sensor, make sure its magnet is in place
 * For network problems, see the WiFi code 
 */


//Hardware pins

//Fake button press output
const int relay = 3;

//Closed sensor, active low
const int sw_closed = 6;

const int led = 13;

const int net_enable = 4;

SoftwareSerial net(11, 10); // RX, TX


CircularList<String> idList(5);

String cmd="";
String id="";


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
/*
const int CMD_SIZE = 8;
const int ID_SIZE = 37;
*/
//Incoming serial data buffers
/*
char cmd_buffer[CMD_SIZE];
char id_buffer[ID_SIZE];

*/

//Last keep alive check time
unsigned long lastKeepAliveTime;

//Auto reset net every 5 min 
const unsigned long NET_RESTART_TIME = 1000*60*5; // was 2 min

unsigned long lastNetRestartTime;

bool gotKeepAlive = false;
bool useAutoClose = false;
bool netRestarted = false;


void setup(){
  //115200 was error prone with software serial
  net.begin(57600);
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(sw_closed,INPUT);
  pinMode(net_enable,OUTPUT);
  digitalWrite(net_enable,HIGH);
}

void fakeButton(){
  digitalWrite(relay,HIGH);
  delay(333);
  digitalWrite(relay,LOW);
}

void serialBridge(){
  while(net.available())
  Serial.write(net.read());
    
  while(Serial.available())
  net.write(Serial.read());
}

void blinkLed(){
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}

void autoRestartNet(){
  if(gotKeepAlive or netRestarted)
    return;
  else{
    Serial.println("Restarting Network");
    digitalWrite(net_enable,LOW);
    delay(2000);
    digitalWrite(net_enable,HIGH);
    netRestarted = true;
    lastNetRestartTime = millis();
  }
}

void autoClose(){
  //Serial.println("AutoClose routine");
  bool closed = !digitalRead(sw_closed);
  
  //Serial.println("Gate is "+ closed? "closed":"open");
  //Serial.println(closed);

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
//  {ace} - auto close enabled ---  deprecated
//  {acd} - auto close disabled  ---- deprecated
//--------
void handleData(String data){
  int sepIndex = data.indexOf(':');
  if(sepIndex==-1) return;
 
  cmd="";
  id="";

  cmd = data.substring(0,sepIndex);
  id = data.substring(sepIndex+1);

  
  idList.insert_unique(id);
  if(id!=idList.last_unique_insertion())
    return;
  
  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(" , ");
  Serial.print("id: ");
  Serial.println(id);
  
  //int strncmp ( const char * str1, const char * str2, size_t num );
    //return 0 if there's an exact match
    if(strncmp(cmd.c_str(),"btn",3)==0)
      fakeButton();
      
    else if(strncmp(cmd.c_str(),"kal",3)==0){
      gotKeepAlive = true;
      netRestarted = false;
      lastKeepAliveTime = millis(); 
    }
    else if(strncmp(cmd.c_str(),"ace",3)==0){
      useAutoClose = true;
    }
    else if(strncmp(cmd.c_str(),"acd",3)==0){
      useAutoClose = false;
    }

    //Clear buffer
    /*
    for(char i:cmd_buffer)
      i=' '; 
    for(char i:id_buffer)
      i=' ';
*/
    
}
String data;
void loop(){
    //serialBridge();
    
    //Serial.readBytesUntil(character, cmd_buffer, length)
    if(net.available()){
      char c = net.read();
      if(c=='{'){
        data="";
        data+= net.readStringUntil('}');
        Serial.println(data);
        handleData(data);
      }
    }
              
    if(millis()-lastKeepAliveTime>KEEPALIVE_TIME)
      gotKeepAlive = false; 

    if(netRestarted and millis()-lastNetRestartTime>NET_RESTART_TIME)
      netRestarted = false;
      
    autoClose(); //Be careful
    autoRestartNet(); // Periodically restarting prevents bugs
     
}
