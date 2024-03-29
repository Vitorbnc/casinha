#include <PS2X_lib.h>                         /* PS2 Controller Library */
/*
 * IMPORTANTE: INCLUA GRANDES CAPACITORES NA SAÍDA DO REG. 3.3V QUE ALIMENTA O LORA E O CONTROLE PS2
 * INCLUA UM CAPACITOR ENTRE VCC E GND DO LORA
 * REDUZI A VELOCIDADE DO SPI A 250000
 * SE ISSO NÃO FOR FEITO, O CONTROLE PODERÁ REINICIAR QUANDO O LORA TRANSMITE
 * 
 * Protocolo antigo: header é >
 * protoc. Novo: header é $
 * O protocolo novo é usado no LoRa
 * O protocolo antigo é enviado pelo serial, por razões de compatibilidade
 */


#include <SPI.h>
#include <LoRa.h>

char payload[6] =">R80FF"; // Should be constant size. Example: >R8080 means right joystick, x = 128, y= 255. > is header


PS2X ps2x;                                    /* create PS2 Controller Class*/
byte Type = 0;
int vibrate = 0;
int RX=0,RY=0,LX=0,LY=0;
int lastRX,lastRY,lastLX,lastLY;
                  //(amarelo,azul),(verde a cinza)

//protocol specific
String header=">ctl.";
String trailer=")\n";
String tmpGlob="";

int value;

// Variables used by the Interpreter

const int dirFields=2;  // Set your number of dirs here
const int argFields=5;  //Set your number of args here
String dir[dirFields];
String strArg[argFields];
int intArg[argFields];
bool hasStrArg[argFields];
bool hasIntArg[argFields];
// Use the following if you want to check for args, commands or forwardables
bool hasArgs=false;
bool gotCmd=false;
bool gotFwd = false;

long startTime, endTime;

String forwardable;
String cmd;

#define uart Serial


/* ------------------------------
Code: Vítor Barbosa (vitorbarbosanc@gmail.com)

Don't forget to upload data alongside with this code to your ESP

ESP8266 tested configs:
  Blue model: 512K Flash, 64KB SPIFFS
  Black model: 1M Flash, 64KB SPIFFS
*/

/*
 * New simple radio protocol
 * U/D/L/R -> key up, down or left/right joystick value
 * {ST, SE, UP, DO, LE, RI, SQ, CI, TR, CR, R1, R2, R3, L1, L2, L3} and 00; or 2 values value 0-255  in hex (00 - FF)for joysticks' x and y
 * 
 */


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
   joysticks --> LJ, RJ
  DPad --> up,down,left,right 
   other buttons --> start, back/sel, 1,2,3,4   (1,2,3,4 are buttons numbered from the uppermost, clockwise)

   For PS2,PS3,PSX --> 1,2,3,4 are Triangle,Circle, Cross, Square

 */

 void cleanInterpreter(){
         gotFwd=false;
         gotCmd=false;
         forwardable="";
         /* // clean dirs only if necessary
          for(int i=0;i<dirFields;i++){
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



void setup(){
        uart.begin(250000);
        cleanInterpreter();
        delay(1000);
        ps2x.config_gamepad(A0,A1,A2,A3, true, true); /* setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error*/
        //ps2x.config_gamepad(2,3,4,5, true, true); /* setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error*/

        Type = ps2x.readType();                  /* Reading type of the PS2 Ccontroller */
        //delay(5000);
        LoRa.setPins(7, 8); //SS, RESET
        LoRa.setSPIFrequency(250000);
        if (!LoRa.begin(433E6)) {
        uart.println("Starting LoRa failed!");
        }
        
}


void radioWrite(String msg, char header='$'){
  if(header!=0) msg = String(header)+ msg;
  
  uart.println(msg); 
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
 
}



