//#include <Arduino.h>  // not necessary
// Vitor Barbosa
/* Código para o NodeMCU, versão testada usa o ESP-12F
IMPORTANTE : Teste a correspondência entre os pinos do código e da placa, a numeração pode ser confusa
*/

// comentar print da valocidade em accelerateCallback

//-------------------------------------------

#include <ESP8266WiFi.h>


#include <Streaming.h>
#include <Servo.h>

#include <Thread.h>
#include <ThreadController.h>


ThreadController thrController = ThreadController();
Thread thrAccelerate;


 #define debug false  // turn debug message on or off in serial
 #define usb Serial
 #define arm Serial
 #define bluetooth Serial
 #define wifi Serial

const char* ssid     = "things";
const char* password = "";

const char* host = "192.168.1.1";
const int port = 23;

  WiFiClient client;


char source; // char to define from which stream message came

// nodemcu onboard led
const int LED_ONBOARD = 2; // this is pin D4
bool wifiOK = false;


// thread callback state variables
long interval_accelerator = 250; // was 500
const int joyAcceleratorTrig = 64;

int absAcceleration = 4; // was 1
int currentSpeed=0;



const int PIN_ESC =D8; // constantes dos pinos dos servos
const int PIN_REV = D7; // pino do relé da ré

const int PIN_STEERING=D6;
//const int sonarServo_pin = 5;




const int defaultInterval = 500;



const int joySet[]={0,255};
const int joyMid = (joySet[0]+joySet[1])/2;
const int deltaJoySet[]={0,128};



int arm_steps = 30;
int arm_stepsInterval=15;

int arm_angleStep = 3;
int arm_angleStepInterval = 60;

bool arm_isHolding =false;
bool arm_fanIsRunning = false;
int arm_currentPitchMotor = 0;

//------------------------------------
struct intTuple {
        int data[4];
        intTuple(int a, int b){
                data[0] =a; data[1] =b;
        }
        intTuple(int a, int b, int c){
                data[0] =a; data[1] =b;
                data[2]=c;
        }
        intTuple(int a, int b, int c,int d){
                data[0] =a; data[1] =b;
                data[2]=c; data[3]=d;
        }


};
//  -----------------------------------------------------------------------
class Fasterpreter {

protected:
const static int dirCount=3;  // Set your number of dirs here
const static int argCount=3;  //Set your number of args here
char header;
char trailer;

public:
char source;
String dir[dirCount];
String strArg[argCount];
int intArg[argCount];
bool hasStrArg[argCount];
bool hasIntArg[argCount];
// Use the following if you want to check for args, commands or forwardables
bool hasArgs=false;
bool gotCmd=false;
bool gotFwd = false;
bool shouldPrintData = false;
String forwardable;
String cmd;

// constructor here
Fasterpreter(){
        header = '>';
        trailer = ')';
        cleanInterpreter();
}
Fasterpreter( char head, char trail){
        header = head;
        trailer = trail;
        cleanInterpreter();
}

void readStream(HardwareSerial* inStream,char src ='u'){
        if(inStream->available()) {
                // inStream->read(); is equivalent to *inStream.read()  ------ reads "value pointed to by inStream", it gets the value pointed by the pointer, not its address
                char c = inStream->read();
                if(c==header) {
                        String serialTxt = inStream->readStringUntil(trailer);
                        serialTxt+=trailer;
                        //usb.println(serialTxt);
                        source = src;
                        parse(serialTxt);
                }
                // if you don't want forwardables feature, just comment the lines below
                /*
                   else if (c=='\"') {
                        gotFwd=true;
                        forwardable= inStream->readStringUntil('\"');
                        // use forwardable here
                   }
                 */
        }
}

void printData(){
        for(int i=0; i<dirCount; i++) {
                usb.print("dir "); usb.print(i); usb.print(":");
                usb.println(dir[i]);
        }
        for(int i=0; i<argCount; i++) {
                if(hasStrArg[i]) {
                        usb.print("strArg "); usb.print(i); usb.print(":");
                        usb.println(strArg[i]);
                }
                else {
                        usb.print("Has no strArg "); usb.print(i);
                }
                if(hasIntArg[i]) {
                        usb.print("intArg "); usb.print(i); usb.print(":");
                        usb.println(intArg[i]);
                }
                else{
                        usb.print("Has no intArg "); usb.print(i);
                }
        }
}


void cleanInterpreter(){
        gotFwd=false;
        gotCmd=false;
        //forwardable="";
        /* // clean dirs only if necessary
           for(int i=0;i<dirCount;i++){
           dir[i]="";
           }
         */
        for(int i=0; i<argCount; i++) {
                //intArg[i]=0;
                //strArg[i]=""; // clean String Arguments only if necessary
                hasStrArg[i]=false;
                hasIntArg[i]=false;
        }
}


void  parseArgs(String rawTxt){
        // parses the function arguments. E.g.:(100,10,-25)
        String tmp;
        int old_commaIndex =-1;
        bool oneMore = true;
        for(int i=0; i<argCount; i++) {
                int commaIndex = rawTxt.indexOf(',',old_commaIndex+1);
                if(commaIndex!=-1) {
                        tmp= rawTxt.substring(old_commaIndex+1,commaIndex);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-'&& c!='+') {
                                strArg[i] = tmp;
                                hasStrArg[i] = true;
                        }
                        else {
                                intArg[i] = tmp.toInt();
                                hasIntArg[i] = true;
                        }

                        old_commaIndex = commaIndex;
                }
                else if(oneMore) {
                        oneMore=false;
                        tmp = rawTxt.substring(old_commaIndex+1);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-'&& c!='+') {
                                /*
                                   // removes the last ')', using length()-1 because the index starts at 0
                                   tmp.remove(tmp.length()-1);
                                 */
                                hasStrArg[i] = true;
                                strArg[i] = tmp;
                        }
                        else {
                                intArg[i] = tmp.toInt();
                                hasIntArg[i] = true;
                        }

                }
        }

}


