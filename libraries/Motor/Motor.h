#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "Arduino.h"

class Motor {
  private:
    byte MOTOR_LEFT[3];
    byte MOTOR_RIGHT[3];
    void start_driving_forward_left_motor(short speed);
    void start_driving_backward_left_motor(short speed);
    void stop_left_motor();
    void start_driving_forward_right_motor(short speed);
    void start_driving_backward_right_motor(short speed);
    void stop_right_motor();
  public:
    const short MAX_SPEED = 255;
    const float EASY = 0.9;
    const float MEDIUM = 0.75;
    const float HARD = 0;
    Motor(byte motor_left_pwr, byte motor_left_gnd, byte motor_left_pwm, byte motor_right_pwr, byte motor_right_gnd, byte motor_right_pwm);
    void start_turning_left(short speed, float amount);
    void start_turning_right(short speed, float amount);
    void start_driving_forward(short speed);
    void start_driving_backward(short speed);
    void stop_both_motors();
};

#endif