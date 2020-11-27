
#include <LiquidCrystal.h>                    /* LiquidCrystal Library */
#include "pitches.h"
LiquidCrystal lcd(48,49,53, 52, 51, 50); 

/*
 * Este código é o sucessor do Power_Sation 
 * Compreende uma fonte de alta tensão com modulação PWM. Ela contém uma bateria lipo 7.4V, um fet IRF3205 para modulação de um sinal de entrada até 55V
 * Há também um divisor de tensão para a saída com atenuação de x10^4, ele nos permite ler até 50kV
 * 
 */

const int ADC_MAX = 1023;

const int PWM_DUTY_POT_PIN=A1;
const int PIN_ZVS=12; // pin to zvs control mosfet

const int TIMER_ZVS = 1; //timer corresponding to PIN_ZVS
int prescaler_zvs = 0;

const int HV_PROBE_PIN=A7;
const float HV_PROBE_FACTOR = (5.0/1023.0)*10.0; // in kV

const int JOY_X_PIN=A8;
const int JOY_Y_PIN=A9;
const int JOY_BUTTON_PIN=46;

const int PIN_BTN_RIGHT = 43;
const int PIN_BTN_LEFT = 42;



const int BATT_PIN=A2;
const float BATT_VOLTAGE_FACTOR = 0.0096;
const float MIN_BATT_VOLTAGE = 7.4;

const int PIN_LED_ONBOARD = 13;

unsigned long lastUiUpdate =0;
int uiUpdateInterval = 50; // in ms, was 50

float pwmFreq =0;
// ---- music player
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";

int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;

int speaker  = PIN_ZVS;

//-----------------------

void limit(int* value, int min, int max){
  if(*value>max)
    *value = max;
  else if (*value <0)
    *value=0;
 
}

void splashScreen(){
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" Chocante!");
  lcd.setCursor(0,1);
  lcd.print("Entrada max:55V");
}

int joyXDir,joyX,joyYDir,joyY;

bool joyBtnChanged, joyXDirChanged, joyYDirChanged;
bool joyBtn;
int debounceInterval = 50;
unsigned long lastDebounceTime =0;

void initJoy(){
 joyBtnChanged = false;
 joyBtn = false;
}

void readJoy(){
  int highThreshold = ADC_MAX - ADC_MAX/4.0;
  int lowThreshold =  ADC_MAX/4.0;

// The button pin is HIGH when not pressed
  bool btnNow = !digitalRead(JOY_BUTTON_PIN);
   
    if (btnNow != joyBtn) 
      joyBtnChanged = true;
    else 
      joyBtnChanged = false; 

    joyBtn = btnNow;

 
  joyX = analogRead(JOY_X_PIN);
  joyY = analogRead(JOY_Y_PIN);

  
  int joyXDirNow;

  if(joyX>highThreshold)
    joyXDirNow =1;
  else if(joyX<lowThreshold)
    joyXDirNow = -1;
  else 
    joyXDirNow = 0;

  if(joyXDirNow != joyXDir)
    joyXDirChanged = true;
  else joyXDirChanged = false;
  joyXDir = joyXDirNow;

int joyYDirNow;

  if(joyY>highThreshold)
    joyYDirNow =1;
  else if(joyY<lowThreshold)
    joyYDirNow = -1;
  else 
    joyYDirNow = 0;

  if(joyYDirNow != joyYDir)
    joyYDirChanged = true;
  else joyYDirChanged = false;
  joyYDir = joyYDirNow;

}

bool btnLeftChanged, btnRightChanged;
bool btnLeft, btnRight;

void readBtns(){
// The button pin is HIGH when not pressed
  bool btnNow = !digitalRead(PIN_BTN_LEFT);
   
    if (btnNow != btnLeft) 
      btnLeftChanged = true;
    else 
      btnLeftChanged = false; 

    btnLeft = btnNow;

    btnNow = !digitalRead(PIN_BTN_RIGHT);

    if (btnNow != btnRight) 
      btnRightChanged = true;
    else 
      btnRightChanged = false; 

    btnRight = btnNow;
}