void  parse(String fullTxt){
        //Eg.: >car.go(100,100,20)
        //>car.turn(10)
        //display.show(lalalal)
        //Obs.: fullTxt must already be without '>', use '>' to detect a command in the desired data stream before calling this.
        gotCmd=true;
        int argStartIndex =  fullTxt.indexOf('(');
        int argEndIndex = fullTxt.indexOf(trailer);
        String rawTxt = fullTxt.substring(0,argStartIndex);

        int old_dotIndex =-1;
        bool oneMore = true;
        for(int i=0; i<dirCount; i++) {
                int dotIndex = rawTxt.indexOf('.',old_dotIndex+1);
                if(dotIndex!=-1) {
                        dir[i] = rawTxt.substring(old_dotIndex+1,dotIndex);
                        old_dotIndex = dotIndex;
                }
                else if(oneMore) {
                        dir[i] = rawTxt.substring(old_dotIndex+1);
                        oneMore =false;
                }
                else dir[i] = "";

        }

        // if there are no arguments, just skip to Interpreter. E.g.: led.red()
        if(argStartIndex+1==argEndIndex) {
                hasArgs=false;
                interpret();
        }
        else {
                String justArgs = fullTxt.substring(argStartIndex+1,argEndIndex);
                hasArgs=true;
                parseArgs(justArgs);
                interpret();
        }
}



// This has to be defined later
void interpret();

};
//----------------- end of Fasterpreter class

class Steering {
protected:
Servo turnServo;
public:
const int ll_turnSet[2]={130,65};
const int angleSet[2] ={180,0};
int ll_midAngle=(ll_turnSet[0]+ll_turnSet[1])/2;
void init(int pin){
        turnServo.attach(pin);
        turnServo.write(ll_midAngle);//ângulo mínimo de 65, médio de 100, máximo de 135

}


void turn(int x,const int valueSet[2]){
        int turnvalue;
        turnvalue = map(x,valueSet[0],valueSet[1],ll_turnSet[0],ll_turnSet[1]);
        turnServo.write(turnvalue);
}

void turn(int x){
        int turnvalue;
        turnvalue = map(x,angleSet[0],angleSet[1],ll_turnSet[0],ll_turnSet[1]);
        turnServo.write(turnvalue);
}

};

