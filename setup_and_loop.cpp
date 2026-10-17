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
  Serial.println(F("\n====== 4-LEG TACTILE BUTTON ENGINE ======"));

  // Enable the internal pullup to hold Pin 12 steadily at HIGH (1) until pressed
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Initialize Audio module over working Pins 2 and 3
  audioSerial.begin(9600); 
  player.begin();
  delay(600); 

  player.setVolume(25);    
  delay(150);              

  Serial.println(F("Mounting active SD card filesystem..."));
  player.setPlayingDevice(DY::Device::Sd);
  delay(150);

  Serial.println(F("Setting loop playback mode to RepeatOne..."));
  player.setCycleMode(DY::PlayMode::RepeatOne); 
  delay(150);              

  Serial.println(F("Starting background audio playback on a loop..."));
  player.play();     
  delay(150);

  // Initialize the two unequal physical strings
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

  // Fill both strips with Pure White
  for (int i = 0; i < NUM_LEDS_LONG; i++) {
    ledsLong[i] = CRGB::White;
  }
  for (int i = 0; i < NUM_LEDS_SHORT; i++) {
    ledsShort[i] = CRGB::White;
  }

  // --- STABLE TACTILE EDGE LATCH ENGINE ---
  static bool lastButtonState = HIGH; 
  bool currentButtonState = digitalRead(PIN_BUTTON);

  // Trigger ONLY on the exact frame the button connects to GND (LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(25); // Debounce filter to ignore mechanical button vibration noise
    if (digitalRead(PIN_BUTTON) == LOW) { 
      Serial.println(F("\n[!] BUTTON PRESSED: INTERRUPTING SYSTEM..."));
      
      // Hold execution here until you release the button (returns back to HIGH)
      while(digitalRead(PIN_BUTTON) == LOW) { 
        delay(1); 
      }
    }
  }
  
  // Track state changes safely across execution passes
  lastButtonState = currentButtonState;

  FastLED.show();
}
