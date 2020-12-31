/*
 * Examples of using the library
 * 
 * Copyright (C)2020 Maxim Varchenko
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <A4988.h>                                      //include the library itself
/*
 * Driver configs
 */
#define DIR 9                                           //DIR pin port of A4988
#define STEP 10                                         //STEP pin port of A4988
#define MS1 3                                           //MS1 pin port of A4988
#define MS2 5                                           //MS2 pin port of A4988
#define MS3 6                                           //MS3 pin port of A4988
/*
 * Motor configs
 */
float RPM = 1;                                            //Revolutions per minute (be careful, max speed depends on the motor and can cause issues if RPM is more than max value)
#define MOTOR_DEG 1.8                                   //Motor step size (for most motors it's 1.8 degrees or 200 steps per revolution, see in your motor specifications)
/*
 * Modes of movement
 */
#define DEG 0                                           //Set the movement mode to "DEGREES"
#define MM 1                                            //Set the movement mode to "MILLIMETRES"
/*
 * Pitch properties, to move for certain distance in millimetres
 */
#define PITCH 4                                         //Size of thread pitch
#define STARTS 1                                        //Ammount of thread pitch starts

A4988 stepper(MOTOR_DEG, DIR, STEP, MS1, MS2, MS3);     //Setup the motor to use "stepper" as a class reference

void setup() {  
  Serial.begin(9600);                                   //Start serial port of Arduino to check the properties
  int a = 0;
  stepper.setupDriveUnit(PITCH, STARTS);                //Setup drive unit (use only in case you want to be able to move for millimetres)
  stepper.setMicrostep(1);                              //Set the microstep of motor (A4988 supports 1, 2, 4, 8, 16 microsteps)
  stepper.setRPM(RPM);                                  //Set the speed of motor
  
  stepper.move(MM, 4);                                  //Move for 4 millimetres
  a = stepper.getEncoder();                             //Get the current encoder value
  Serial.println(a);                                    //Print current value to the serial port
  
  stepper.moveABS(MM, -10);                             //Move to the point where encoder equals -10
  a = stepper.getEncoder();                             //Get the current encoder value
  Serial.println(a);                                    //Print current value to the serial port
  
  stepper.move(DEG, 360);                               //Make a full backward revolution (move for -360 degrees)
  a = stepper.getEncoder();                             //Get the current encoder value
  Serial.println(a);                                    //Print current value to the serial port
  
  stepper.setDeg(77);                                   //Move to the point where degree equals 77
  a = stepper.getEncoder();                             //Get the current encoder value
  Serial.println(a);                                    //Print current value to the serial port
}
void loop() {
  delay(1);
}
