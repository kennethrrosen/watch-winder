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
  Limit switch: 4, Sporadic Rotation Change/other (advance/override loop/not needed for my watch)
  DIR: 6
  STEP: 7
  EN: 8
  OB2: BLK
  OB1: GRN
  OA1: RED
  OA2: BLU
  MS1: VIO (16 steps enabled)
  MS2: VIO (16 Steps enabled)
  9V: VIN
  VM: 5v from Arduino 
  GND: GND to Arduino GND

  Stepper Motor: 
  NEMA11, 1.8° step angle (200 steps/revolution), with each phase drawing 670 mA at 3.5 V

  For My Watch (TPD Calculation): 
  Luxury Automatic (Powermatic 80) - Directional requirements: CCW 800 (TPD: Turns Per Day)
  https://www.orbita.com/winder-support/

  Other Watch Winder INOs: 
  https://www.instructables.com/Dual-Automatic-Watch-Winder/
  https://github.com/goldcove/Easy-Watch-Winder/blob/master/watchwinder.ino

*/
#include <Debouncer.h>

int pin = 18;
int debounce_duration_ms = 50;
int rise_count = 0;
int fall_count = 0;

boolean limit;

Debouncer debouncer(pin, debounce_duration_ms);

#define EN_PIN    7
#define STEP_PIN  6
#define DIR_PIN   5
#define LIM_PIN  18
#define RX_PIN    0
#define TX_PIN    1

void setup() {
  // Push at the start of setting up the driver resets the register to default
  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(EN_PIN, LOW);    // Enable driver in hardware

  pinMode(LIM_PIN, INPUT_PULLUP);

}

void winderCCW() {
  limit = digitalRead(LIM_PIN);
  digitalWrite(DIR_PIN, HIGH);        // HIGH = CCW LOW= CW
  for (int i = 0; i < 160000; i++) {  //800TPD
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delay(1);
    if (limit == false); {
      i = 160001;
      break;
    }
    delay(50);
  }
}

void winderCW() {
  limit = digitalRead(LIM_PIN);
  digitalWrite(DIR_PIN, LOW);        // HIGH = CCW LOW= CW
  for (int i = 0; i < 160000; i++) {  //800TPD
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delay(1);
    if (limit == false); {
      i = 160001;
      break;
    }
    delay(50);
  }
}

/*void limOptions() {
    delay(50);
  }
*/
void loop() {
  if (limit == false) {
    winderCW();   //limOptions = alternate winder rotate on long button press; pause on short press
  }
  else if (limit == true) {
    winderCCW();
  }
}

/*

NOTES FOR limOptions
====================

const int SHORT_PRESS_TIME = 1000; 
const int LONG_PRESS_TIME  = 5000;

int lastState = LOW;  
int currentState;     
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

currentState = digitalRead(LIM_PIN);

if (lastState == HIGH && currentState == LOW)        // button is pressed
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if (pressDuration < SHORT_PRESS_TIME )
      //SWITCH TO CLOCKWISE

    if (pressDuration > LONG_PRESS_TIME )
      //PAUSE FOR 30 SECONDS
  }

  // save the the last state
  lastState = currentState;
}

*/
