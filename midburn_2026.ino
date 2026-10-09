#include <FastLED.h>
#include "definitions.h"
#include "setup_and_loop.h"

void setup() {
  my_setup();
  pinMode(LED_BUILTIN, OUTPUT);     

}

void loop() {
  int period = 100;
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(period);                             
  digitalWrite(LED_BUILTIN, LOW);   
  delay(period);                             

  my_loop();
}

