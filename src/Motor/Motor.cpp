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

void Motor::home() {
  int endStop = digitalRead(X_END_STOP_PIN);
  setPosition(0);

  while (endStop == HIGH) {
    stepper.setSpeed(this->speed);
    endStop = digitalRead(X_END_STOP_PIN);
    moveToPosition();
  }
}

void Motor::run() {
  setPosition(X_MAX * X_STEPS_PER_MM);

  while (stepper.distanceToGo() != 0) {
    stepper.setSpeed(this->speed);
    moveToPosition();
  }
}

void Motor::toggleSteppers() {
  int stepperEnabled = digitalRead(X_ENABLE_PIN);
  digitalWrite(X_ENABLE_PIN, stepperEnabled == HIGH ? LOW : HIGH);
}

void Motor:: setSteppersEnabled(bool enabled) {
  digitalWrite(X_ENABLE_PIN, enabled == true ? LOW : HIGH);
}

void Motor::setPosition(float position) {
  stepper.moveTo(position);   
}

void Motor::setSpeed(float speed) {
  stepper.setSpeed(speed);
}

void Motor::moveToPosition() {
  stepper.runSpeedToPosition();
}

void Motor::move() {
  stepper.runSpeed();
}