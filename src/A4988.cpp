/*
 * A4988 - stepper motor driver library
 * Copyright (C)2020 Maxim Varchenko
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include "A4988.h"
/*
 * 0bMS3,MS2,MS1 for 1,2,4,8,16 microsteps
*/
const uint8_t A4988::MS[]={0b000, 0b001, 0b010, 0b011, 0b111};
A4988::A4988(float motor_deg, short dir_pin, short step_pin, short ms1, short ms2, short ms3)
{
    pinMode(ms1, OUTPUT);
    pinMode(ms2, OUTPUT);
    pinMode(ms3, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    digitalWrite(dir_pin, HIGH);
    pinMode(step_pin, OUTPUT);
    digitalWrite(step_pin, LOW);
    this->motor_deg = motor_deg;
    
}

void A4988::setupDriveUnit(short threadPitch, short threadStarts){
    dst = (threadPitch * threadStarts);
}

void A4988::setMicrostep(short microsteps){
    const uint8_t* msTable = getMS();
    size_t tableSize = sizeof(msTable);
    unsigned short i = 0;
    while (i < tableSize){
        if(microsteps & (1<<i)){
            uint8_t x = msTable[i];
            digitalWrite(ms3, x & 4);
            digitalWrite(ms2, x & 2);
            digitalWrite(ms1, x & 1);
            break;
        }
        i++;
    }
}

long A4988::setRPM(float rpm){
    long delay_ = rpm * 6 / this->motor_deg;
}

void A4988::updateEncoder(long degree){
    encoder += degree;
}
long A4988::getEncoder(){
    return encoder;
}

uint8_t* A4988::getMS(){
    return A4988::MS;
}

void A4988::move(int mode, long distance){
    this->dir_ = (distance >= 0) ? HIGH : LOW;
    if (digitalRead(dir_pin) != dir_){
        digitalWrite(dir_pin, dir_);
    }    
    if (mode ==1){
        distance=distance*360/dst;
    }
    distance = (distance >= 0) ? distance:-distance;
    unsigned long i = 0;
    while (i<distance){
        unsigned long now = micros();
        if (now - prev_time >= delay_){
            prev_time = now;
            move_();
            i+=motor_deg;
        }
    }
    
}

void A4988::setEncoder(int mode, long distance){
    if (mode == 1){
        distance = distance * 360 / dst;
    }
    encoder = distance;
}

void A4988::setDeg(long degree){
    long e = getEncoder() % 360;
    degree = degree % 360;
    degree = (degree >= 0) ? degree : 360+degree;
    e = (e >= 0) ? e: 360+e;
    dir_ = (degree - e >= 0) ? HIGH : LOW;
    if (digitalRead(dir_pin) != dir_){
        digitalWrite(dir_pin, dir_);
    }
    
    long degree_ = (degree - e)%360;
    degree_ = (degree_ >= 0) ?  degree_ : -degree_;
    unsigned long i = 0;
    while (i < degree_){
        unsigned long now = micros();
        if (now - prev_time >= delay_){
            prev_time = now;
            move_();
            i += motor_deg;
        }
    }
}

void A4988::moveABS(int mode, long distance){
    long e = getEncoder();
    if (mode == 1){
        distance = distance * 360 / dst;
    }
    distance = distance - e;
    dir_ = (distance >= 0) ? HIGH : LOW;
    if (digitalRead(dir_pin) != dir_){
        digitalWrite(dir_pin, dir_);
    }
    distance = (distance >= 0) ? distance : -distance;
    unsigned long i = 0;
    while (i < distance){
        unsigned long now = micros();
        if (now - prev_time >= delay_){
            prev_time = now;
            move_();
            i+=motor_deg;
        }
   }
}

void A4988::move_(){
    digitalWrite(step_pin, HIGH);
    digitalWrite(step_pin, LOW);
    int a = (dir_ == HIGH) ? 1:-1;
    updateEncoder(motor_deg * a);
}

/*
 * To-do: add linear (accelerated) movement.
*/