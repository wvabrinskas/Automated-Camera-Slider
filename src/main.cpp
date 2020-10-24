/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <Motor/Motor.h>
#include <Screen/Screen.h>

Screen screen = Screen();
Motor motor = Motor();

void setup() {
  screen.start();
  screen.setPosition(0);
  screen.setSpeed(DEFAULT_SPEED);
}

void moveTo(int position, int speed) {
  motor.moveTo(position, speed);
}

void loop() {
  screen.update();
}
