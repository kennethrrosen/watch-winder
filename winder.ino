/*
SIMPLE WATCH WINDER
  by: Questionable Mechanics
  contact: questionable.mechanics@gmail.com
  last rev: 02/2021
  This sketch is in the public domain
  
  Notes: 
  Developed and tested using Arduino IDE ver 1.8.42.0 in VS Code
  BTT TMC2008-V3.0 Driver

  Pinout:
  Toggle Switch: For On/Off Battery (not connected to arduino)
  Push-button: Reset
  Limit switch: 7, Sporadic Rotation Change/other (advance/override loop/not needed for my watch)
  DIR: 4
  STEP: 5
  EN: 6
  OB2: BLK/GRN
  OB1: GRN/BLK
  OA1: RED/BLU 
  OA2: BLU/RED
  MS1: VIO (16 steps enabled)
  MS2: VIO (16 Steps enabled)
  9V: VIN
  VM: 5v from Arduino 
  GND: GND to reset switch

  Stepper Motor: 
  NEMA11, 1.8° step angle (200 steps/revolution), with each phase drawing 670 mA at 3.5 V

  For My Watch (TPD Calculation): 
  Luxury Automatic (Powermatic 80) - Directional requirements: CCW 800 (TPD: Turns Per Day)
  https://www.orbita.com/winder-support/

  Other Watch Winder INOs: 
  https://www.instructables.com/Dual-Automatic-Watch-Winder/
  https://github.com/goldcove/Easy-Watch-Winder/blob/master/watchwinder.ino

*/

#include <AccelStepper.h>
//#include <Stepper.h> 

int smDirectionPin = 4; //Direction
int smStepPin = 5; //Stepper
int tpd;
int turndirection; //Motor turnning direction. 0=both, 1=clockwise, 2=counterclockwise. In accordance with your watch requirements.

boolean limitSwitch 7
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

void setup(){
  myStepper.setSpeed(60); // set the speed at 60 rpm:
  pinMode(smDirectionPin, OUTPUT);
  pinMode(smStepPin, OUTPUT);
  pinMode(limitSwitch, INPUT);
  Serial.begin(9600);
}
 
void loop(){

 myStepper.step(stepsPerRevolution);
 myStepper.step(-stepsPerRevolution);

  digitalWrite(smDirectionPin, LOW); //Set the rotation direction (HIGH is clockwise;LOW is counter-clockwise).
  for (int i = 0; i < 160000; i++){ //800TPD
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(smStepPin, LOW);
  }

  if digitalRead(limitswitch = 1){
    digitalWrite(smDirectionPin, HIGH);
    digitalWrite(smStepPin, HIGH)
    delayMicroseconds(800);
    digitalWrite(smStepPin, LOW)
  }

  cw=0;
  ccw=0;
  limitSwitch (turndirection) {
    case 0: //both directions
      cw=turns/2;
      ccw=turns-cw; //in case odd number
      break;
    case 1: //clockwise
      cw=turns;
      break;
    case 2: //counterclockwise
      ccw=turns;
      break;

    delay(540000) //30 minute break
}