void readJoys(){
  String tmp="";

        LY = ps2x.Analog(PSS_LY);     /* Reading Left stick Y axis */
        LX = ps2x.Analog(PSS_LX);     /* Reading Left stick X axis */
        RY = ps2x.Analog(PSS_RY);     /* Reading Right stick Y axis */
        RX = ps2x.Analog(PSS_RX);     /* Reading Right stick X axis */
        if(LY!=lastLY||LX!=lastLX) {
                String x = String(LX,HEX);
                String y = String(LY,HEX);
                if(x.length()==1) x = String("0") + x;
                if(y.length()==1) y = String("0") + y;
                
                tmp="L";
                tmp+=x; tmp+=y;
                radioWrite(tmp);
                  
                tmp=header; tmp+="LJ(";
                tmp+=LX; tmp+=","; tmp+=LY; tmp+=trailer;
                uart.print(tmp);

                lastLY=LY; lastLX=LX;
        }
        if(RY!=lastRY||RX!=lastRX) {
                String x = String(RX,HEX);
                String y = String(RY,HEX);
                if(x.length()==1) x = String("0") + x;
                if(y.length()==1) y = String("0") + y;
                
                tmp="R";
                tmp+=x; tmp+=y;
                radioWrite(tmp);
                
                tmp=header; tmp+="RJ(";
                tmp+=RX; tmp+=","; tmp+=RY; tmp+=trailer;
                uart.print(tmp);
                lastRY=RY; lastRX=RX;
        }
}

void readBtns(){
  String tmp="";
        if(ps2x.NewButtonState()) {    /* will be TRUE if any button changes state  */
    
                //-------------
                if(ps2x.ButtonReleased(PSB_L2))       {
                        tmp=header; tmp+="LRel("; tmp+="L2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UL2--");

                }
                if(ps2x.ButtonReleased(PSB_L1))       {
                        tmp=header; tmp+="LRel("; tmp+="L1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UL1--");

                }
                if(ps2x.ButtonReleased(PSB_L3))       {
                        tmp=header; tmp+="LRel("; tmp+="L3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UL3--");

                }
                //----------
                if(ps2x.ButtonReleased(PSB_R2))  {
                        tmp=header; tmp+="RRel("; tmp+="R2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UR2--");
                }

                if(ps2x.ButtonReleased(PSB_R1))  {
                        tmp=header; tmp+="RRel("; tmp+="R1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UR1--");
                }
                if(ps2x.ButtonReleased(PSB_R3))  {
                        tmp=header; tmp+="RRel("; tmp+="R3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UR3--");
                }
                //----------
                if(ps2x.ButtonReleased(PSB_PAD_UP))       {
                        tmp=header; tmp+="DRel("; tmp+="up"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UUP--");
                }
                if(ps2x.ButtonReleased(PSB_PAD_DOWN))  {
                        tmp=header; tmp+="DRel("; tmp+="down"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UDO--");
                }

                if(ps2x.ButtonReleased(PSB_PAD_LEFT))       {
                        tmp=header; tmp+="DRel("; tmp+="left"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("ULE--");
                }
                if(ps2x.ButtonReleased(PSB_PAD_RIGHT))  {
                        tmp=header; tmp+="DRel("; tmp+="right"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("URI--");
                }

//---------------------

                if(ps2x.ButtonReleased(PSB_START))      {
                        tmp=header; tmp+="rel("; tmp+="start"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UST--");
                }

                if(ps2x.ButtonReleased(PSB_SELECT))      {
                        tmp=header; tmp+="rel("; tmp+="back/sel"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("USE--");
                }
                if(ps2x.ButtonReleased(PSB_GREEN))      {//triangle
                        tmp=header; tmp+="rel("; tmp+="1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UTR--");
                }
                if(ps2x.ButtonReleased(PSB_RED))      {//circle
                        tmp=header; tmp+="rel("; tmp+="2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UCI--");
                }
                if(ps2x.ButtonReleased(PSB_BLUE))      {//cross
                        tmp=header; tmp+="rel("; tmp+="3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("UCR--");
                }
                if(ps2x.ButtonReleased(PSB_PINK))      {//square
                        tmp=header; tmp+="rel("; tmp+="4"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("USQ--");
                }

//----------------------------------------------------------------------------------------------
                if(ps2x.ButtonPressed(PSB_L2))      {
                        tmp=header; tmp+="LPsd("; tmp+="L2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DL2--");
                }

                if(ps2x.ButtonPressed(PSB_L1))      {
                        tmp=header; tmp+="LPsd("; tmp+="L1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DL1--");
                }

                if(ps2x.ButtonPressed(PSB_L3))      {
                        tmp=header; tmp+="LPsd("; tmp+="L3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DL3--");
                }
