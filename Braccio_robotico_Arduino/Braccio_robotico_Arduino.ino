/** SKETCH MOVIMENTO BRACCIO ROBOTICO
 *  
 *  Autori: Olivero Tommaso, Coppola Carmine Mattia
 *  4^A ROB
 *  21/02/2022
 */

#include <Servo.h>

///////////////////////// JOYSTICK /////////////////////////

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

/////////////////// MOTORI BASE BRACCIO ///////////////////

const int xAtt = 0;
const int xOld = 0;

Servo BASE_DX;
Servo BASE_SX;

const int base_dx = 5;
const int base_sx = 6;

int valoreBase_dx = 0;
int valoreBase_sx = 0;

/////////////////// MOTORI META BRACCIO ///////////////////

Servo BRACCIO_DX;
Servo BRACCIO_SX;

const int braccio_dx = 3;
const int braccio_sx = 4;

int valoreBraccio_dx = 0;
int valoreBraccio_sx = 0;

/////////////////// PULSANTE MOTORI PINZA/////////////////

Servo PINZA;

const int pinzaPot = A2;
const int pinza = 7;


int valorePinza = 0;

//////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  BASE_DX.attach(base_dx);
  BASE_SX.attach(base_sx);

  BRACCIO_DX.attach(braccio_dx);
  BRACCIO_SX.attach(braccio_sx);

  PINZA.attach(pinza);
}

//////////////////////////////////////////////////

void loop() {
  int x = analogRead(JOYSTICK_X);
  int y = analogRead(JOYSTICK_Y);

  valorePinza = analogRead(pinzaPot);

  valorePinza = map(valorePinza,  0, 1023, 0, 180);
  int posizionex = map(x, 0, 1023, -10, 10);
  int posizioney = map(y, 0, 1023, -10, 10);

  Serial.println("x :       " + String(x));
  Serial.println("x :" + String(y));
  
  if(x>505 && x <512){
    posizionex=0;
  }
  
  if(y>505 && y <512){
    posizioney=0;
  }
  
 
  valoreBase_dx += posizionex;
  
  if(valoreBase_dx<0){
    valoreBase_dx=0;
  }
  
  if(valoreBase_dx>180){
    valoreBase_dx=180;
  }
  
  valoreBase_sx =180 - valoreBase_dx;


  valoreBraccio_dx += posizioney;
  
  if(valoreBraccio_dx<0){
    valoreBraccio_dx=0;
  }
  
  if(valoreBraccio_dx>180){
    valoreBraccio_dx=180;
  }
  
  valoreBraccio_sx =180 - valoreBraccio_dx;


////////////// rivedere //////////////////////
  //if(statoButt == HIGH){
    //valorePinza += 1;
  //}
/////////////////////////////////////////////

  
  //Serial.println("gradi" + String(valoreBase_dx));
  
  BASE_DX.write(valoreBase_dx);
  BASE_SX.write(valoreBase_sx);

  BRACCIO_DX.write(valoreBraccio_dx);
  BRACCIO_SX.write(valoreBraccio_sx);

  PINZA.write(valorePinza);
  
  delay(10);

}
