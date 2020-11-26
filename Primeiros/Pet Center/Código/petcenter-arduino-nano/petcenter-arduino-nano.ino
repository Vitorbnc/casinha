#include <Arduino.h>
#include <Servo.h>
#include <ArduinoJson.h>

Servo servoH;
Servo servoV;

StaticJsonBuffer<200> jsonBuffer;

const int laserPin = 7;
const int relayPin = 4; // relay is active low

//Servo limits
const int hLim[] = {70,150};
const int vLim[] = {20,70};

//Init servo pos to middle
int posH = (hLim[1] + hLim[0])/2;
int posV = (vLim[1] + vLim[0])/2;

//Food motor ON time 
const unsigned long FOOD_DURATION = 35000;

bool shouldServeFood = false;
unsigned long lastFoodTime = 0;


void goTo(int target,Servo* servo, int* current){
//Slowly go to target position
while(*current>target){
    *current-=5;
    if(*current<target) *current = target;
    servo->write(*current);
    delay(75);
}
while(*current<target){
    *current+=5;
    if(*current>target) *current = target;
    servo->write(*current);
    delay(75);
}

}

void randomMotion(){
  //Randomly move both servos
    digitalWrite(laserPin,HIGH);

    for(int i=0;i<6;i++){
        goTo(random(hLim[0],hLim[1]),&servoH,&posH);
        delay(1000);
        goTo(random(vLim[0],vLim[1]),&servoV,&posV);
        delay(1000);
    }
    digitalWrite(laserPin,LOW);
}



void setup() {
    Serial.begin(115200);

    servoH.attach(9);
    servoV.attach(10);

    pinMode(laserPin,OUTPUT);
    pinMode(relayPin,OUTPUT);

    digitalWrite(laserPin,LOW);
    digitalWrite(relayPin,HIGH);

    servoH.write(posH);
    servoV.write(posV);

}

void manageFood(){
  //Keep food motor ON for the specified time, then turn it OFF
  
    if(millis()-lastFoodTime>FOOD_DURATION)
        shouldServeFood = false;
    
    if(shouldServeFood)
        digitalWrite(relayPin,LOW);
    else
        digitalWrite(relayPin,HIGH);
}

void loop() {

    manageFood();
    
    if(Serial.available()<4)
        return;

    JsonObject& root = jsonBuffer.parse(Serial);
    String cmd = root["cmd"];

    if(cmd=="feed"){
        shouldServeFood = true;
        lastFoodTime = millis();
    }
    else if(cmd=="play"){
        randomMotion();
    }
    else if(cmd=="blink"){
        digitalWrite(laserPin,HIGH);
        delay(1000);
        digitalWrite(laserPin,LOW);
    }

}
