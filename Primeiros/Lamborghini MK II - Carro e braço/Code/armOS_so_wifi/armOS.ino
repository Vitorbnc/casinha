//#include <Arduino.h>

#include <Stepper.h>
#include <Servo.h>

#include <Thread.h>
#include <ThreadController.h>

ThreadController thrController = ThreadController();
Thread thrStepper, thrServo;
int defaultInterval = 500;

#define uart Serial

const int stepsPerRevolution = 96;  // change this to fit the number of steps per revolution, for pm35l-048 or pm55l-048, it is 48

Stepper base_yawMotor(stepsPerRevolution, A4, 6, 8, 7);
Stepper base_pitchMotor(stepsPerRevolution, 2, A5, 4, 13);


const int fan = 3; // has pwm
const int holdSensor = 12;
bool isHolding = false;
const int a_pin = 10, b_pin = 11, c_pin = 9; // servos or other stuff attached to pwm

int servoNum=3;
int servoPos[] ={0,0,0};  // servo pos received from Serial (not real)
const int aLimits[]={0,175};
const int bLimits[]={0,180};
const int cLimits[]={0,170};
const int angleSet[]={0,180};
Servo a,b,c;


bool cIsServo = true;

int base_pitchMotor_speedWithLoad = 60;
int base_pitchMotorSpeed = 120;
int base_yawMotorSpeed = 120;
int base_yawMotor_speedWithLoad = 60;

// callback state variables
char currentServo;
int currentServoLimits[2];
//Stepper& currentStepper=base_yawMotor;
char currentStepper;
int currentSteps,currentAngleSteps;
bool stepIsPositive, angleStepIsPositive;


int value;

// Variables used by the Interpreter

const int dirFields=3;  // Set your number of dirs here
const int argFields=3;  //Set your number of args here
const int dirSize=6;  //Max dir name size
String dir[dirFields];
String strArg[argFields];
int intArg[argFields];
// Use the following if you want to check for args, commands or forwardables
bool hasArgs=false;
bool gotCmd=false;
bool hasStrArg[argFields];
bool hasIntArg[argFields];

bool gotFwd = false;

long startTime, endTime;

String forwardable;
String cmd;

void setupThreads(){
  thrStepper.onRun(stepperCallback);
  thrServo.onRun(servoCallback);

  thrStepper.enabled=false;
  thrServo.enabled=false;

  thrController.add(&thrStepper);
  thrController.add(&thrServo);
}

void stepperCallback(){
  //currentStepper.step(currentSteps);
  if (currentStepper == 'p') base_pitchMotor.step(currentSteps);
  else if (currentStepper == 'y') base_yawMotor.step(currentSteps);
}

void servoCallback(){
  if(currentServo=='a'){
  servoPos[0]+=currentAngleSteps;
  int pos=map(servoPos[0],angleSet[0],angleSet[1],currentServoLimits[0],currentServoLimits[1]);
   a.write(pos);
 }
 else if(currentServo=='b'){
 servoPos[1]+=currentAngleSteps;
 int pos=map(servoPos[1],angleSet[0],angleSet[1],currentServoLimits[0],currentServoLimits[1]);
  b.write(pos);
}
else if(currentServo=='c'){
servoPos[2]+=currentAngleSteps;
int pos=map(servoPos[2],angleSet[0],angleSet[1],currentServoLimits[0],currentServoLimits[1]);
 c.write(pos);
}
}

void logTime(){
  if(startTime==-1){
    startTime=micros();
  }
  else if(endTime==-1){
    endTime=micros();
  }
}

