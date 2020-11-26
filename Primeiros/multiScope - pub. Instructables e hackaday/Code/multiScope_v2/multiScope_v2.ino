/*.
 * This project is an extension of carScope_v2, which was based on STM32-O-Scope.
 * It's gonna join 3 tools:
 *  Oscilloscope
 *  Laser Power Meter
 *  Wave Generator (perhaps for switching)
 */


#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <SPI.h>
#include <Fonts/TomThumb.h> // super small font

//edit Wire.h to set SDA and SCL constants to the desired pins (using PA11 and PA12)
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;


//#include <stdint.h>

// if you get uint8_t error, go to TouchScreen_STM.cpp and comment #include "pins_arduino.h"
// also, you may try changing   #include <WProgram.h> to  #include <Arduino.h>
#include <TouchScreen_STM.h>

#include "Adafruit_ILI9341_8bit_STM.h" //modified lib for 8-bit parallel displays

#define PORTRAIT 0
#define LANDSCAPE 1

// size on landscape mode
#define TFT_WIDTH  320
#define TFT_HEIGHT 240

// Initialize touchscreen
/* --------- LCD-STM32 wiring:

   8 bit parallel interface

   Data pins
   Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
   Pin stm32 |PB15|PB14|PB13|PB12|PB11|PB10|PB9|PB8|

   Control pins |RD |WR |RS |CS |RST|
   Pin stm32    |PA0|PA1|PA2|PA3|PA8|

 */


#define TOUCH_SCREEN_AVAILABLE

#if defined TOUCH_SCREEN_AVAILABLE

// These are the lcd pins used for touch (you don't need to define them here, but it will make touch setup more clear )
#define LCD_RD PA0

#define LCD_RS PA2
#define LCD_CS PA3
#define LCD_D0 PB8
#define LCD_D1 PB9

// pin setup for the 4-wire resisitve touch version:

#define YP LCD_RS  // must be an analog pin
#define XM LCD_CS  // must be an analog pin
#define YM LCD_D0   // can be a digital pin
#define XP LCD_D1   // can be a digital pin

#define XMIN 500
#define XMINBLACK 320
#define XMAX 3740
#define YMIN 420
#define YMAX 3640

#define MINPRESSURE -1 //10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int16_t touchX,touchY;
int16_t last_touchX, last_touchY;

int diffTouchThreshold = 25;
int doubleTapMinTime = 150;
int doubleTapMaxTime = 800;
long lastTapTime;

boolean gotDoubleTap = false;
boolean gotTouch = false;

boolean touched_left=false,touched_right=false,touched_top=false,touched_bottom=false,touched_centerX=false,touched_centerY=false;


#endif




/* For reference on STM32F103CXXX

   variants/generic_stm32f103c/board/board.h:#define BOARD_NR_SPI              2
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI1_NSS_PIN        PA4
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI1_MOSI_PIN       PA7
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI1_MISO_PIN       PA6
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI1_SCK_PIN        PA5

   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI2_NSS_PIN        PB12
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI2_MOSI_PIN       PB15
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI2_MISO_PIN       PB14
   variants/generic_stm32f103c/board/board.h:#define BOARD_SPI2_SCK_PIN        PB13

 */


#define TEST_WAVE_PIN       PB1     //PB1 PWM 500 Hz

// Create the lcd object
Adafruit_ILI9341_8bit_STM TFT = Adafruit_ILI9341_8bit_STM();


// Display colours
#define BEAM1_COLOUR ILI9341_GREEN
#define BEAM2_COLOUR ILI9341_RED
#define GRATICULE_COLOUR 0x07FF
#define BEAM_OFF_COLOUR ILI9341_BLACK
#define CURSOR_COLOUR ILI9341_GREEN

// Analog input
#define ANALOG_MAX_VALUE 4096
#define ANALOG_MAX_VOLTAGE 3.3
const int8_t analogInPin = PB0;   // Analog input pin: any of LQFP44 pins (PORT_PIN), 10 (PA0), 11 (PA1), 12 (PA2), 13 (PA3), 14 (PA4), 15 (PA5), 16 (PA6), 17 (PA7), 18 (PB0), 19  (PB1)
float samplingTime = 0;
float displayTime = 0;
float timePerSample =0;
float kSamples_per_second =0;

const int VPP_SAMPLES = 10;
int vmax_raw,vmin_raw;
float vmax,vmin,Vpp,Vrms;
// factors for getting actual voltages from voltage divider iput
const float factor_p6=2.0;

// variables for frequency counter
volatile unsigned long cyclesCount =0; // variable whose value will be changed by interrupt, must be marked as volatile
unsigned long lastMeasureTime;
int measureInterval = 1000000; // 1s in uS
int freqCounter_deltaTime =0;
float frequency;
const int FREQ_COUNT_PIN = PA15;

//variables for the inductance meter
const int INDUCTANCE_METER_IN_PIN = PB3;
const int INDUCTANCE_METER_OUT_PIN = PB4;

const double INDUCTANCE_METER_FIXED_CAPACITANCE = 1.E-6;

// Variables for the beam position
uint16_t signalX;
uint16_t signalY;
uint16_t signalY1;
int16_t xZoomFactor = 1;
// yZoomFactor (percentage)
int16_t yZoomFactor = 100; //Adjusted to get 3.3V wave to fit on screen
int16_t yPosition = 0;

// Startup with sweep hold off or on
boolean triggerHeld = 0;


unsigned long sweepDelayFactor = 1;
unsigned long timeBase = 200;  //Timebase in microseconds

// Screen dimensions
int16_t myWidth;
int16_t myHeight;

