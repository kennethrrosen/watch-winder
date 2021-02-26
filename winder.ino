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
#include <TMC2208Stepper.h>

#define EN_PIN    8  
#define STEP_PIN  7  
#define RX_PIN    0  
#define TX_PIN    1  

// Create driver that uses SoftwareSerial for communication
TMC2208Stepper driver = TMC2208Stepper(RX_PIN, TX_PIN);

void setup() {
  driver.beginSerial(115200);
  // Push at the start of setting up the driver resets the register to default
  driver.push();
  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);

  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(640);      // Set driver current = 500mA, 0.5 multiplier for hold current and RSENSE = 0.11.
  driver.toff(2);               // Enable driver in software

  digitalWrite(EN_PIN, LOW);    // Enable driver in hardware
}

void loop() {
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
  delay(1);
}