void printTime(String intro){
long interval;
interval=endTime-startTime;
startTime=-1;
endTime=-1;
String txt = intro;
txt+=" took ";
txt+=interval;
 txt+="uS";
  uart.println(txt);
}
void cleanInterpreter(){
        gotFwd=false;
        gotCmd=false;
        forwardable="";
         // clean dirs only if necessary
        /* for(int i=0;i<dirFields;i++){
          dir[i]="";
        }
         */
        for(int i=0; i<argFields; i++) {
                //intArg[i]=0;
                //strArg[i]=""; // clean String Arguments only if necessary
                hasStrArg[i]=false;
                hasIntArg[i]=false;
        }
}
void initSteppers(){
  base_yawMotor.setSpeed(base_yawMotorSpeed);
  base_pitchMotor.setSpeed(base_pitchMotorSpeed);
}

void initServos(){
  a.attach(a_pin);
    delay(100);
  b.attach(b_pin);
    delay(100);
  c.attach(c_pin);
  delay(100);

int midAngle = (angleSet[0]+angleSet[1])/2;
for (int i=0;i< servoNum;i++)  servoPos[i] = midAngle;
  a.write(midAngle);

  delay(100);
  b.write(midAngle);
    delay(100);
  c.write(midAngle);
    delay(100);

}

void setup() {
  uart.begin(250000);
  delay(10);
cleanInterpreter();
initSteppers();
initServos();

pinMode(holdSensor,INPUT);
pinMode(fan,OUTPUT);
delay(100);
digitalWrite(fan,LOW);
delay(100);
setupThreads();

}


void interpret(){
// Uncomment the line below to print every dir and arg. Useful for debugging or understanding this code
//printData();
//uart.println(dir[0]);
//uart.println(intArg[0]);
if(strcmp(dir[0].c_str(),"base")==0){
  if(strcmp(dir[1].c_str(),"pitch")==0){
    if(!hasIntArg[1]){
          base_pitchMotor.step(intArg[0]);

    }
    else if (intArg[1]>5){
      thrStepper.setInterval(intArg[1]);
      currentSteps = intArg[0];
      currentStepper = 'p';
      thrStepper.enabled=true;

    }
    else {
    thrStepper.enabled=false;
    }
}

else if(strcmp(dir[1].c_str(),"yaw")==0){
  if(!hasIntArg[1]){
    base_yawMotor.step(intArg[0]);
  }
else if (intArg[1]>5){
      thrStepper.setInterval(intArg[1]);
      currentSteps = intArg[0];
      currentStepper = 'y';
      thrStepper.enabled=true;

    }
    else {
    thrStepper.enabled=false;
}
  }

}

else if(strcmp(dir[0].c_str(),"elbow")==0){
if(strcmp(dir[1].c_str(),"pitch")==0){
  if(!hasIntArg[1]){
    servoPos[2] = intArg[0];
    int pos=map(intArg[0],angleSet[0],angleSet[1],aLimits[0],aLimits[1]);
   a.write(pos);
  }
  else if (intArg[1]>2){
    thrServo.setInterval(intArg[1]);
      //currentServoAngle = servoPos[0];
      currentAngleSteps = intArg[0];
      currentServo = 'a';
      currentServoLimits[0] = aLimits[0];
      currentServoLimits[1] = aLimits[1];
      thrServo.enabled=true;
  }
  else  thrServo.enabled=false;


}
}

  else if(strcmp(dir[0].c_str(),"wrist")==0){
   if(strcmp(dir[1].c_str(),"pitch")==0){
  if(!hasIntArg[1]){
    servoPos[2] = angleSet[1]-intArg[0];
    int pos=map(servoPos[2],angleSet[0],angleSet[1],bLimits[0],bLimits[1]);
   b.write(pos);
  }
  else if (intArg[1]>2){
    thrServo.setInterval(intArg[1]);
      //currentServoAngle = servoPos[1];
      currentAngleSteps = -intArg[0];
      currentServo = 'b';
      currentServoLimits[0] = bLimits[0];
      currentServoLimits[1] = bLimits[1];
      thrServo.enabled=true;
  }
  else  thrServo.enabled=false;


}
  }

else if(strcmp(dir[0].c_str(),"claw")==0){

if(strcmp(dir[1].c_str(),"pitch")==0){
  if(!hasIntArg[1]){
    servoPos[2] = intArg[0];
    int pos=map(intArg[0],angleSet[0],angleSet[1],cLimits[0],cLimits[1]);
   c.write(pos);
  }
  else if (intArg[1]>2){
    thrServo.setInterval(intArg[1]);
    //  currentServoAngle = servoPos[2];
      currentAngleSteps = intArg[0];
      currentServo = 'c';
      currentServoLimits[0] = cLimits[0];
      currentServoLimits[1] = cLimits[1];
      thrServo.enabled=true;
  }
  else  thrServo.enabled=false;

  }
}

else if (strcmp(dir[0].c_str(),"grip")==0){
  uart.println("grabbig...");
  int actualPos= map(servoPos[2],angleSet[0],angleSet[1],cLimits[0],cLimits[1]);
  for (; actualPos< cLimits[1]; actualPos += 5) { // goes from 0 degrees to 180 degrees
       uart.println(actualPos);
    // in steps of 1 degree
    c.write(actualPos);              // tell servo to go to position in variable 'pos'
      delay(25);                       // waits 15ms for the servo to reach the position
  if(digitalRead(holdSensor)){
    uart.println("got it");
    isHolding=true;
    base_yawMotor.setSpeed(base_yawMotor_speedWithLoad);
    base_pitchMotor.setSpeed(base_pitchMotor_speedWithLoad);
    break;
  }
  }
}

else if(strcmp(dir[0].c_str(),"drop")==0){
  int actualPos= map(servoPos[2],angleSet[0],angleSet[1],cLimits[0],cLimits[1]);
  if(actualPos>cLimits[0]-20)actualPos-=20;
  c.write(actualPos);
  while(digitalRead(holdSensor)==HIGH&&actualPos>cLimits[0]){
    actualPos-=5;
    actualPos=constrain(actualPos,cLimits[0],cLimits[1]);
    c.write(actualPos);
    delay(25);
  }
  base_yawMotor.setSpeed(base_yawMotorSpeed);
  base_pitchMotor.setSpeed(base_pitchMotorSpeed);
  isHolding=false;
}

else if(strcmp(dir[0].c_str(),"fan")==0){

    if(intArg[0]==1) digitalWrite(fan,HIGH);
    if(intArg[0]==0) digitalWrite(fan,LOW);

  }

// Don't remove this line
  cleanInterpreter();
}