//Trigger stuff
boolean notTriggered;

// Sensitivity is the necessary change in AD value which will cause the scope to trigger.
// If VAD=3.3 volts, then 1 unit of sensitivity is around 0.8mV but this assumes no external attenuator. Calibration is needed to match this with the magnitude of the input signal.

// Trigger is setup in one of 32 positions
#define TRIGGER_POSITION_STEP ANALOG_MAX_VALUE/32
// Trigger default position (half of full scale)
int32_t triggerValue = 1024; //2048

int16_t retriggerDelay = 0;
int8_t triggerType = 3; //0-both 1-negative 2-positive 3-always triggers //default was 2
String triggerType_str="";

//Array for trigger points
uint16_t triggerPoints[2];


// Serial output of samples - off by default. Toggled from UI/Serial commands.
boolean serialOutput = false;


// Create USB serial port
//USBSerial usb;
#define usb Serial

// Samples - depends on available RAM 6K is about the limit on an STM32F103C8T6
// Bear in mind that the ILI9341 display is only able to display 240x320 pixels, at any time but we can output far more to the serial port, we effectively only show a window on our samples on the TFT.
# define maxSamples 1024*6 //1024*6
uint32_t startSample = 0; //10
uint32_t endSample = maxSamples;

// Array for the ADC data
//uint16_t dataPoints[maxSamples];
uint32_t dataPoints32[maxSamples / 2];
uint16_t *dataPoints = (uint16_t *)&dataPoints32;

//array for computed data (speedup)
uint16_t dataPlot[320]; //max(width,height) for this display


// End of DMA indication
volatile static bool dma1_ch1_Active;
#define ADC_CR1_FASTINT 0x70000 // Fast interleave mode DUAL MODE bits 19-16

adc_smp_rate adc_sampling_time = ADC_SMPR_1_5;
int current_sampling_rate =0;

/*
   // available sampling rates for adc
   typedef enum adc_smp_rate {
    ADC_SMPR_1_5,               //< 1.5 ADC cycles
    ADC_SMPR_7_5,               //< 7.5 ADC cycles
    ADC_SMPR_13_5,              //< 13.5 ADC cycles
    ADC_SMPR_28_5,              //< 28.5 ADC cycles
    ADC_SMPR_41_5,              //< 41.5 ADC cycles
    ADC_SMPR_55_5,              //< 55.5 ADC cycles
    ADC_SMPR_71_5,              //< 71.5 ADC cycles
    ADC_SMPR_239_5,             /**< 239.5 ADC cycles
   } adc_smp_rate;
 */



//UI variables
int trunkHeight =0;
int branch=0;
bool screenChanged = true;
const int  BOXSIZE=50;

boolean scope_enabled =false, powerMeter_enabled = false;

float abs_f(float value){
  if(value<0) return value*(-1.0);
  else return value;
}

//these calculate touch functions are made for LANDSCAPE mode
uint16_t calculateX(uint16_t x)
{
        return 320-(320*(x-XMIN))/(XMAX-XMIN);
}
uint16_t calculateY(uint16_t y)
{
        return (240*(y-YMIN))/(YMAX-YMIN);
}

class PowerMeter{

protected:

float temp_i, temp_f, heat_capacity, deltaTemp, deltaTime_secs;
long time_i,time_f;
const int factor_ms =1000;
int deltaTime;
float trigger_deltaTemp;

bool getData(){
// we have to convert every int to float, otherwise int math is used
 temp_f = bmp.readTemperature();
 time_f = millis();
 deltaTime = time_f-time_i;
 deltaTemp = temp_f-temp_i;
deltaTime_secs = float(deltaTime)/float(factor_ms);

/*
 Serial.print(deltaTime_secs);
 Serial.print(" s   ");
 Serial.println(deltaTemp);
*/
if(abs_f(deltaTemp)>=trigger_deltaTemp){
  //Serial.println("triggered");

  temp_i = temp_f;
  time_i=time_f;
  return true;
}
else return false;

}

public:

float power;


PowerMeter(float trig=1.0, float heatCap=.18){
    trigger_deltaTemp=trig;
    time_i=0;
    power=0;
    heat_capacity = heatCap;
  }

  void init(){
    deltaTime=0;
    power=0;
    time_i = millis();
    temp_i = bmp.readTemperature();
  }

void setTrigger(float temp){
  trigger_deltaTemp = temp;
}

float getDeltaTemp(){
  return deltaTemp;
}

float readPower(){
//P=CT/t
if(getData()) {
power = heat_capacity*deltaTemp/deltaTime_secs;
}
return power;
}

float readHeatCapacity(float knownPower){
//C=P.t/T
if(getData()){
heat_capacity = knownPower*deltaTime_secs/deltaTemp;
}
return heat_capacity;
}


}; // end of class

PowerMeter powerMeter(3.0,0.20); //trigger temperature difference in Celsius, heat Capacity in J/Celsius