class Engine {
protected:
Servo accel;    // create servo object to control a servo
bool reversed = false;   // modo ré
int revpin;
// using ll_ for low level, hardware-specific or tuned values
const int defaultSpeedSet[2]={-100,100};
//const int deltaSpeedSet[]={0,100};
const int ll_zeroSpeedPulse = 800;    // was 800
const int escPulseSet[2]={980,1600};    // was 800,1800, 800 is zero Speed


void reverse(bool rev){
        if(rev) {
                reversed=true;
                digitalWrite(revpin,HIGH);
        }
        else{
                reversed=false;
                digitalWrite(revpin,LOW);
        }
}

void armESC(){
        // arm the speed controller, modify as necessary for your ESC
        setSpeed(0);
        delay(1000);   //delay 1 second,  some speed controllers may need longer
}


public:
int lastSpeed;
int minMotionSpeed = 5; // was 4 or 5
int accelIsPositive = true;
bool canMoveForward = true;
bool canMoveBackward = true;

void init(int PIN_ESC, int PIN_REV){
        revpin = PIN_REV;
        pinMode(revpin, OUTPUT); // inicializa pino do relé da ré
        accel.attach(PIN_ESC,800,1800); // attaches the esc to its pin

        armESC();
}

void brake(){
                accel.writeMicroseconds(ll_zeroSpeedPulse);
                thrAccelerate.enabled=false;
                if(debug) usb.println("zero speed");
                lastSpeed =0;
        }
void fastBrake(){ // reverse polarity for fast braking
  if(lastSpeed>0) {
    reverse(true);
    delay(100);
    brake();
  //  reverse(false);
  }
  else if(lastSpeed<0){
     reverse(false);
     delay(100);
     brake();
     //reverse(true);
   }


}

void accelerate(int sign){
        if(sign==0) brake();
        else {
                if(!thrAccelerate.shouldRun()) {
                        if(sign<0&&canMoveBackward) {
                                accelIsPositive = false;
                                lastSpeed = minMotionSpeed* -1;
                        }
                        else if (sign>0&&canMoveForward) {
                                accelIsPositive = true;
                                lastSpeed = minMotionSpeed;
                        }
                        thrAccelerate.setInterval(interval_accelerator);
                        thrAccelerate.enabled=true;
                }
        }
}


void setSpeed(int speed){
        // speed is from 0 to 100 where 0 is off and 100 is maximum speed
        //the following maps speed values of +- (0-100) to pulses from 800uS to 1800uS
        // some speed controllers may need different values, see the ESC instructions

        // delays between steps: 500 is a good value
        //currentSpeed = speed;
        int pulseWidth;
        int midSpeed= 0;
        if(speed<midSpeed) {
                if(!canMoveBackward)  speed=0;

                else reverse(true);
        }

        else if(speed>midSpeed) {
                if(!canMoveForward) speed=0;
                else  reverse(false);// check both sides to prevent sudden braking
        }
        int trigSpeed = 2;
        int absDeltaSpeed = abs(speed-0);

        if(absDeltaSpeed<trigSpeed) {
                accel.writeMicroseconds(ll_zeroSpeedPulse);
                thrAccelerate.enabled=false;
                if(debug) usb.println("zero speed");
                lastSpeed =0;
        }
        else{
                //  int speedChange = speed-lastSpeed;

                pulseWidth = map(absDeltaSpeed, 0, 100, escPulseSet[0], escPulseSet[1]);

                /*
                        if(debug) usb.println(midSpeed);
                        if(debug) usb.println(absDeltaSpeed);
                        if(debug) usb.println(pulseWidth);

                 */
                accel.writeMicroseconds(pulseWidth);
                lastSpeed = speed;
                if(debug) usb.println(speed);
                if(debug) usb.println(pulseWidth);
        }
}

void setSpeed(int speed, const int speedSet[2]){
        // flexible set speed function, works with any given values set
        // some speed controllers may need different values, see the ESC instructions

        // delays between steps: 500 is a good value
        int pulseWidth;
        int midSpeed= (speedSet[1]+speedSet[0])/2;
        int trigSpeed = abs(speedSet[1]-midSpeed)/26;
        int deltaSpeed = (speed-midSpeed);
        if(speed<midSpeed) reverse(true);
        else  reverse(false);

        if(abs(deltaSpeed)<trigSpeed) {
                accel.writeMicroseconds(ll_zeroSpeedPulse);
                thrAccelerate.enabled=false;
                if(debug) usb.println("zero speed");

        }
        else{
                //  int speedChange = speed-lastSpeed;

                pulseWidth = map(abs(deltaSpeed), 0, abs(speedSet[1]-midSpeed), escPulseSet[0], escPulseSet[1]);


                if(debug) usb.println(midSpeed);
                if(debug) usb.println(deltaSpeed);
                if(debug) usb.println(pulseWidth);
                accel.writeMicroseconds(pulseWidth);
                lastSpeed = speed;

        }

}



}; // end of Engine -------------------------------------------------------