void setup() {
  initJoy();
  Serial.begin(115200);
  splashScreen();
  pinMode(JOY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
  //setPwmFreq(0, 0x04); // this will set pins D4,D13 to 62500/256=244.14Hz;
  prescaler_zvs = 0x04;
  setPwmFreq(TIMER_ZVS,prescaler_zvs); //setting D11,D12. I believe 0x03 (490Hz) is default
  delay(1500);
  
}

void loop() {
  readJoy();
  readBtns();
  UI();
}



String lastHvTxt ="";
unsigned long lastHvReading =0;
int hvReadingInterval = 250;
int hv_rawSum =0;
int hv_readingCount =0;

String hvTxt(){
if(millis()-lastHvReading>hvReadingInterval){
  String hv_txt="HV:";

  float hv=(hv_rawSum/hv_readingCount)*HV_PROBE_FACTOR;

  hv_txt+=hv; hv_txt+="kV";
  lastHvReading = millis();
  lastHvTxt = hv_txt;
  hv_rawSum =0;
  hv_readingCount =0;
  return hv_txt;
}
else {
  hv_rawSum += analogRead(HV_PROBE_PIN);
  hv_readingCount++;
  return lastHvTxt;
}
}

int currentScreen =0;

void mainScreen(){
  lcd.clear();
  lcd.setCursor(0,0);

  String battTxt="Bateria: ";
  float battVoltage = analogRead(BATT_PIN)*BATT_VOLTAGE_FACTOR;
  battTxt+=battVoltage;
  battTxt+="V ";
  lcd.print(battTxt);

  lcd.setCursor(0,1);
  lcd.print(hvTxt());
  //showPwm();

  if(joyBtnChanged and joyBtn){
    Serial.println("got!");
    Serial.println(currentScreen);
    currentScreen++;
    
  }
 
}

bool zvsIsOn = false;

String zvsTxt(){
  String txt="ZVS:";
  if(zvsIsOn)
    txt+="ON";
  else 
    txt+="OFF";
    return txt;
}


void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(speaker, note, duration);
    delay(duration);
   //Stop tone on buzzerPin
  noTone(speaker);
   delay(50);
 }

void imperial_march_1st()
{
 beep( NOTE_A4, 500);
 beep( NOTE_A4, 500);    
 beep( NOTE_A4, 500);
 beep( NOTE_F4, 350);
 beep( NOTE_C5, 150);  
 beep( NOTE_A4, 500);
 beep( NOTE_F4, 350);
 beep( NOTE_C5, 150);
 beep( NOTE_A4, 650);
 
  delay(500);
 
 beep( NOTE_E5, 500);
 beep( NOTE_E5, 500);
 beep( NOTE_E5, 500);  
 beep( NOTE_F5, 350);
 beep( NOTE_C5, 150);
 beep( NOTE_D5, 500);
 beep( NOTE_F4, 350);
 beep( NOTE_C5, 150);
 beep( NOTE_A4, 650);
 
  delay(500);
}
 
void imperial_march_2nd()
{
 beep( NOTE_A5, 500);
 beep( NOTE_A4, 300);
 beep( NOTE_A4, 150);
 beep( NOTE_A5, 500);
 beep( NOTE_GS5, 325);
 beep( NOTE_G5, 175);
 beep( NOTE_FS5, 125);
 beep( NOTE_F5, 125);    
 beep( NOTE_FS5, 250);
 
  delay(325);
 
 beep( NOTE_A5, 250);
 beep( NOTE_DS5, 500);
 beep( NOTE_D5, 325);  
 beep( NOTE_CS5, 175);  
 beep( NOTE_C5, 125);  
 beep( NOTE_B4, 125);  
 beep( NOTE_C5, 250);  
 
  delay(350);
}

void song_imperial_march(){

  //Play first section
  imperial_march_1st();
 
  //Play second section
  imperial_march_2nd();
 
  //Variant 1
 beep( NOTE_F4, 250);  
 beep( NOTE_G5, 500);  
 beep( NOTE_F4, 350);  
 beep( NOTE_A4, 125);
 beep( NOTE_C5, 500);
 beep( NOTE_A4, 375);  
 beep( NOTE_C5, 125);
 beep( NOTE_E5, 650);
 
  delay(500);
 
  //Repeat second section
  imperial_march_2nd();
 
  //Variant 2
 beep( NOTE_F4, 250);  
 beep( NOTE_G5, 500);  
 beep( NOTE_F4, 375);  
 beep( NOTE_C5, 125);
 beep( NOTE_A4, 500);  
 beep( NOTE_F4, 375);  
 beep( NOTE_C5, 125);
 beep( NOTE_A4, 650);  
 
  delay(650);

}

void song_test(){
analogWrite(PIN_ZVS, 0);
    for (count = 0; count < MAX_COUNT; count++){
      statePin = !statePin;
      digitalWrite(PIN_LED_ONBOARD, statePin);
      for (count3 = 0; count3 <= (melody[count * 2] - 48) * 30; count3++){
        for (count2 = 0; count2 < 8; count2++) {
          if (names[count2] == melody[count * 2 + 1]){
            analogWrite(PIN_ZVS, 500);
            delayMicroseconds(tones[count2]);
            analogWrite(PIN_ZVS, 0);
            delayMicroseconds(tones[count2]);
          }
          if (melody[count * 2 + 1] == 'p')
          {
            // make a pause of a certain size
            analogWrite(PIN_ZVS, 0);
            delayMicroseconds(500);
          }
        }
      }
    }
}