adc_smp_rate changeSamplingTime(adc_smp_rate smp_time,boolean increasing){
        switch(int(smp_time)) {
        case ADC_SMPR_1_5:
                if(increasing) smp_time= ADC_SMPR_7_5;
                break;
        case ADC_SMPR_7_5:
                if(increasing) smp_time= ADC_SMPR_13_5;
                else smp_time=ADC_SMPR_1_5;
                break;
        case ADC_SMPR_13_5:
                if(increasing) smp_time= ADC_SMPR_28_5;
                else smp_time=ADC_SMPR_7_5;
                break;
        case ADC_SMPR_28_5:
                if(increasing) smp_time= ADC_SMPR_41_5;
                else smp_time=ADC_SMPR_13_5;
                break;
        case ADC_SMPR_41_5:
                if(increasing) smp_time= ADC_SMPR_55_5;
                else smp_time=ADC_SMPR_28_5;
                break;
        case ADC_SMPR_55_5:
                if(increasing) smp_time= ADC_SMPR_71_5;
                else smp_time=ADC_SMPR_41_5;
                break;
        case ADC_SMPR_71_5:
                if(increasing) smp_time= ADC_SMPR_239_5;
                else smp_time=ADC_SMPR_55_5;
                break;
        case ADC_SMPR_239_5:
                if(!increasing) smp_time= ADC_SMPR_71_5;
                break;

                // ADC_SMPR_239_5 was disabled because once there, we couldn't change it back.

        }
        return smp_time;
}

void increaseSamplingRate(){
        adc_sampling_time = changeSamplingTime(adc_sampling_time,false);
        setADCs();
}


void decreaseSamplingRate(){
        adc_sampling_time = changeSamplingTime(adc_sampling_time,true);
        setADCs();
}

boolean readTouch(){
        // Retrieve a point
        TFT.setRotation(LANDSCAPE);
        pinMode(LCD_RD,OUTPUT);
        digitalWrite(LCD_RD, HIGH);
        TSPoint p = ts.getPoint();
        //set controlpins to output again
        TFT_CNTRL->regs->CRL = (TFT_CNTRL->regs->CRL & 0xFFFF0000) | 0x00003333;

         gotTouch=false;
        touchX=calculateX(p.x);
        touchY=calculateY(p.y);
//this is a patched version, originally it was: if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        if (touchX>20) {
                gotTouch = true;
                gotDoubleTap=false;
                int deltaTime = millis()-lastTapTime;
                if(deltaTime<=doubleTapMaxTime && deltaTime>doubleTapMinTime) {
                        if(abs(last_touchX-touchX) + abs(last_touchY-touchY) <=2*diffTouchThreshold) {
                                gotDoubleTap = true;
                                //Serial.println("double tap!!");
                        }
                }
                lastTapTime = millis();
                last_touchX = touchX;
                last_touchY = touchY;
                //this will show a circle on touched point, useful for debugging
                TFT.fillCircle(touchX, touchY, 3, ILI9341_NAVY);

/*  Serial.print("touchX = "); Serial.print(touchX);
   Serial.print("\ttouchY = "); Serial.print(touchY);
   Serial.print("\tPressure = "); Serial.println(p.z);
 */
        }
        TFT.setRotation(PORTRAIT);
        if(gotTouch)  return true;
        else return false;
}

void Oscilloscope_touchActions(){
if(gotTouch){
  if(touched_centerY) {
          if(touched_left) {
             decreaseTimebase();
           }
          else if(touched_right) {
             increaseTimebase();
          }
          else if(touched_centerX) {
            incEdgeType();
          }
  }
  if(touched_centerX) {
          if(touched_top) {
          //  if(gotDoubleTap) increaseZoomFactor();
            increaseSamplingRate();

          }
          else if(touched_bottom){
          //  if(gotDoubleTap) increaseZoomFactor();
              decreaseSamplingRate();

           }
  }

//  showLabels();
}
}

void touchPos(){
        // actions on duble tap
        touched_left=false,touched_right=false,touched_top=false,touched_bottom=false,touched_centerX=false,touched_centerY=false;

                        if(touchX<TFT_WIDTH/3) {
                                Serial.println("touch on  left");
                                touched_left = true;
                        }
                        else if(touchX>TFT_WIDTH*2/3) {
                                Serial.println("touch on  right");
                                touched_right = true;
                        }
                        else touched_centerX = true;



                        if(touchY<TFT_HEIGHT/3) {
                                Serial.println("touch on  top");
                                touched_top=true;
                        }
                        else if(touchY>TFT_HEIGHT*2/3) {
                                Serial.println("touch on  bottom");
                                touched_bottom = true;
                        }
                        else touched_centerY = true;




}

void setup()
{


        usb.begin(115200);
        adc_calibrate(ADC1);
        adc_calibrate(ADC2);
        setADCs (); //Setup ADC peripherals for interleaved continuous mode.

        if (!bmp.begin()) usb.println("bmp sensor init failed, check wiring!");
              powerMeter.init();
        // The test pulse is a square wave of approx 3.3V (i.e. the STM32 supply voltage) at approx 1 kHz
        // "The Arduino has a fixed PWM frequency of 490Hz" - and it appears that this is also true of the STM32F103 using the current STM32F03 libraries as per
        // STM32, Maple and Maple mini port to IDE 1.5.x - http://forum.arduino.cc/index.php?topic=265904.2520
        // therefore if we want a precise test frequency we can't just use the default uncooked 50% duty cycle PWM output.


  #define  TEST_WAVE_FREQ 1000 //1kHz

        timer_set_period(Timer3, (1000000/TEST_WAVE_FREQ)); //This is in uS. For 1000Hz we have (1s=10^6us) T=10^6us/10^3Hz = 10^3us
        //toggleTestWaveOn();  // moved elsewhere

        // Set up our sensor pin(s)
        pinMode(analogInPin, INPUT_ANALOG); // this is the scope wave input
        pinMode(FREQ_COUNT_PIN, INPUT); // this is tied to scope wave input too(via 1k resistor), but is used to count frequency

        pinMode(INDUCTANCE_METER_IN_PIN, OUTPUT);
        pinMode(INDUCTANCE_METER_OUT_PIN, INPUT);

        TFT.begin();
        // initialize the display
        clearTFT();
        TFT.setRotation(PORTRAIT);
        myHeight   = TFT.width();
        myWidth  = TFT.height();
        TFT.setTextColor(CURSOR_COLOUR, BEAM_OFF_COLOUR);

        TFT.setRotation(LANDSCAPE);
        //  TFT.setFont(&TomThumb); this is the smallest font available
        clearTFT();
//  showGraticule();
        showCredits(); // Honourable mentions ;¬)
        delay(3000); //5000
        clearTFT();
        notTriggered = true;
        trunkHeight++;

      //interrupt for freq counter was here, moved it to the UI of the latter
}