// ---------------------------- end of AI
Steering steering;
Fasterpreter interpreter;
Engine engine;

void setupWifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
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

void  readWifi(){
if(client.available()){
    char c = client.read();
    if(c=='>'){
     String tcpTxt = client.readStringUntil(')');
     tcpTxt+=')';
     interpreter.parse(tcpTxt);
     String printable = ">";
     printable+=tcpTxt;
     usb.println(printable);
    }
    
  }
}

  void reconnect(){
  // Use WiFiClient class to create TCP connections
      if(!client.connected()){
        Serial.println("Connecting");
        while (!client.connect(host, port)) {
       Serial.print(".");
        }
      }
  }


void accelerateCallback(){
        int speed;
        if(engine.accelIsPositive)
                speed = engine.lastSpeed+absAcceleration;
        else speed = engine.lastSpeed-absAcceleration;

        engine.setSpeed(speed);
        if(debug) usb.println(speed);

}

void setupThreads(){
        thrAccelerate.onRun(accelerateCallback);

        thrAccelerate.enabled=false;

        thrController.add(&thrAccelerate);
}


void sendAnswer(String txt){
  switch(interpreter.source){
    case 'b':
    bluetooth.println(txt);
    break;
    case 'u':
    usb.println(txt);
    break;
    case 'w':
  wifi.println(txt);
    break;

  }

}


void setup()
{
        steering.init(PIN_STEERING);
        engine.init(PIN_ESC,PIN_REV);

        setupWifi();
        usb.begin(115200);

        usb.println("Iniciando...");

        pinMode(LED_ONBOARD,OUTPUT);
        digitalWrite(LED_ONBOARD,LOW);
        setupThreads();

}




void loop()
{
        thrController.run();
        
       /* interpreter.readStream(&wifi,'w');
        interpreter.readStream(&bluetooth,'b');
        interpreter.readStream(&usb,'u');
        */
        readWifi();
        reconnect();

}

   void blinkOK(){
        for(int i=0; i<2; i++) {
                digitalWrite(LED_ONBOARD,HIGH);
                delay(300);
                digitalWrite(LED_ONBOARD,LOW);
                delay(700);
        }
   }

   void blinkError(){
        for(int i=0; i<6; i++) {
                digitalWrite(LED_ONBOARD,HIGH);
                delay(200);
                digitalWrite(LED_ONBOARD,LOW);
                delay(400);
        }
   }




void carGoJoy(int in){
        int absDeltaValue = abs(in-joyMid);
        if(absDeltaValue>joyAcceleratorTrig) {
                if(!thrAccelerate.shouldRun()) {

                        if(in>joyMid)  engine.accelerate(-1);

                        else    engine.accelerate(1);
                }
        }
        else engine.brake();

}