int currentSong =1;
int maxSong =2;

void songGUI(){

  lcd.clear();
  lcd.setCursor(0,0);
  String txt =zvsTxt();
  txt+=" -Clique";
  lcd.print(txt);

  txt="Musica ";
  txt+=currentSong;
  lcd.setCursor(0,1);
  lcd.print(txt);
}

void songPlayer(){
  //Desativado por instabilidade
 /*
  if(btnRightChanged and btnRight)
    currentSong++;
  if(btnLeftChanged and btnLeft) 
    currentSong--;
*/
limit(&currentSong,0,maxSong);   

if(joyBtnChanged and joyBtn)
  zvsIsOn = !zvsIsOn;

  if (zvsIsOn){
    songGUI(); 
    switch(currentSong){
      case 0:
      song_test();
      break;
      case 1:
      song_imperial_march();
      break;

    }
  if(joyBtnChanged and joyBtn)
  zvsIsOn = !zvsIsOn;  
  
}
}



void decreaseZVSPWM(){
    prescaler_zvs++;
    limit(&prescaler_zvs,0,5);
    setPwmFreq(TIMER_ZVS,prescaler_zvs);
}



void increaseZVSPWM(){
prescaler_zvs--;
    limit(&prescaler_zvs,0,5);
    setPwmFreq(TIMER_ZVS,prescaler_zvs);
}

void zvsGUI(){
 lcd.clear();
  lcd.setCursor(0,0);
  String txt="";
if(zvsIsOn){
    lcd.print(zvsTxt());
    lcd.print(" ");
    lcd.print(hvTxt());
  }
  else
    lcd.print(zvsTxt()+" -Clique");

  int pwm = mapPWM();

  lcd.setCursor(0,1);
  txt+="PWM:";
  txt+=(unsigned int)round(pwmFreq);txt+="Hz@";
  txt+=pwm;
  txt+="% ";
  lcd.print(txt);
}

void zvs(){
 
  if(joyBtnChanged and joyBtn)
  zvsIsOn = !zvsIsOn;

//Desativado por comportamento instável
/*
  if(btnRightChanged and btnRight)
    increaseZVSPWM();
  if(btnLeftChanged and btnLeft) 
    decreaseZVSPWM();
*/

 int pwm = mapPWM();
   if(zvsIsOn)
    if(pwm==100)
      digitalWrite(PIN_ZVS,HIGH);
    else
      analogWrite(PIN_ZVS, pwm);

  else(digitalWrite(PIN_ZVS,LOW));

}

bool mayChangeScreen = true;

int maxScreen =2;
void UI(){
  
  if(mayChangeScreen and joyYDirChanged){
    if(joyYDir==1){
      currentScreen++;
    }
    else if (joyYDir==-1){
      currentScreen--;

    }
  }

if(currentScreen>maxScreen)
  currentScreen =maxScreen;
else if(currentScreen<0)
  currentScreen =0;

  switch(currentScreen){
    case 1:
    zvs();
    break;
    case 2:
    songPlayer();
    break;
    default:
    break;
  }


  if(millis()-lastUiUpdate>=uiUpdateInterval){
    switch(currentScreen){
      case 0:
      mainScreen();
      break;
      case 1:
      zvsGUI();
      break;
      case 2:
      songGUI();
      break;
      default:
      mainScreen();
    }
  
  lastUiUpdate=millis();
}
}



int mapPWM(){
int pwmValue = map(analogRead(PWM_DUTY_POT_PIN),0, 1023,0,255);
return map(pwmValue,0,255,0,100);
}






int prescaler_settingToDivisor(int prescaler){
  switch(prescaler){
    case 0x01: return 1;
    break;
    case 0x02: return 8;
    break;
    case 0x03: return 64;
    break;
    case 0x04: return 256;
    break;
    case 0x05: return 1024;
    break;
    default: return -1;
    break;
  }

}

void setPwmFreq(int timer,int prescaler){ // this is for mega2560
  float baseFreq;
  switch(timer){
    case 0: // pins D4, D13
    baseFreq = 62500.0;// base freq for timer0 is 62500
    TCCR0B = TCCR0B & 0b11111000 | prescaler;
    break;

    case 1: // pins D11 & D12
    baseFreq = 31372.75;
    TCCR1B = TCCR1B & 0b11111000 | prescaler;
    break;

    case 2: // pins D9 & D10
    baseFreq = 31372.55;
    TCCR2B = TCCR2B & 0b11111000 | prescaler;
    break;
// there are more 3 timers not implemented here
    default:
    baseFreq = 0.0;

    break;
  }
    pwmFreq= baseFreq/prescaler_settingToDivisor(prescaler);

}
