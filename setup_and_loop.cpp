#include <Arduino.h>      // Required for pinMode, digitalWrite, HIGH, LOW, delay
#include <FastLED.h>      // Required for FastLED, CRGB
#include "definitions.h"  // Required for leds, NUM_LEDS, BRIGHTNESS, LED_PIN, builting_led

// Forward declaration of your helper function
CRGB change_color(int i); 

void my_setup() {
  pinMode(builting_led, OUTPUT);     

  // Initialize FastLED for the WS2815 chipset
  FastLED.addLeds<WS2815, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  FastLED.clear();
  FastLED.show();
}

void my_loop() {
  int period = 1000;
  digitalWrite(builting_led, HIGH);  
  for(int i = 0; i < NUM_LEDS; i++) {
    // Call your new function here to pick Red or Blue based on the index!
    leds[i] = change_color(i);     
    FastLED.show();           
    delay(50);                
    leds[i] = CRGB::Black;    
  }
  delay(period);                
  digitalWrite(builting_led, LOW);   
}

// Your new color logic with corrected C++ syntax
CRGB change_color(int i) {
    if (i % 2 == 0) {
        return CRGB::Red;
    } else {
        return CRGB::Blue;
    }
} 
