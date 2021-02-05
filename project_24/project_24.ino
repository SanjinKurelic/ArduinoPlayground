#include <Motor.h>
#include <Stopwatch.h>

#define SOINC_TRIG 8
#define SOINC_ECHO 9

const unsigned long TURN = 480;

const float OBSTACLE_DISTANCE = 25;

const byte STATE_FORWARD = 1;
const byte STATE_GO_RIGHT = 2;
const byte STATE_RETURN_LEFT = 3;

Motor motor(22, 23, 28, 25, 24, 29);
Stopwatch sw;
byte state;
boolean obstacle;

void setup() {
  pinMode(SOINC_TRIG, OUTPUT);
  pinMode(SOINC_ECHO, INPUT);
  state = STATE_FORWARD;
}

void loop() {
  // flag if obstacle is infront
  obstacle = (check_obstacle() <= OBSTACLE_DISTANCE);
  
  switch (state) {
    case STATE_FORWARD:
      if (obstacle) {
        motor.stop_both_motors();
        sw.reset();
        motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
        state = STATE_GO_RIGHT;
      } else {
        motor.start_driving_forward(motor.MAX_SPEED);
      }
      break;
    case STATE_GO_RIGHT:
      if (sw.has_elapsed(TURN)) {        
        motor.stop_both_motors();
        if (obstacle) {
          sw.reset();
          motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
          state = STATE_RETURN_LEFT;
        } else {
          state = STATE_FORWARD;
        }
      }
      break;
    case STATE_RETURN_LEFT:
      if (sw.has_elapsed(TURN * 2)) {
        sw.reset();
        motor.stop_both_motors();
        state = STATE_FORWARD;
      }
      break;
  }  
}

float check_obstacle() {
  digitalWrite(SOINC_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(SOINC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SOINC_TRIG, LOW);

  return (pulseIn(SOINC_ECHO, HIGH) / 2.0) / 29.1;
}
