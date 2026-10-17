#include <FastLED.h>
#include "definitions.h"
#include "setup_and_loop.h"

// Non-blocking timer variables for the built-in LED
unsigned long lastBlinkTime = 0;
const int period = 100; 
bool ledState = LOW;

void setup() {
  my_setup();
  pinMode(LED_BUILTIN, OUTPUT);     
}

void loop() {
  // 1. Non-blocking LED blink (replaces blocking delays)
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime >= period) {
    lastBlinkTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }

  // 2. Continuous processor engine for audio & FastLED
  my_loop();
}
