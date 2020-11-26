//#include <Arduino.h>  // not necessary
// Vitor Barbosa

// comentar print da valocidade em accelerateCallback

//-------------------------------------------


#include <SPI.h>
#include <LoRa.h>

const int PAYLOAD_LEN = 6;
String payload = "";

#include <Streaming.h>
#include <Servo.h>

#include <Thread.h>
#include <ThreadController.h>


ThreadController thrController = ThreadController();
Thread thrAccelerate;


 #define debug true  // turn debug message on or off in serial
 #define usb Serial


char source; // char to define from which stream message came

// nodemcu onboard led
const int LED_ONBOARD = A6; 


// thread callback state variables
long interval_accelerator = 250; // was 500
const int joyAcceleratorTrig = 64;

int absAcceleration = 4; // was 1
int currentSpeed=0;



const int PIN_ESC =7; // constantes dos pinos dos servos, D4
const int PIN_REV = 4
; // pino do relé da ré, D3

const int PIN_STEERING=2; // d2




const int defaultInterval = 500;



const int joySet[]={0,255};
const int joyMid = (joySet[0]+joySet[1])/2;
const int deltaJoySet[]={0,128};



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
const int escPulseSet[2]={980,1600};    // was 800,1800, 800 is zero Speed // 2nd ver 980,1600


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
const int maxAbsSpeed = 40;
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
                if(debug) Serial.println("zero speed");
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
                if(debug) Serial.println("zero speed");
                lastSpeed =0;
        }
        else{
                //  int speedChange = speed-lastSpeed;

                pulseWidth = map(absDeltaSpeed, 0, 100, escPulseSet[0], escPulseSet[1]);

                /*
                        if(debug) Serial.println(midSpeed);
                        if(debug) Serial.println(absDeltaSpeed);
                        if(debug) Serial.println(pulseWidth);

                 */
                accel.writeMicroseconds(pulseWidth);
                lastSpeed = speed;
                if(debug) Serial.println(speed);
                if(debug) Serial.println(pulseWidth);
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
                if(debug) Serial.println("zero speed");

        }
        else{
                //  int speedChange = speed-lastSpeed;

                pulseWidth = map(abs(deltaSpeed), 0, abs(speedSet[1]-midSpeed), escPulseSet[0], escPulseSet[1]);


                if(debug) Serial.println(midSpeed);
                if(debug) Serial.println(deltaSpeed);
                if(debug) Serial.println(pulseWidth);
                accel.writeMicroseconds(pulseWidth);
                lastSpeed = speed;

        }

}



}; // end of Engine -------------------------------------------------------

Steering steering;
Engine engine;


void readLoRa(){
  if(LoRa.parsePacket()){
    if((char)LoRa.read()=='$'){
      payload = "";
      for(int i=0;i<PAYLOAD_LEN-1;i++)
        payload+=(char)LoRa.read();

      parseShort();

    }
  }
}



void accelerateCallback(){
        int speed;
        if(engine.accelIsPositive){
                speed = engine.lastSpeed+absAcceleration;
                if(speed>engine.maxAbsSpeed){
                speed = engine.maxAbsSpeed;
                return;
                }
        }
        else {
          speed = engine.lastSpeed-absAcceleration;
          if(speed<-engine.maxAbsSpeed){
                speed = -engine.maxAbsSpeed;
                return;
          }
        }       

        engine.setSpeed(speed);
        if(debug) Serial.println(speed);

}

void setupThreads(){
        thrAccelerate.onRun(accelerateCallback);

        thrAccelerate.enabled=false;

        thrController.add(&thrAccelerate);
}



void setup()
{
        steering.init(PIN_STEERING);
        engine.init(PIN_ESC,PIN_REV);

        //setupWifi();
        Serial.begin(115200);
        delay(2000);
        Serial.println("Iniciando...");

        pinMode(LED_ONBOARD,OUTPUT);
        digitalWrite(LED_ONBOARD,LOW);

        setupThreads();

        
        LoRa.setPins(A3, A2); //SS, RESET (D1, D0)
        LoRa.setSPIFrequency(125000);
        
        if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
           //while (1); //block
        }

}




void loop()
{
        thrController.run();
        
       /* interpreter.readStream(&wifi,'w');
        interpreter.readStream(&bluetooth,'b');
        interpreter.readStream(&usb,'u');
        */
       

        readLoRa();
        //readWifi();
        //reconnect();

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




void parseShort(){
  if(debug){
    Serial.print('$');
    Serial.println(payload);
  }
  char c0 = payload.charAt(0);
  if(c0=='R'){
    
   int x = strtol(payload.substring(1,3).c_str(),NULL,16);
    steering.turn(x,joySet);
  }
  else if (c0=='L'){
    int y = strtol(payload.substring(3,5).c_str(),NULL,16);
    carGoJoy(y);
  }
}
