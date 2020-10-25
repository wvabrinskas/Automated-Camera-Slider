#include "Motor.h"

Motor::Motor() {
    pinMode(X_ENABLE_PIN, OUTPUT);
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);

    digitalWrite(X_ENABLE_PIN, LOW);

    stepper.setMaxSpeed(DEFAULT_MAX_SPEED);
    stepper.setSpeed(DEFAULT_SPEED);
}

void Motor::moveTo(int position, int speed) {
  stepper.moveTo(position); 
  stepper.setSpeed(speed); 

  while (stepper.currentPosition() != stepper.targetPosition()) { 
    stepper.runSpeedToPosition();
  }
}

void Motor::move() {
  stepper.runSpeed();
}