void readSerial(){

}


void Oscilloscope(){
  if ( !triggerHeld  )
  {
          // Wait for trigger
          trigger();
          if ( !notTriggered )
          {
              //    blinkLED();

                  // Take our samples
                  takeSamples();

                  //Blank  out previous plot
                  TFTSamplesClear(BEAM_OFF_COLOUR);

                  // Show the showGraticule
                  showGraticule();

                  //Display the samples
                  TFTSamples(BEAM1_COLOUR);
                  displayTime = (micros() - displayTime);

                  //getVpp();
                  getVoltages();

                  freqCounter();

                  // Display the Labels ( uS/Div, Volts/Div etc).
                  showLabels();
                  displayTime = micros();

          }else {
                  showGraticule();
          }

  }

  // Wait before allowing a re-trigger
  delay(retriggerDelay);
  // DEBUG: increment the sweepDelayFactor slowly to show the effect.
  // sweepDelayFactor ++;
}



void choiceScreen(){
if(screenChanged){ // caled once, in the beginning
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(LANDSCAPE);

  TFT.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
  TFT.fillRect(0, BOXSIZE, BOXSIZE, BOXSIZE, ILI9341_GREEN);
  TFT.fillRect(0, BOXSIZE*2, BOXSIZE, BOXSIZE, ILI9341_BLUE);
  TFT.fillRect(0, BOXSIZE*3, BOXSIZE, BOXSIZE, ILI9341_CYAN);
//  TFT.fillRect(0, BOXSIZE*4, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
//  TFT.fillRect(0, BOXSIZE*5, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
powerMeter_enabled=false;
scope_enabled=false;
screenChanged = false;
}

TFT.setRotation(LANDSCAPE);
TFT.setTextSize(3);
  TFT.setCursor(BOXSIZE+20, 15);
  TFT.print("Power Meter");

  TFT.setCursor(BOXSIZE+20, BOXSIZE+15);
  TFT.print("Oscilloscope");

  TFT.setCursor(BOXSIZE+20, BOXSIZE*2+15);
  TFT.print("Freq. Counter");

  TFT.setCursor(BOXSIZE+20, BOXSIZE*3+15);
  TFT.print("Induct. Meter");

if(gotTouch){
  if(touchY<BOXSIZE){  //choice 0
    screenChanged =true;
    trunkHeight++;
    branch=0;
    TFT.fillScreen(ILI9341_BLACK);

  }
  if(touchY>BOXSIZE&&touchY<BOXSIZE*2){ //choice 1
    screenChanged =true;
    trunkHeight++;
    branch=1;
    TFT.fillScreen(ILI9341_BLACK);

  }
  if(touchY>BOXSIZE*2&&touchY<BOXSIZE*3){ //choice 2
    screenChanged =true;
    trunkHeight++;
    branch=2;
    TFT.fillScreen(ILI9341_BLACK);

  }
  if(touchY>BOXSIZE*3&&touchY<BOXSIZE*4){ //choice 3
    screenChanged =true;
    trunkHeight++;
    branch=3;
    TFT.fillScreen(ILI9341_BLACK);

  }

}

}

void cyclesCounterISR(){
  cyclesCount++;
}

void freqCounter(){ // just the background logic
  freqCounter_deltaTime = micros()-lastMeasureTime;
  if(freqCounter_deltaTime>=measureInterval){
    lastMeasureTime=micros();
    frequency = float(1000000)*float(cyclesCount)/float(freqCounter_deltaTime);
    cyclesCount=0;

}
}

void freqCounterUI(){
  if(screenChanged){ //use this like a setup()
  //freqCounter_enabled = true;
  attachInterrupt(FREQ_COUNT_PIN,cyclesCounterISR,FALLING);
  toggleTestWaveOn();
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(LANDSCAPE);

  usb.println("freq counter init");

//TODO: inidicate working range as above 1kHz
  TFT.setTextSize(2);

  TFT.setCursor((TFT_WIDTH/2)-20,10);
  TFT.print("Frequency:");

  //attachInterrupt(analogInPin,cyclesCounterISR,RISING);

  screenChanged=false;
}

freqCounter();

  TFT.setRotation(LANDSCAPE);
  TFT.setCursor(0,30);
  TFT.print(frequency);
  TFT.print(" Hz");

  TFT.setCursor(0,60);
  TFT.print(freqCounter_deltaTime);
  TFT.print(" uS");

}

double getInductance(){
  double pulse,frequency,capacitance,inductance;
  capacitance = INDUCTANCE_METER_FIXED_CAPACITANCE;

  digitalWrite(INDUCTANCE_METER_IN_PIN,HIGH);
  delay(5);
  //give some time to charge inductor.
  digitalWrite(INDUCTANCE_METER_IN_PIN,LOW);
  delayMicroseconds(100);
  //make sure resination is measured

  //pulse in tumeout for smaller inductors could be 5000

  pulse=pulseIn(INDUCTANCE_METER_OUT_PIN,HIGH,10000);

  //returns 0 if timeout
  if(pulse>0.1){
    //if a timeout did not occur and it took a reading:
  frequency=1.E6/(2*pulse);
  inductance=1./(capacitance*frequency*frequency*4.*3.14159*3.14159);
  inductance*=1E6;  //note that this is the same as saying inductance = inductance*1E6
  inductance*=2.; //for some reason, was returning half the expected value
  return inductance;
}

}

