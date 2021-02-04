#include <Motor.h>
#include <Stopwatch.h>

const unsigned long CAMERA_SETUP = 5000;
const unsigned long HALF_CIRCLE = 2500;

// States
const byte STATE_START = 1;
const byte STATE_SIN = 2;
const byte STATE_END = 3;

// Fine turn settings
const byte RIGHT_FINE_TURN = 1;
const byte LEFT_FINE_TURN = 2;
const unsigned long HARD_TURN = 100;
const unsigned long SOFT_TURN = 200;
const byte NO_TURN_STATE = 0;
const byte HARD_TURN_STATE = 1;
const byte SOFT_TURN_STATE = 2;
// End fine turn settings

Motor motor(22, 23, 28, 25, 24, 29);
Stopwatch fine_turn_sw, state_sw;
byte fine_turn_state, state, turn_type;

void setup() {
  fine_turn_state = NO_TURN_STATE;
  state = STATE_START;
}

void fine_turn(byte turn_type) {
  if (fine_turn_state == HARD_TURN_STATE and fine_turn_sw.has_elapsed(SOFT_TURN)) {
    if (turn_type == RIGHT_FINE_TURN) {
      motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
    } else {
      motor.start_turning_left(motor.MAX_SPEED, motor.HARD);
    }
    fine_turn_state = SOFT_TURN_STATE;
    fine_turn_sw.reset();
  }
  else if (fine_turn_state == SOFT_TURN_STATE and fine_turn_sw.has_elapsed(HARD_TURN)) {
    motor.start_driving_forward(motor.MAX_SPEED);
    fine_turn_state = HARD_TURN_STATE;
    fine_turn_sw.reset();
  }
}

void loop() {
  switch (state) {
    case STATE_START:
      if (state_sw.has_elapsed(CAMERA_SETUP)) {
        state_sw.reset();

        fine_turn_state = HARD_TURN_STATE;
        turn_type = RIGHT_FINE_TURN;
        state = STATE_SIN;
      }
      break;

    case STATE_SIN:
      if (state_sw.has_elapsed(HALF_CIRCLE)) {
        state_sw.reset();

        fine_turn_state = HARD_TURN_STATE;
        turn_type = LEFT_FINE_TURN;
        state = STATE_END; 
      }
    break;

    case STATE_END:
      if (state_sw.has_elapsed(HALF_CIRCLE)) {
        fine_turn_sw.disable();
        state_sw.disable();

        fine_turn_state = NO_TURN_STATE;
        turn_type = NO_TURN_STATE;
        motor.stop_both_motors();
      }
    break;
  }

  fine_turn(turn_type);
}
