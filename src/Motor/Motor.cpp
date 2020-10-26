#include "Motor.h"
#include "Configuration.h"

Motor::Motor() {

}

void Motor::setup() {
    pinMode(X_ENABLE_PIN, OUTPUT);
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);

    stepper.setMaxSpeed(DEFAULT_MAX_SPEED);
    stepper.setSpeed(DEFAULT_SPEED);
    stepper.setAcceleration(ACCELERATION);
    stepper.setPinsInverted(STEPPER_INVERTED);

    setSteppersEnabled(false);
}

void Motor::toggleSteppers() {
  int stepperEnabled = digitalRead(X_ENABLE_PIN);
  digitalWrite(X_ENABLE_PIN, stepperEnabled == HIGH ? LOW : HIGH);
}

void Motor:: setSteppersEnabled(bool enabled) {
  digitalWrite(X_ENABLE_PIN, enabled == true ? LOW : HIGH);
}

void Motor::moveTo(int position, int speed) {
  stepper.moveTo(position); 
  stepper.setSpeed(speed); 

  while (stepper.currentPosition() != stepper.targetPosition()) { 
    stepper.runSpeedToPosition();
  }
}

void Motor::setSpeed(float speed) {
  stepper.setSpeed(speed);
}

void Motor::move() {
  stepper.runSpeed();
}