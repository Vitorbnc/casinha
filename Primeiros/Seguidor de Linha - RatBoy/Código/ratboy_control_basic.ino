
#define DEBUG false
#define NUM_SENSORS 6

#define EN_A PB0
#define IN1 PB10
#define IN2 PB11

#define EN_B PB1
#define IN3 PC14
#define IN4 PC13

const uint8_t sensor[] = {PA7, PA6, PA5, PA4, PA3, PA2};
int sensorVal[NUM_SENSORS];
//The sensor output is about 40-50 for a white surface and about 620-800 for black insulating tape (using 10 bit resolution)
// For 12 bit: 160-210 for white; 2500-3500 for black insulating tape
int sensorBin = 0;
int error = 0;
int lastError = 0;
int errorThreshold = 0;
int Kp = 500;//750 //500

int base_pwm_lm = 4.5*65536.0/10.0;
int base_pwm_rm = 5.5*65536.0/10.0;

void setup() {
  // put your setup code here, to run once:

  //for (int i=0;i<NUM_SENSORS;i++){
  //  pinMode(sensors[i]
  //}
  pinMode(EN_A, PWM);
  pinMode(EN_B, PWM);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //analogWriteResolution(10);
  pwmWrite(EN_B, base_pwm_rm);
  pwmWrite(EN_A, base_pwm_lm);

  //delay(750);
  //pwmWrite(EN_B, 0);
  //pwmWrite(EN_A, 0);

  Serial.begin(115200);
}

int getError(){
  sensorBin = 0;
   for (int i = 0; i < NUM_SENSORS; i++) {
    sensorVal[i] = analogRead(sensor[i]);
    sensorBin |= (sensorVal[i]>1500)<<i;
  }
       if (sensorBin == 0b100000) error = -5;
  else if (sensorBin == 0b110000) error = -4;
  else if (sensorBin == 0b010000) error = -3;
  else if (sensorBin == 0b011000) error = -2;
  else if (sensorBin == 0b001000) error = -1;
  else if (sensorBin == 0b001100 || sensorBin == 0 || sensorBin == 0b111111) error =  0;
  else if (sensorBin == 0b000100) error =  1;
  else if (sensorBin == 0b000110) error =  2;
  else if (sensorBin == 0b000010) error =  3;
  else if (sensorBin == 0b000011) error =  4;
  else if (sensorBin == 0b000001) error =  5;
  error = -error;
    return error;
}
void control(){
  if((error==lastError)or((lastError>errorThreshold) and (error>errorThreshold))or(lastError<errorThreshold and error<errorThreshold));
  else{
    digitalWrite(EN_A,LOW);
    digitalWrite(EN_B,LOW);
  }
  if(error ==0){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
else if (error <errorThreshold){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
else if(error>errorThreshold){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
int leftPwm = base_pwm_lm+Kp*error;
int rightPwm = base_pwm_rm-Kp*error;
  
  leftPwm = constrain(leftPwm,0,50000);
  rightPwm = constrain(rightPwm,0,50000);
 if(DEBUG){
  String txt = "left: ";
  txt+=leftPwm;txt+="   right: "; txt+=rightPwm; 
  Serial.println(txt);
 }
  pwmWrite(EN_A,leftPwm);
  pwmWrite(EN_B,rightPwm);
lastError = error;
}
void loop() {
  // put your main code here, to run repeatedly:
getError();
if(DEBUG){
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorVal[i] = analogRead(sensor[i]);
    Serial.print(sensorVal[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Error: ");
  Serial.println(error);
  //delay(200);

}
  control();
  //delay(10);
}