//-------------
                if(ps2x.ButtonPressed(PSB_R2))      {
                        tmp=header; tmp+="RPsd("; tmp+="R2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DR2--");
                }

                if(ps2x.ButtonPressed(PSB_R1))      {
                        tmp=header; tmp+="RPsd("; tmp+="R1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DR1--");
                }
                if(ps2x.ButtonPressed(PSB_R3))      {
                        tmp=header; tmp+="RPsd("; tmp+="R3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DR3--");
                }
                //---------------
                if(ps2x.ButtonPressed(PSB_PAD_UP))      {
                        tmp=header; tmp+="DPsd("; tmp+="up"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DUP--");
                }

                if(ps2x.ButtonPressed(PSB_PAD_DOWN))      {
                        tmp=header; tmp+="DPsd("; tmp+="down"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DDO--");
                }
                if(ps2x.ButtonPressed(PSB_PAD_LEFT))      {
                        tmp=header; tmp+="DPsd("; tmp+="left"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DLE--");
                }

                if(ps2x.ButtonPressed(PSB_PAD_RIGHT))      {
                        tmp=header; tmp+="DPsd("; tmp+="right"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DRI--");
                }

                if(ps2x.ButtonPressed(PSB_START))      {
                        tmp=header; tmp+="psd("; tmp+="start"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DST--");
                }

                if(ps2x.ButtonPressed(PSB_SELECT))      {
                        tmp=header; tmp+="psd("; tmp+="back/sel"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DSE--");
                }
                if(ps2x.ButtonPressed(PSB_GREEN))      { //triangle
                        tmp=header; tmp+="psd("; tmp+="1"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DTR--");
                }
                if(ps2x.ButtonPressed(PSB_RED))      { //circle
                        tmp=header; tmp+="psd("; tmp+="2"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DCI--");
                }
                if(ps2x.ButtonPressed(PSB_BLUE))      { //cross
                        tmp=header; tmp+="psd("; tmp+="3"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DCR--");
                }
                if(ps2x.ButtonPressed(PSB_PINK))      { //square
                        tmp=header; tmp+="psd("; tmp+="4"; tmp+=trailer;
                        uart.print(tmp);
                        radioWrite("DSQ--");
                }

        }

}

void loop(){

        ps2x.read_gamepad(false, vibrate); /* read controller and set large motor to spin at 'vibrate' speed */
        readJoys();
        readBtns();
        //readStreams();
}


void printData(){
  for(int i=0;i<dirFields;i++){
    uart.print("dir "); uart.print(i); uart.print(":");
    uart.println(dir[i]);
  }
  for(int i=0;i<argFields;i++){
    uart.print("strArg "); uart.print(i); uart.print(":");
    uart.println(strArg[i]);
    uart.print("intArg "); uart.print(i); uart.print(":");
    uart.println(intArg[i]);
  }
}

void interpret(){
// Uncomment the line below to print every dir and arg. Useful for debugging or understanding this code
//printData();

/*if(strcmp(dir[0].c_str(),"wifi")==0){
  if(strcmp(dir[1].c_str(),"led")==0){
    uart.println("command is: wifi.led");

   }
}
*/

if(strcmp(dir[0].c_str(),"ctl")==0){
  if(strcmp(dir[1].c_str(),"vibrate")==0){
    vibrate =intArg[0];

   }
}


// try >friends(Batman,Iron Man)
else if(strcmp(dir[0].c_str(),"dbg")==0){
//  uart.println("got dbg");
String txt = "";txt+=dir[1];txt+=":";
for(int i=0;i<argFields;i++){

  if(hasStrArg[i]){
    if(i>0) txt+=",";
    txt+= strArg[i];
  }
  else if (hasIntArg[i]){
    if(i>0) txt+=",";
     txt+=intArg[i];
  }
}


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
                int dotIndex = rawTxt.indexOf('.');
                rawTxt.setCharAt(dotIndex,',');
                int commaIndex = rawTxt.indexOf(',',old_commaIndex+1);

                if(commaIndex!=-1) {
                        tmp= rawTxt.substring(old_commaIndex+1,commaIndex);
                        char c =  tmp.charAt(0);
                        if(c=='.') c=',';
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
