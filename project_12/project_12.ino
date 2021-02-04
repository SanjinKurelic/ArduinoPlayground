#include <Motor.h>
#include <Stopwatch.h>

const unsigned long CAMERA_SETUP = 5000;
const unsigned long MOTOR_FORWARD = 1000;
const unsigned long MOTOR_TURN_LEFT = 200;
const unsigned long MOTOR_TURN_RIGHT = 300;
const unsigned long MOTOR_DIAGONAL = 600;
const unsigned long MOTOR_BACKWARD = 300;

const byte STATE_START = 1;
const byte STATE_STOP_FORWARD = 2;
const byte STATE_STOP_LEFT = 3;
const byte STATE_STOP_DIAGONAL = 4;
const byte STATE_STOP_RIGHT = 5;
const byte STATE_STOP_BACKWARD = 6;
const byte STATE_END = 7;

Motor motor(22, 23, 28, 25, 24, 29);
Stopwatch sw;
byte state;

void setup() {
  state = STATE_START;
}

void loop() {
  switch (state) {
    case STATE_START:
    if (sw.has_elapsed(CAMERA_SETUP)) {
      motor.start_driving_forward(motor.MAX_SPEED);
      state = STATE_STOP_FORWARD;
      sw.reset();
    }
    break;

    case STATE_STOP_FORWARD:
      if (sw.has_elapsed(MOTOR_FORWARD)) {
        motor.start_turning_left(motor.MAX_SPEED, motor.HARD);
        state = STATE_STOP_LEFT;
        sw.reset();
      }
      break;
      
    case STATE_STOP_LEFT:
      if (sw.has_elapsed(MOTOR_TURN_LEFT)) {
        motor.start_driving_backward(motor.MAX_SPEED);
        state = STATE_STOP_DIAGONAL;
        sw.reset();
      }
      break;

    case STATE_STOP_DIAGONAL:
      if (sw.has_elapsed(MOTOR_DIAGONAL)) {
        motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
        state = STATE_STOP_RIGHT;
        sw.reset();
      }
      break;
      
    case STATE_STOP_RIGHT:
      if (sw.has_elapsed(MOTOR_TURN_RIGHT)) {
        motor.start_driving_backward(motor.MAX_SPEED);
        state = STATE_STOP_BACKWARD;
        sw.reset();
      }
      break;

    case STATE_STOP_BACKWARD:
      if (sw.has_elapsed(MOTOR_BACKWARD / 2)) {
        motor.start_driving_forward(motor.MAX_SPEED);
        state = STATE_END;
        sw.reset();
      }
      break;

    case STATE_END:
      if (sw.has_elapsed(MOTOR_BACKWARD)) {
        motor.stop_both_motors();
        sw.disable();
      }
      break;
  }
}
