#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class MotorControl{
    private:
        int speedControlPin1, speedControlPin2;
    public:
        MotorControl(int pin1, int pin2);
        ~MotorControl();
        void setSpeed(float speed);
};

#endif