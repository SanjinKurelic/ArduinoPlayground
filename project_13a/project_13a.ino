#include <Motor.h>
#include <Stopwatch.h>

const unsigned long CAMERA_SETUP = 5000;
const unsigned long MOTOR_TURN = 9000;
const unsigned long MOTOR_FORWARD = 1000;

const byte STATE_START = 1;
const byte STATE_POINT_A = 2;
const byte STATE_A_TO_B = 3;
const byte STATE_POINT_B = 4;
const byte STATE_TO_END = 5;
const byte STATE_END = 6;

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
      state = STATE_POINT_A;
      sw.reset();
    }
    break;

    case STATE_POINT_A:
      if (sw.has_elapsed(MOTOR_FORWARD)) {
        motor.start_turning_left(motor.MAX_SPEED, motor.HARD);
        state = STATE_A_TO_B;
        sw.reset();
      }
      break;
      
    case STATE_A_TO_B:
      if (sw.has_elapsed(MOTOR_TURN)) {
        motor.start_driving_forward(motor.MAX_SPEED);
        state = STATE_POINT_B;
        sw.reset();
      }
      break;

    case STATE_POINT_B:
      if (sw.has_elapsed(MOTOR_FORWARD)) {
        motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
        state = STATE_TO_END;
        sw.reset();
      }
      break;
      
    case STATE_TO_END:
      if (sw.has_elapsed(MOTOR_TURN)) {
        motor.start_driving_forward(motor.MAX_SPEED);
        state = STATE_END;
        sw.reset();
      }
      break;

    case STATE_END:
      if (sw.has_elapsed(MOTOR_FORWARD)) {
        motor.stop_both_motors();
        sw.disable();
      }
      break;
  }
}
