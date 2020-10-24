/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <Screen/Screen.h>

Screen screen = Screen();

void setup() {
  screen.start();
}

void loop() {
  screen.update();
}
