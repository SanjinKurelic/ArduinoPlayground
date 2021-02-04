#include <Motor.h>

#define BLACK_LINE 1
#define IC_PIN_1 2 // left
#define IC_PIN_2 3 // left !
#define IC_PIN_3 4
#define IC_PIN_4 5 // right !
#define IC_PIN_5 6 // right

Motor motor(22, 23, 28, 25, 24, 29);

void setup() {
  pinMode(IC_PIN_1, INPUT);
  pinMode(IC_PIN_2, INPUT);
  pinMode(IC_PIN_3, INPUT);
  pinMode(IC_PIN_4, INPUT);
  pinMode(IC_PIN_5, INPUT);
}

bool check_ic(int pin) {
  return digitalRead(pin) == BLACK_LINE;
}

void loop() {  
  // line goes left
  if (check_ic(IC_PIN_1) or check_ic(IC_PIN_2)) {
    motor.start_turning_left(motor.MAX_SPEED, motor.HARD);
  }
  // line goes right
  if (check_ic(IC_PIN_5) or check_ic(IC_PIN_4)) { 
    motor.start_turning_right(motor.MAX_SPEED, motor.HARD);
  }
  // line is in the middle
  if (check_ic(IC_PIN_3)) {
    motor.start_driving_forward(motor.MAX_SPEED);
  }
}
