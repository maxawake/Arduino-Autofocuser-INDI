/*
 * Microstepping demo
 *
 * This requires that microstep control pins be connected in addition to STEP,DIR
 *
 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 100

#define DIR 8
#define STEP 9

#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);


void setup() {
    Serial.begin(115200); 
	  Serial.setTimeout(1); 

    /*
     * Set target motor RPM.
     */
    stepper.begin(RPM);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
    stepper.enable();
    stepper.setMicrostep(16); 
    // set current level (for DRV8880 only). 
    // Valid percent values are 25, 50, 75 or 100.
    // stepper.setCurrent(100);
}

void loop() {
    // Check if data is available to read
    if (Serial.available() > 0) {
        // Read the incoming number
        int x = Serial.readString().toInt(); 
        
        if (x == 1) {
            stepper.move(MOTOR_STEPS);    // forward revolution
            Serial.println("Moving forward"); 
        } else if (x == 2) {
            stepper.move(-MOTOR_STEPS);   // reverse revolution
            Serial.println("Moving backward");
        } else if (x == 3) {
            stepper.rotate(360);     // forward revolution
            Serial.println("Rotating forward");
        } else if (x == 4) {
            stepper.rotate(-360);    // reverse revolution
            Serial.println("Rotating backward");
        }
    } 
}
