#include <Motor.h>
#include <Stopwatch.h>

const unsigned long CAMERA_SETUP = 5000;
const unsigned long FULL_CIRCLE = 4850;
const unsigned long LED_BLINK = 500;

// States
const byte STATE_START = 1;
const byte STATE_RIGHT_EIGHT = 2;
const byte STATE_LEFT_EIGHT = 3;
const byte STATE_END = 4;

// Led states
const byte TURN_ON = 1;
const byte TURN_OFF = 2;

// Fine turn settings
const byte RIGHT_FINE_TURN = 1;
const byte LEFT_FINE_TURN = 2;
const unsigned long HARD_TURN = 100;
const unsigned long SOFT_TURN = 100;
const byte NO_TURN_STATE = 0;
const byte HARD_TURN_STATE = 1;
const byte SOFT_TURN_STATE = 2;
// End fine turn settings

Motor motor(22, 23, 28, 25, 24, 29);
Stopwatch fine_turn_sw, state_sw, led_sw;
byte fine_turn_state, state, turn_type, led_state;
byte laps_counter = 0, led_counter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  fine_turn_state = NO_TURN_STATE;
  state = STATE_START;
  led_state = TURN_OFF;
  led_sw.disable();
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

void showLapCounter() {
  if (led_sw.has_elapsed(LED_BLINK)) {
    if (led_state == TURN_OFF) {
      digitalWrite(LED_BUILTIN, HIGH);
      led_state = TURN_ON;

      led_counter++;
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      led_state = TURN_OFF;

      if (led_counter >= laps_counter - 1) {
        led_counter = 0;
        led_sw.disable();
      }
    }
  }
}

void loop() {
  switch (state) {
    case STATE_START:
      if (state_sw.has_elapsed(CAMERA_SETUP)) {
        state_sw.reset();

        fine_turn_state = HARD_TURN_STATE;
        turn_type = RIGHT_FINE_TURN;
        state = STATE_RIGHT_EIGHT;
      }
      break;

    case STATE_RIGHT_EIGHT:
      if (state_sw.has_elapsed(FULL_CIRCLE)) {
        laps_counter++;
        led_sw.reset();
        led_sw.enable();       
        state_sw.reset();

        fine_turn_state = HARD_TURN_STATE;
        turn_type = LEFT_FINE_TURN;
        state = STATE_LEFT_EIGHT; 
      }
    break;

    case STATE_LEFT_EIGHT:
      if (state_sw.has_elapsed(FULL_CIRCLE)) {
        state_sw.reset();

        fine_turn_state = HARD_TURN_STATE;
        turn_type = RIGHT_FINE_TURN;
        state = STATE_RIGHT_EIGHT;
      }
    break;

    case STATE_END:
      fine_turn_sw.disable();
      state_sw.disable();
  
      fine_turn_state = NO_TURN_STATE;
      turn_type = NO_TURN_STATE;
      motor.stop_both_motors();
    break;
  }

  // start = 1, first lap = 2 (so there is no negative value)
  if (laps_counter >= 6) {    
    state = STATE_END;
  }

  showLapCounter();
  fine_turn(turn_type);
}