void arm_printRepeat(String cmd,int steps=arm_angleStep,int interval=arm_angleStepInterval ){
        String tmp=">"; tmp+=cmd; tmp+="("; tmp+=steps; tmp+=","; tmp+=interval; tmp+=")";
        arm.print(tmp);
        if(debug) usb.println(tmp);
}

// Interprets commands
void Fasterpreter::interpret(){
        // usb.println("Interpreter loaded");
//printData();

        if(strcmp(dir[0].c_str(),"ctl")==0) {
                /* Controller protocol:
                   E.g.: >ctl.psd(start)\n
                      >ctl.RJ(128,128)\n
                   Begins with ">ctl.", followed by:
                   DPsd --> D Pad buton pressed (up,down,left,right)
                   DRel --> "  "    "    released
                   RPsd --> Right(R1,R2,R3) button pressed
                   RRel
                   LPsd
                   LRel
                   LJ --> left joystick, in the form LJ(X,Y) .Eg.: LJ(128,128)
                   RJ --> right joystick, ...
                   psd --> other button pressed
                   rel --> other button released
                   --------------
                      Buttons:
                   R --> R1,R2, R3 (3rd is right joystick button)
                   L --> L1,L2, L3 (3rd is left joystick button)
                   DPad --> up,down,left,right
                   joysticks --> LJ, RJ

                   other buttons --> start, back/sel, 1,2,3,4   (1,2,3,4 are buttons numbered from the uppermost, clockwise)

                   For PS2,PS3,PSX --> 1,2,3,4 are Triangle,Circle, Cross, Square

                 */
                if(strcmp(dir[1].c_str(),"LJ")==0) {
                        carGoJoy(intArg[1]);
                        //engine.setSpeed(intArg[1],joySet);
                }

                else if(strcmp(dir[1].c_str(),"RJ")==0) {
                        //  int x = mapJoy(intArg[0]);

                        steering.turn(intArg[0],joySet);
                }
                else if(strcmp(dir[1].c_str(),"psd")==0) {
                        if(intArg[0]==3) {
                                String tmp=">";
                                if(arm_isHolding) {
                                        tmp+="drop(";
                                        arm_isHolding = false;
                                }
                                else {
                                        tmp+="grip(";
                                        arm_isHolding = true;
                                }
                                tmp+=")";
                                arm.println(tmp);
                        }
                        else if(intArg[0]==1) {
                                String tmp=">"; tmp+="fan(";
                                if(arm_fanIsRunning) {
                                        tmp+=0;
                                        arm_fanIsRunning=false;
                                }
                                else {
                                        tmp+=1;
                                        arm_fanIsRunning=true;
                                }
                                tmp+=")";
                                arm.println(tmp);
                        }
                        else if (strncmp(strArg[0].c_str(),"start",5)==0){
                          // nothing yet
                }
              }

                else if(strcmp(dir[1].c_str(),"DPsd")==0) {
                        if(strncmp(strArg[0].c_str(),"left",2)==0) arm_printRepeat("base.yaw",(-arm_steps),arm_stepsInterval);


                        else if(strncmp(strArg[0].c_str(),"right",2)==0) arm_printRepeat("base.yaw",arm_steps,arm_stepsInterval);


                        else if(strncmp(strArg[0].c_str(),"up",2)==0)  arm_printRepeat("base.pitch",arm_steps,arm_stepsInterval);


                        else if(strncmp(strArg[0].c_str(),"down",2)==0) arm_printRepeat("base.pitch",(-arm_steps),arm_stepsInterval);


                }

                else if(strcmp(dir[1].c_str(),"DRel")==0) {
                        if(strncmp(strArg[0].c_str(),"left",2)==0) arm_printRepeat("base.yaw",0,0);

                        else if(strncmp(strArg[0].c_str(),"right",2)==0) arm_printRepeat("base.yaw",0,0);


                        else if(strncmp(strArg[0].c_str(),"up",2)==0) arm_printRepeat("base.pitch",0,0);


                        else if(strncmp(strArg[0].c_str(),"down",2)==0) arm_printRepeat("base.pitch",0,0);


                }

                else if(strcmp(dir[1].c_str(),"RRel")==0) {
                        if(strncmp(strArg[0].c_str(),"R1",2)==0)  arm_printRepeat("wrist.pitch",0,0);

                       else if(strncmp(strArg[0].c_str(),"R2",2)==0) arm_printRepeat("wrist.pitch",0,0);

                }

                else if(strcmp(dir[1].c_str(),"LRel")==0) {
                        if(strncmp(strArg[0].c_str(),"L1",2)==0)  arm_printRepeat("elbow.pitch",0,0);

                       else if(strncmp(strArg[0].c_str(),"L2",2)==0) arm_printRepeat("elbow.pitch",0,0);

                }

                else if(strcmp(dir[1].c_str(),"RPsd")==0) {
                        if(strncmp(strArg[0].c_str(),"R1",2)==0) arm_printRepeat("wrist.pitch",(arm_angleStep),arm_angleStepInterval);

                        else if(strncmp(strArg[0].c_str(),"R2",2)==0)  arm_printRepeat("wrist.pitch",(-arm_angleStep),arm_angleStepInterval);

                }

                else if(strcmp(dir[1].c_str(),"LPsd")==0) {
                        if(strncmp(strArg[0].c_str(),"L1",2)==0) arm_printRepeat("elbow.pitch",arm_angleStep,arm_angleStepInterval); 

                        else if(strncmp(strArg[0].c_str(),"L2",2)==0) arm_printRepeat("elbow.pitch",(-arm_angleStep),arm_angleStepInterval);

                }


        }


        else if(strcmp(dir[0].c_str(),"car")==0) {
                //if(debug)usb.println("to the Car");
                if(strcmp(dir[1].c_str(),"turn")==0) {
                        steering.turn(intArg[0]);
                }
                else if(strcmp(dir[1].c_str(),"go")==0||strncmp(dir[1].c_str(),"speed",3)==0) {
                        engine.setSpeed(intArg[0]);
                }
                else if(strncmp(dir[1].c_str(),"accelerate",3)==0) {
                        engine.accelerate(intArg[0]);
                }
                else if(strncmp(dir[1].c_str(),"brake",3)==0||strcmp(dir[1].c_str(),"stop")==0) {
                        engine.brake();
                }


        }

        else if(strncmp(dir[0].c_str(),"arm",3)==0) {
                usb.println("got arm");
                String tmp=">"; tmp+=dir[1];
                if(strcmp(dir[2].c_str(),"")!=0) {
                        tmp+=".";
                        tmp+=dir[2];
                }
                tmp+="(";
                if(hasIntArg[0]) tmp+=intArg[0];
                if(hasIntArg[1]) {
                        tmp+=",";
                        tmp+=intArg[1];
                }
                tmp+=")";
                usb.println(tmp);
                arm.println(tmp);

        }

        else if (strncmp(dir[0].c_str(),"sensor",4)==0) {
               // sensors removed
        }

        /* else if(strcmp(dir[0].c_str(),"wifi")==0) {
                 if(strcmp(dir[1].c_str(),"led")==0) {
                         usb.println("command is: wifi.led");

                 }
           }
         */


        cleanInterpreter();
}

void printValue(String txt,int data){
        String tmp=">"; tmp+=txt; tmp+="("; tmp+=data; tmp+=")\n";
        if(interpreter.source =='b') bluetooth.print(tmp);
        else if(interpreter.source =='w') wifi.print(tmp);
        else if(interpreter.source =='u') usb.print(tmp);
}

void printValue(String txt,float data){
        String tmp=">"; tmp+=txt; tmp+="("; tmp+=data; tmp+=")\n";
        if(interpreter.source =='b') bluetooth.print(tmp);
        else if(interpreter.source =='w') wifi.print(tmp);
        else if(interpreter.source =='u') usb.print(tmp);
}
