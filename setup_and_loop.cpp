#include <Arduino.h>      
#include <FastLED.h>      
#include <SoftwareSerial.h>
#include <DYPlayerArduino.h> 
#include "definitions.h"  

CRGB change_color(int i); 

SoftwareSerial audioSerial(AUDIO_RX_PIN, AUDIO_TX_PIN);
DY::Player player(&audioSerial); // Correct library initialization pattern

void my_setup() {
  Serial.begin(115200);
  while (!Serial) { ; } 
  Serial.println(F("\n====== FORCED AUDIO DIAGNOSTIC ENGINE ======"));

  // Initialize Software Serial bus for the audio module
  audioSerial.begin(9600); 
  player.begin();
  delay(600); // Give the module plenty of time to wake up safely

  Serial.println(F("Setting master playback volume to 10..."));
  player.setVolume(10);    
  delay(150);              

  // Force play command for 0001.mp3 (Track Index 1)
  Serial.println(F("CRITICAL: Sending command to play '00001.mp3'..."));
  player.playSpecified(1);     
  delay(150);

  Serial.println(F("Diagnostic phase finished. Initializing FastLED strips..."));

  // Initialize your FastLED hardware strings using full dimensions
  FastLED.addLeds<WS2815, PIN_TOP,       GRB>(ledsTop, NUM_LEDS_TOP);
  
  // All 4 hardware data pins share the single ledsShort memory profile simultaneously
  FastLED.addLeds<WS2815, PIN_STRIP_A,   GRB>(ledsShort, NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_B,   GRB>(ledsShort, NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_C,   GRB>(ledsShort, NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_D,   GRB>(ledsShort, NUM_LEDS_SHORT);
  
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void my_loop() {
  static unsigned long lastLedFrame = 0;
  static int currentPixel = 0;

  if (millis() - lastLedFrame >= 30) {
    lastLedFrame = millis();
    
    // Clear display slate safely
    FastLED.clear();
    
    // Animate the Top strip
    ledsTop[currentPixel] = change_color(currentPixel);
    
    // Optional: Animate all short strips identically in sync
    ledsShort[currentPixel % NUM_LEDS_SHORT] = change_color(currentPixel);
    
    FastLED.show();
    
    currentPixel++;
    if (currentPixel >= NUM_LEDS_TOP) {
      currentPixel = 0;
    }
  }
}

CRGB change_color(int i) {
    return (i % 2 == 0) ? CRGB::Red : CRGB::Blue;
}
