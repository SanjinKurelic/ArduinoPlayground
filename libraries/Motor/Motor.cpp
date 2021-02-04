#include "Arduino.h"
#include "Motor.h"

Motor::Motor(byte motor_left_pwr, byte motor_left_gnd, byte motor_left_pwm, byte motor_right_pwr, byte motor_right_gnd, byte motor_right_pwm) {
  MOTOR_LEFT[0] = motor_left_pwr;
  MOTOR_LEFT[1] = motor_left_gnd;
  MOTOR_LEFT[2] = motor_left_pwm;
  MOTOR_RIGHT[0] = motor_right_pwr;
  MOTOR_RIGHT[1] = motor_right_gnd;
  MOTOR_RIGHT[2] = motor_right_pwm;

  pinMode(MOTOR_LEFT[0], OUTPUT);
  pinMode(MOTOR_LEFT[1], OUTPUT);
  pinMode(MOTOR_LEFT[2], OUTPUT);
  pinMode(MOTOR_RIGHT[0], OUTPUT);
  pinMode(MOTOR_RIGHT[1], OUTPUT);
  pinMode(MOTOR_RIGHT[2], OUTPUT);
}

void Motor::start_turning_left(short speed, float amount) { 
  short slower = (short)(amount * speed); 

  start_driving_forward_left_motor(slower);
  start_driving_forward_right_motor(speed);
}

void Motor::start_turning_right(short speed, float amount) {
  short slower = (short)(amount * speed); 
  
  start_driving_forward_left_motor(speed);
  start_driving_forward_right_motor(slower);
}

void Motor::start_driving_forward(short speed) {
  start_driving_forward_left_motor(speed);
  start_driving_forward_right_motor(speed);
}

void Motor::start_driving_backward(short speed) {
  start_driving_backward_left_motor(speed);
  start_driving_backward_right_motor(speed);
}

void Motor::stop_both_motors(){
  stop_left_motor();
  stop_right_motor();
}

void Motor::start_driving_forward_left_motor(short speed) {
  digitalWrite(MOTOR_LEFT[0], HIGH); 
  digitalWrite(MOTOR_LEFT[1], LOW);
  analogWrite(MOTOR_LEFT[2], speed);
}

void Motor::start_driving_backward_left_motor(short speed) {
  digitalWrite(MOTOR_LEFT[0], LOW); 
  digitalWrite(MOTOR_LEFT[1], HIGH);
  analogWrite(MOTOR_LEFT[2], speed);
}

void Motor::stop_left_motor() {
  digitalWrite(MOTOR_LEFT[0], LOW); 
  digitalWrite(MOTOR_LEFT[1], LOW);
  analogWrite(MOTOR_LEFT[2], 0);
}

void Motor::start_driving_forward_right_motor(short speed) {
  digitalWrite(MOTOR_RIGHT[0], HIGH); 
  digitalWrite(MOTOR_RIGHT[1], LOW);
  analogWrite(MOTOR_RIGHT[2], speed);
}

void Motor::start_driving_backward_right_motor(short speed) {
  digitalWrite(MOTOR_RIGHT[0], LOW); 
  digitalWrite(MOTOR_RIGHT[1], HIGH);
  analogWrite(MOTOR_RIGHT[2], speed);
}

void Motor::stop_right_motor() {
  digitalWrite(MOTOR_RIGHT[0], LOW); 
  digitalWrite(MOTOR_RIGHT[1], LOW);
  analogWrite(MOTOR_RIGHT[2], 0);
}