void inductanceMeterUI(){

  if(screenChanged){ //use this like a setup()
  //inductanceMeter_enabled = true;

  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(LANDSCAPE);

//TODO  inidcate working range: 80- 30000 uH

  TFT.setTextSize(2);
  TFT.setCursor((TFT_WIDTH/2)-20,10);
  TFT.print("Inductance:");

  //attachInterrupt(analogInPin,cyclesCounterISR,RISING);

  screenChanged=false;
}

  double inductance = getInductance();

  TFT.setRotation(LANDSCAPE);
  TFT.setCursor(0,30);

  if(inductance<1.e3){
  TFT.print(inductance);
  TFT.print(" uH  ");
}
else if(inductance>1.e3 && inductance<1.e6){
  TFT.print(inductance/1.e3);
  TFT.print(" mH  ");
}
else if(inductance>1.e6 && inductance<1.e9){
  TFT.print(inductance/1.e6);
  TFT.print(" H  ");
}

}



void powerMeterUI(){
  if(screenChanged){
  powerMeter_enabled = true;
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(LANDSCAPE);
  TFT.setTextSize(2);
  screenChanged=false;
}
TFT.setRotation(LANDSCAPE);
TFT.setCursor(0,10);
TFT.print("Power:");
TFT.print(powerMeter.readPower());
TFT.print("  W");
TFT.setCursor(0,30);
TFT.print("Temperature:");
TFT.print(bmp.readTemperature());
TFT.print("*C");
TFT.setCursor(0,50);
TFT.print("Delta T:");
TFT.print(powerMeter.getDeltaTemp());
TFT.print("*C");
TFT.setCursor(0,70);
TFT.print("Pressure:");
TFT.print(bmp.readPressure());
TFT.print(" Pa");

int reset_btn_region_x = (TFT_WIDTH/2)-40;
int reset_btn_region_y = TFT_HEIGHT-25;
TFT.setCursor(reset_btn_region_x,reset_btn_region_y);
TFT.print("RESET");
if(gotTouch){
  if(touched_bottom) powerMeter.init();
}
}

void UI(){
  /*
  0| intro
  1| choose:(scope,power_meter,wave_gen)
  2| power_meter   scope   freq_counter
  */
  if(trunkHeight==1){
choiceScreen();
scope_enabled =false;
powerMeter_enabled = false;
  }
  else if(trunkHeight==2){
    if(branch==0){ //power_meter
      powerMeterUI();
    }
    else if(branch==1){ // oscilloscope
      if(screenChanged){
      scope_enabled = true;
      attachInterrupt(FREQ_COUNT_PIN,cyclesCounterISR,FALLING);
      toggleTestWaveOn();
      showGraticule();
      showLabels();
      screenChanged=false;
      }
      Oscilloscope_touchActions();
      Oscilloscope();

    }

    else if(branch==2){
      freqCounterUI();
    }
    else if(branch==3){
      inductanceMeterUI();
    }
  }

}

void loop()
{
  #if defined TOUCH_SCREEN_AVAILABLE
        if (readTouch()) {
                touchPos();
      }
  #endif
        readSerial();

        UI();
}

void showGraticule()
{
        TFT.drawRect(0, 0, myHeight, myWidth, GRATICULE_COLOUR);
        // Dot grid - ten distinct divisions (9 dots) in both X and Y axis.
        for (uint16_t TicksX = 1; TicksX < 10; TicksX++)
        {
                for (uint16_t TicksY = 1; TicksY < 10; TicksY++)
                {
                        TFT.drawPixel(  TicksX * (myHeight / 10), TicksY * (myWidth / 10), GRATICULE_COLOUR);
                }
        }
        // Horizontal and Vertical centre lines 5 ticks per grid square with a longer tick in line with our dots
        for (uint16_t TicksX = 0; TicksX < myWidth; TicksX += (myHeight / 50))
        {
                if (TicksX % (myWidth / 10) > 0 )
                {
                        TFT.drawFastHLine(  (myHeight / 2) - 1, TicksX, 3, GRATICULE_COLOUR);
                }
                else
                {
                        TFT.drawFastHLine(  (myHeight / 2) - 3, TicksX, 7, GRATICULE_COLOUR);
                }

        }
        for (uint16_t TicksY = 0; TicksY < myHeight; TicksY += (myHeight / 50) )
        {
                if (TicksY % (myHeight / 10) > 0 )
                {
                        TFT.drawFastVLine( TicksY,  (myWidth / 2) - 1, 3, GRATICULE_COLOUR);
                }
                else
                {
                        TFT.drawFastVLine( TicksY,  (myWidth / 2) - 3, 7, GRATICULE_COLOUR);
                }
        }
}

