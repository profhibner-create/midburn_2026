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
  // if {play == false} {
  //   offline_play_track();
  //   offline_periodic_lighting();
  // }
  // if 
  // Initial state, play, is False
  // Pressing buzzer transfers play to True
  // Something happens
  // Return play to False
}

