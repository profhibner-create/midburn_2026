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

  // CRUCIAL STEP: Force the internal memory pointer to mount your SD Card partition
  Serial.println(F("Mounting active SD card filesystem..."));
  player.setPlayingDevice(DY::Device::Sd);
  delay(150);

  // Configure the background chip memory to repeat a single track forever
  Serial.println(F("Setting loop playback mode to RepeatOne..."));
  player.setCycleMode(DY::PlayMode::RepeatOne); 
  delay(150);              

  // Start background playback engine using standard play()
  // Because the device is mounted and RepeatOne is active, track 00001.mp3 loops infinitely!
  Serial.println(F("Starting background audio playback on a loop..."));
  player.play();     
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

  // Fill the long strip with Pure White
  for (int i = 0; i < NUM_LEDS_LONG; i++) {
    ledsLong[i] = CRGB::White;
  }

  // Fill the short strip with Pure White
  for (int i = 0; i < NUM_LEDS_SHORT; i++) {
    ledsShort[i] = CRGB::White;
  }

  if (digitalRead(PIN_BUTTON) == HIGH) { 
    Serial.println(F("\n[!] ARCADE BUTTON OVERRIDE DETECTED: INTERRUPTING SYSTEM..."));
  }
  
  FastLED.show();
}