void setADCs ()
{
        //  const adc_dev *dev = PIN_MAP[analogInPin].adc_device;
        int pinMapADCin = PIN_MAP[analogInPin].adc_channel;
        adc_set_sample_rate(ADC1, adc_sampling_time); //=0,58uS/sample.  ADC_SMPR_13_5 = 1.08uS - use this one if Rin>10Kohm,
        adc_set_sample_rate(ADC2, adc_sampling_time); // if not may get some sporadic noise. see datasheet.

        //  adc_reg_map *regs = dev->regs;
        adc_set_reg_seqlen(ADC1, 1);
        ADC1->regs->SQR3 = pinMapADCin;
        ADC1->regs->CR2 |= ADC_CR2_CONT; // | ADC_CR2_DMA; // Set continuous mode and DMA
        ADC1->regs->CR1 |= ADC_CR1_FASTINT; // Interleaved mode
        ADC1->regs->CR2 |= ADC_CR2_SWSTART;

        ADC2->regs->CR2 |= ADC_CR2_CONT; // ADC 2 continuos
        ADC2->regs->SQR3 = pinMapADCin;
}


// Crude triggering on positive or negative or either change from previous to current sample.
void trigger()
{
        notTriggered = true;
        switch (triggerType) {
        case 1:
                triggerNegative();
                triggerType_str="neg  ";
                break;
        case 2:
                triggerPositive();
                triggerType_str="pos  ";
                break;
        case 3:
                triggerAlways();
                triggerType_str="any  ";
                break;
        default:
                triggerBoth();
                triggerType_str="both ";

                break;
        }
}

void triggerAlways(){

      triggerPoints[0] = analogRead(analogInPin);
      notTriggered=false;
      triggerPoints[0] = triggerPoints[1]; //analogRead(analogInPin);


}

void triggerBoth()
{
        triggerPoints[0] = analogRead(analogInPin);
        while(notTriggered) {
                triggerPoints[1] = analogRead(analogInPin);
                if ( ((triggerPoints[1] < triggerValue) && (triggerPoints[0] > triggerValue)) ||
                     ((triggerPoints[1] > triggerValue) && (triggerPoints[0] < triggerValue)) ) {
                        notTriggered = false;
                }
                triggerPoints[0] = triggerPoints[1]; //analogRead(analogInPin);
        }
}

void triggerPositive() {
        triggerPoints[0] = analogRead(analogInPin);
        while(notTriggered) {
                triggerPoints[1] = analogRead(analogInPin);
                if ((triggerPoints[1] > triggerValue) && (triggerPoints[0] < triggerValue) ) {
                        notTriggered = false;
                }
                triggerPoints[0] = triggerPoints[1]; //analogRead(analogInPin);
        }
}

void triggerNegative() {
        triggerPoints[0] = analogRead(analogInPin);
        while(notTriggered) {
                triggerPoints[1] = analogRead(analogInPin);
                if ((triggerPoints[1] < triggerValue) && (triggerPoints[0] > triggerValue) ) {
                        notTriggered = false;
                }
                triggerPoints[0] = triggerPoints[1]; //analogRead(analogInPin);
        }
}

void incEdgeType() {
        triggerType += 1;
        if (triggerType > 3)
        {
                triggerType = 0;
        }
        /*
           usb.println(triggerPoints[0]);
           usb.println(triggerPoints[1]);
           usb.println(triggerType);
         */
}

void clearTFT()
{
        TFT.fillScreen(BEAM_OFF_COLOUR);          // Blank the display
}



// Grab the samples from the ADC
// Theoretically the ADC can not go any faster than this.
//
// According to specs, when using 72Mhz on the MCU main clock,the fastest ADC capture time is 1.17 uS. As we use 2 ADCs we get double the captures, so .58 uS, which is the times we get with ADC_SMPR_1_5.
// I think we have reached the speed limit of the chip, now all we can do is improve accuracy.
// See; http://stm32duino.com/viewtopic.php?f=19&t=107&p=1202#p1194

void takeSamples ()
{
        // This loop uses dual interleaved mode to get the best performance out of the ADCs
        //

        dma_init(DMA1);
        dma_attach_interrupt(DMA1, DMA_CH1, DMA1_CH1_Event);

        adc_dma_enable(ADC1);
        dma_setup_transfer(DMA1, DMA_CH1, &ADC1->regs->DR, DMA_SIZE_32BITS,
                           dataPoints32, DMA_SIZE_32BITS, (DMA_MINC_MODE | DMA_TRNS_CMPLT));// Receive buffer DMA
        dma_set_num_transfers(DMA1, DMA_CH1, maxSamples / 2);
        dma1_ch1_Active = 1;
        //  regs->CR2 |= ADC_CR2_SWSTART; //moved to setADC
        dma_enable(DMA1, DMA_CH1); // Enable the channel and start the transfer.
        //adc_calibrate(ADC1);
        //adc_calibrate(ADC2);
        samplingTime = micros();
        while (dma1_ch1_Active);
        samplingTime = (micros() - samplingTime);
        kSamples_per_second = float(maxSamples*1000)/samplingTime;
        timePerSample = float (float(samplingTime) / float(maxSamples));
        dma_disable(DMA1, DMA_CH1); //End of trasfer, disable DMA and Continuous mode.
        // regs->CR2 &= ~ADC_CR2_CONT;

}

void TFTSamplesClear (uint16_t beamColour)
{
        for (signalX=1; signalX < myWidth - 2; signalX++)
        {
                //use saved data to improve speed
                TFT.drawLine (  dataPlot[signalX-1], signalX, dataPlot[signalX], signalX + 1, beamColour);
        }
}


void getVpp(){
        int step = maxSamples/VPP_SAMPLES;
        vmin_raw =ANALOG_MAX_VALUE;
        vmax_raw =0;
        for(int i=0; i<VPP_SAMPLES; i++) {

                vmax_raw = max(dataPoints[i*step],vmax_raw);
                vmin_raw = min(dataPoints[i*step],vmin_raw);

        }
        float voltage_factor = ANALOG_MAX_VOLTAGE/ANALOG_MAX_VALUE;
        vmin = vmin_raw*voltage_factor;
        vmax = vmax_raw*voltage_factor;
        Vpp = vmax-vmin;

}

