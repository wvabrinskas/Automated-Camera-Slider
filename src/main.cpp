/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <Screen/Screen.h>
#include "Configuration.h"

Screen screen = Screen();

void setup() {
  Serial.begin(115200);
  screen.start();
}

void loop() {
  screen.update();
}
