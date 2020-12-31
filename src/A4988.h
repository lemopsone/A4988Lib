#pragma once
#include <Arduino.h>
/*
 * A4988 - stepper motor driver library
 * Copyright (C)2020 Maxim Varchenko
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
class A4988 {
protected:
  static const uint8_t MS[];
  short ms1;
  short ms2;
  short ms3;
  short dir_pin;
  short step_pin;
  float motor_deg;
  short microsteps;
  long encoder;
  float rpm;
  long prev_time = 0;
  long delay_;
  float dst = 1;
  int mode = 0;
  long distance;
  int dir_ = HIGH;
public:
  A4988(float motor_deg, short dir_pin, short step_pin, short ms1, short ms2, short ms3);
  void setupDriveUnit(short threadPitch, short threadStarts);
  void setMicrostep(short microsteps);
  long setRPM(float rpm);
  uint8_t* getMS();
  void move_();
  void move(int mode, long distance);
  void setDeg(long degree);
  void moveABS(int mode, long distance);
  void setEncoder(int mode, long distance);
  long getEncoder();
  void updateEncoder(long degree);
};