// the function below extends getVpp to also get Vrms;
void getVoltages(){
        int step = maxSamples/VPP_SAMPLES;
        vmin_raw =ANALOG_MAX_VALUE;
        vmax_raw =0;
        float squared_samples_sum_raw =0;
        for(int i=0; i<VPP_SAMPLES; i++) {

                vmax_raw = max(dataPoints[i*step],vmax_raw);
                vmin_raw = min(dataPoints[i*step],vmin_raw);
                squared_samples_sum_raw += (dataPoints[i*step])*(dataPoints[i*step]);
        }
        float voltage_factor = ANALOG_MAX_VOLTAGE/ANALOG_MAX_VALUE;
        vmin = vmin_raw*voltage_factor;
        vmax = vmax_raw*voltage_factor;
        Vpp = vmax-vmin;

        Vrms=sqrt(squared_samples_sum_raw/VPP_SAMPLES);
        Vrms*=voltage_factor;

}


void TFTSamples (uint16_t beamColour)
{
        //calculate first sample
        signalY =  ((myHeight * dataPoints[0 * ((endSample - startSample) / (myWidth * timeBase / 100)) + 1]) / ANALOG_MAX_VALUE) * (yZoomFactor / 100) + yPosition;
        dataPlot[0]=signalY * 99 / 100 + 1;

        for (signalX=1; signalX < myWidth - 2; signalX++)
        {

                // Scale our samples to fit our screen. Most scopes increase this in steps of 5,10,25,50,100 250,500,1000 etc
                // Pick the nearest suitable samples for each of our myWidth screen resolution points
                signalY1 = ((myHeight * dataPoints[(signalX + 1) * ((endSample - startSample) / (myWidth * timeBase / 100)) + 1]) / ANALOG_MAX_VALUE) * (yZoomFactor / 100) + yPosition;
                dataPlot[signalX] = signalY1 * 99 / 100 + 1;
                TFT.drawLine (  dataPlot[signalX-1], signalX, dataPlot[signalX], signalX + 1, beamColour);
                signalY = signalY1;

        }


}

/*
   // Run a bunch of NOOPs to trim the inter ADC conversion gap
   void sweepDelay(unsigned long sweepDelayFactor) {
   volatile unsigned long i = 0;
   for (i = 0; i < sweepDelayFactor; i++) {
    __asm__ __volatile__ ("nop");
   }
   }
 */

void showLabels()
{
        TFT.setRotation(LANDSCAPE);
        TFT.setTextSize(1);

      /*
        TFT.setCursor(10, 160);
        TFT.print( bmp.readTemperature());
        TFT.print(" C  ");
        */

        TFT.setCursor(10, 190);
        // TFT.print("Y=");
        //TFT.print((samplingTime * xZoomFactor) / maxSamples);
        //  TFT.print(timePerSample);
        TFT.print(kSamples_per_second);
        TFT.print("kS/s ");
        //  TFT.print(displayTime);
        //TFT.print(float (1000000 / float(displayTime)));
        TFT.print(int(1000000 / displayTime));
        TFT.print("fps ");
        TFT.print("timeBase=");
        TFT.print(timeBase);
        TFT.print(" yzoom=");
        TFT.print(yZoomFactor);
        //TFT.print(" ypos=");
        //TFT.print(yPosition);
        TFT.print(" trig=");
        TFT.print(triggerType_str);

/*
//TFT.print(maxSamples);
//  TFT.print(" samples ");
TFT.print(inputFrequency);
//  TFT.print("-");
 TFT.print(" Hz ");
//  TFT.setCursor(10, 190);
        TFT.setTextSize(1);
*/
        TFT.setCursor(10, 210);
        TFT.print("0.3");
        TFT.print(" V/Div ");

        TFT.print(Vpp);
        TFT.print("Vpp ");

        TFT.print(vmax);
        TFT.print("Vm ");

        TFT.print(Vrms);
        TFT.print("Vrms ");

        TFT.print(frequency);
        TFT.print(" Hz  ");


        TFT.setCursor(10,10);
        TFT.print(vmax*factor_p6);
        TFT.print("Vm6 ");

        TFT.print(Vrms*factor_p6);
        TFT.print("Vrms6 ");

        TFT.setRotation(PORTRAIT);
}



void serialSamples ()
{
        // Send *all* of the samples to the serial port.
        usb.println("#Time(uS), ADC Number, value, diff");
        for (int16_t j = 1; j < maxSamples; j++ )
        {
                // Time from trigger in milliseconds
                usb.print((samplingTime / (maxSamples))*j);
                usb.print(" ");
                // raw ADC data
                usb.print(j % 2 + 1);
                usb.print(" ");
                usb.print(dataPoints[j] );
                usb.print(" ");
                usb.print(dataPoints[j] - dataPoints[j - 1]);
                usb.print(" ");
                usb.print(dataPoints[j] - ((dataPoints[j] - dataPoints[j - 1]) / 2));
                usb.print("\n");

                // delay(100);


        }
        usb.print("\n");
}

void toggleHold()
{
        triggerHeld ^= 1;
        //usb.print("# ");
        //usb.print(triggerHeld);
        if (triggerHeld)
        {
                usb.println("# Toggle Hold on");
        }
        else
        {
                usb.println("# Toggle Hold off");
        }
}

