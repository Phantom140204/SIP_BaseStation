#include "MotorControl.h"

MotorControl::MotorControl(int pin1, int pin2){
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    speedControlPin1 = pin1;
    speedControlPin2 = pin2;
    analogWrite(speedControlPin1, 0);
    analogWrite(speedControlPin2, 0);
}

MotorControl::~MotorControl(){

}

void MotorControl::setSpeed(float speed){
    int speed_8bitValue = (abs(speed)/(100*1.0))*255; //Mapping 0-100 to 0-255
    if(speed >= 0 && speed <= 100){
        analogWrite(speedControlPin1, speed_8bitValue);
        analogWrite(speedControlPin2, 0);
    }
    else if(speed <=0 && speed >= -100){
        analogWrite(speedControlPin2, speed_8bitValue);
        analogWrite(speedControlPin1, 0);
    }
    else{
        analogWrite(speedControlPin1, 0);
        analogWrite(speedControlPin2, 0);
    }
}