void  parseArgs(String rawTxt){
        // parses the function arguments. E.g.:(100,10,-25)
        String tmp;
        int old_commaIndex =-1;
        bool oneMore = true;
        for(int i=0; i<argFields; i++) {
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
                        if(!isDigit(c)&& c!='-'&& c!='+'){
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


void  parseDirs(String fullTxt){
        //Eg.: >car.go(100,100,20)
        //>car.turn(10)
        //display.show(lalalal)
        //Obs.: fullTxt must already be without '>', use '>' to detect a command in the desired data stream before calling this.
        gotCmd=true;
        int argStartIndex =  fullTxt.indexOf('(');
        int argEndIndex = fullTxt.indexOf(')');
        String rawTxt = fullTxt.substring(0,argStartIndex);

        int old_dotIndex =-1;
        bool oneMore = true;
        for(int i=0; i<dirFields; i++) {
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


void  readStreams(){

        if(uart.available()) {

                char c = uart.read();
                if(c=='>') {
                        String serialTxt = uart.readStringUntil(')');
                        serialTxt+=')';
                        //uart.println(serialTxt);
                        parseDirs(serialTxt);


                }
                else if (c=='\"') {
                        gotFwd=true;
                        forwardable= uart.readStringUntil('\"');
                        // use forwardable here
                }
        }
}

void loop() {
  //delay(5000);
  ++value;

  readStreams();
thrController.run();

}