void toggleSerial() {
        serialOutput = !serialOutput;
        usb.println("# Toggle Serial");
        serialSamples();
}

void unrecognized(const char *command) {
        usb.print("# Unknown Command.[");
        usb.print(command);
        usb.println("]");
}

void decreaseTimebase() {
        clearTrace();
        /*
           sweepDelayFactor =  sweepDelayFactor / 2 ;
           if (sweepDelayFactor < 1 ) {

           usb.print("Timebase=");
           sweepDelayFactor = 1;
           }
         */
        if (timeBase > 100)
        {
                timeBase -= 100;
        }
        showTrace();
        usb.print("# Timebase=");
        usb.println(timeBase);

}

void increaseTimebase() {
        clearTrace();
        usb.print("# Timebase=");
        if (timeBase < 10000)
        {
              timeBase += 100;
        }
        //sweepDelayFactor = 2 * sweepDelayFactor ;
        showTrace();
        usb.print("# Timebase=");
        usb.println(timeBase);
}

void increaseZoomFactor() {
        clearTrace();
        if ( xZoomFactor < 21) {
                xZoomFactor += 1;
        }
        showTrace();
        usb.print("# Zoom=");
        usb.println(xZoomFactor);

}

void decreaseZoomFactor() {
        clearTrace();
        if (xZoomFactor > 1) {
                xZoomFactor -= 1;
        }
        showTrace();
        Serial.print("# Zoom=");
        Serial.println(xZoomFactor);
        //clearTFT();
}

void clearTrace() {
        TFTSamples(BEAM_OFF_COLOUR);
        showGraticule();
}

void showTrace() {
        showLabels();
        TFTSamples(BEAM1_COLOUR);
}

void scrollRight() {
        clearTrace();
        if (startSample < (endSample - 120)) {
                startSample += 100;
        }
        showTrace();
        Serial.print("# startSample=");
        Serial.println(startSample);


}

void scrollLeft() {
        clearTrace();
        if (startSample > (120)) {
                startSample -= 100;
                showTrace();
        }
        Serial.print("# startSample=");
        Serial.println(startSample);

}

void increaseYposition() {

        if (yPosition < myHeight ) {
                clearTrace();
                yPosition++;
                showTrace();
        }
        Serial.print("# yPosition=");
        Serial.println(yPosition);
}

void decreaseYposition() {

        if (yPosition > -myHeight ) {
                clearTrace();
                yPosition--;
                showTrace();
        }
        Serial.print("# yPosition=");
        Serial.println(yPosition);
}


void increaseTriggerPosition() {

        if (triggerValue < ANALOG_MAX_VALUE ) {
                triggerValue += TRIGGER_POSITION_STEP; //trigger position step
        }
        Serial.print("# TriggerPosition=");
        Serial.println(triggerValue);
}

void decreaseTriggerPosition() {

        if (triggerValue > 0 ) {
                triggerValue -= TRIGGER_POSITION_STEP; //trigger position step
        }
        Serial.print("# TriggerPosition=");
        Serial.println(triggerValue);
}

void atAt() {
        usb.println("# Hello");
}

void toggleTestWaveOn () {
        pinMode(TEST_WAVE_PIN, OUTPUT);
        analogWrite(TEST_WAVE_PIN, 75);
        usb.println("# Test Pulse On.");
}

void toggleTestWaveOff () {
        pinMode(TEST_WAVE_PIN, INPUT);
        usb.println("# Test Pulse Off.");
}

uint16 timer_set_period(HardwareTimer timer, uint32 microseconds) {
        if (!microseconds) {
                timer.setPrescaleFactor(1);
                timer.setOverflow(1);
                return timer.getOverflow();
        }

        uint32 cycles = microseconds * (72000000 / 1000000); // 72 cycles per microsecond

        uint16 ps = (uint16)((cycles >> 16) + 1);
        timer.setPrescaleFactor(ps);
        timer.setOverflow((cycles / ps) - 1 );
        return timer.getOverflow();
}

/**
 * @brief Enable DMA requests
 * @param dev ADC device on which to enable DMA requests
 */

void adc_dma_enable(const adc_dev * dev) {
        bb_peri_set_bit(&dev->regs->CR2, ADC_CR2_DMA_BIT, 1);
}


/**
 * @brief Disable DMA requests
 * @param dev ADC device on which to disable DMA requests
 */

void adc_dma_disable(const adc_dev * dev) {
        bb_peri_set_bit(&dev->regs->CR2, ADC_CR2_DMA_BIT, 0);
}

static void DMA1_CH1_Event() {
        dma1_ch1_Active = 0;
}



void showCredits() {
        TFT.setTextSize(2);                     // Small 26 char / line
        //TFT.setTextColor(CURSOR_COLOUR, BEAM_OFF_COLOUR) ;
        TFT.setCursor(0, 50);
        TFT.print("     multiScope");
        TFT.setCursor(0, 90);
        TFT.print("Max bandwidth: 1MHz");
        TFT.setCursor(0, 110);
        TFT.print("Max sampling: 1.7MSP/s");
        TFT.setCursor(0, 130);
        TFT.print("Max mcu pin voltage: 3.3V");
        TFT.setCursor(0, 150);
        String tmp=""; tmp+="Test wave ("; tmp+=TEST_WAVE_FREQ; tmp+="Hz"; tmp+=") on ";
        TFT.print(tmp);
        TFT.print("PB1");
        TFT.setCursor(0, 170);
        TFT.print("CH1 Probe on ");
        TFT.print("PB0");
        TFT.setCursor(0, 220);
        TFT.setTextSize(2);
        TFT.setRotation(PORTRAIT);
}
