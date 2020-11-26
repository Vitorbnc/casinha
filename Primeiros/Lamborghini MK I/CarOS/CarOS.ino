// Software do Carro Lamborghini para controle via Bluetooth

#include <Servo.h> 
 
Servo accel;  // create servo object to control a servo 
Servo turn;
 
const int acpin =3; // constantes dos pinos dos servos
const int trnpin=2;
//------------------------
//Variáveis de leitura de dados seriais
const int fields =3;
int values_a[fields];
int fieldindex = 0;
int values[fields];

//-------------------------

void setup() 
{ 
  startservos();
  Serial1.begin(115200);
  Serial.begin(9600); 
  
} 
 
void loop() 
{
if (Serial1.available()){
readSerial1();
firstreading();
} 

}
//------------------------------------------------------
void startservos (){
  accel.attach(acpin);  // attaches the servo on its pin
  turn.attach(trnpin);
  accel.write(85); //ângulo mínimo de 70, médio de 85, máximo de 130
  turn.write(110);//ângulo mínimo de 10, médio de 110, máximo de 170
  
}
//----------------------------------------------------------
void readservos(){

String accelang = "Angulo do servo aceleracao = ";
accelang += accel.read();
Serial1.println(accelang);

String turnang = "Angulo do servo direcao = ";
turnang += turn.read();
Serial1.println(turnang);
}

void readSerial1(){
//  Esta função espera 3 campos de dados numéricos separados por vírgula 
if( Serial1.available())
{
char ch = Serial1.read();

if(ch >= '0' && ch <= '9' || ch == '-') // is this an ascii digit between 0 and 9?
{
// yes, accumulate the value if the fieldIndex is within range
// additional fields are not stored
if(fieldindex < fields) {
values_a[fieldindex] = (values_a[fieldindex] * 10) + (ch - '0');
}
}
else if (ch == ',') // comma is our separator, so move on to the next field
{
fieldindex++; // increment field index
}
else
{
values[0] = values_a[0];
values[1] = values_a[1];
values[2] = values_a[2];
for(int i=0; i < min(fields, fieldindex+1); i++)
{
Serial.println(values[i]);
values_a[i] = 0; // set the values to zero, ready for the next message
}
fieldindex = 0; // ready to start over
}
}
/* Código de teste para verificar os valores
------------------------------
Serial.print( fieldindex);
Serial.println(" fields received:");
for(int i=0; i < fieldindex; i++)
{
Serial1.println(values[i]);
}
-----------------------------
*/
}
void firstreading (){
  // Função de leitura, para tomada de decisões, adicionar casos aqui
  // Primeiro campo, sistema específico
  switch (values[0]){
    case 1:
    servocommand();
    break;
  }
}
 void servocommand (){
   // Função para comando dos servos
   int accelvalue = map(values[2],1,200,85,130);
   int turnvalue = map(values[2],1,200,50,170);
   switch (values[1]){
    case 1:
    accel.write(accelvalue);
    break;
    case 2:
    turn.write(turnvalue);
    break;
   }
   }
