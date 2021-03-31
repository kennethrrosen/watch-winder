/*
SIMPLE WATCH WINDER
  by: Questionable Mechanics
  contact: questionable.mechanics@gmail.com
  last rev: 03/2021
  This sketch is in the public domain
  
  Notes: 
  Developed and tested using Arduino IDE ver 1.8.42.0 in VS Code
  Lerdge® TMC2208 Stepper Motor Driver Module

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
    winderCW(); 
  }
  else if (limit == true) {
    winderCCW();
  }
}

/*
 * 
 * FOR EVENTUAL TACTILE SWITCH REPLACEMENT
 * 
unsigned long keyPrevMillis = 0;
const unsigned long keySampleIntervalMs = 25;
byte longKeyPressCountMax = 80;    // 80 * 25 = 2000 ms
byte longKeyPressCount = 0;

byte prevKeyState = HIGH;         // button is active low
const byte keyPin = 18;            // button is connected to pin 2 and GND


// called when button is kept pressed for less than 2 seconds
void shortKeyPress() {
    Serial.println("short");
}


// called when button is kept pressed for more than 2 seconds
void longKeyPress() {
    Serial.println("long");
}


// called when key goes from not pressed to pressed
void keyPress() {
    Serial.println("key press");
    longKeyPressCount = 0;
}


// called when key goes from pressed to not pressed
void keyRelease() {
    Serial.println("key release");
   
    if (longKeyPressCount >= longKeyPressCountMax) {
        longKeyPress();
    }
    else {
        shortKeyPress();
    }
}


void setup() {
    Serial.begin(9600);
    pinMode(keyPin, INPUT_PULLUP);
}


void loop() {
    // key management section
    if (millis() - keyPrevMillis >= keySampleIntervalMs) {
        keyPrevMillis = millis();
       
        byte currKeyState = digitalRead(keyPin);
       
        if ((prevKeyState == HIGH) && (currKeyState == LOW)) {
            keyPress();
        }
        else if ((prevKeyState == LOW) && (currKeyState == HIGH)) {
            keyRelease();
        }
        else if (currKeyState == LOW) {
            longKeyPressCount++;
        }
       
        prevKeyState = currKeyState;
    }


    // other code goes here
}*/
