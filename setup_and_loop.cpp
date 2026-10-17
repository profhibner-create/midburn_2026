#include <Arduino.h>      
#include <FastLED.h>      
#include <SoftwareSerial.h>
#include <DYPlayerArduino.h> 
#include "definitions.h"  

SoftwareSerial audioSerial(AUDIO_RX_PIN, AUDIO_TX_PIN);
DY::Player player(&audioSerial); 

void my_setup() {
  Serial.begin(115200);
  while (!Serial) { ; } 
  Serial.println(F("\n====== TWO STRIP SINEWAVE ENGINE ======"));

  // 1. Initialize Audio module
  audioSerial.begin(9600); 
  player.begin();
  delay(600); 

  player.setVolume(25);    
  delay(150);              

  // FIXED: Cleared namespaces to match SnijderC's official header exactly
  player.setCycleMode(DY::PlayMode::RepeatOne); 
  delay(150);              

  player.playSpecified(1);     
  delay(150);

  // 2. Initialize the two unequal physical strings
  FastLED.addLeds<WS2815, PIN_STRIP_LONG,  GRB>(ledsLong,  NUM_LEDS_LONG);
  FastLED.addLeds<WS2815, PIN_STRIP_SHORT, GRB>(ledsShort, NUM_LEDS_SHORT);
  
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void my_loop() {
  // Calculates a perfect smooth sinewave cycle breathing 30 times a minute
  uint8_t dynamicBrightness = beatsin8(30, 10, MAX_BRIGHTNESS);
  FastLED.setBrightness(dynamicBrightness);

  // Fill the long strip with Solid Red
  for (int i = 0; i < NUM_LEDS_LONG; i++) {
    ledsLong[i] = CRGB::Red;
  }

  // Fill the short strip with Solid Blue
  for (int i = 0; i < NUM_LEDS_SHORT; i++) {
    ledsShort[i] = CRGB::Blue;
  }

  FastLED.show();
}
