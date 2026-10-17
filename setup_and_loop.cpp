#include <Arduino.h>      
#include <FastLED.h>      
#include <SoftwareSerial.h>
#include <DYPlayerArduino.h> 
#include "definitions.h"  

SoftwareSerial audioSerial(AUDIO_RX_PIN, AUDIO_TX_PIN);
DY::Player player(&audioSerial); 

// State Tracking Variables for your interactive events
bool isSpecialEventRunning = false;
unsigned long eventEndTime = 0;
static bool lastButtonState = HIGH; // Regular tactile button sits HIGH when open

void my_setup() {
  Serial.begin(115200);
  while (!Serial) { ; } 
  Serial.println(F("\n====== FINAL UNIFIED SOUND & LIGHT ENGINE ======"));

  // Initialize your button pin as a safe pullup tracking line
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Initialize randomizer seed using electrical noise from an open analog pin
  randomSeed(analogRead(A0));

  // 1. Initialize Audio module over working Pins 2 and 3
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

  // 2. Initialize the two unequal physical strings
  FastLED.addLeds<WS2815, PIN_STRIP_LONG,  GRB>(ledsLong,  NUM_LEDS_LONG);
  FastLED.addLeds<WS2815, PIN_STRIP_SHORT, GRB>(ledsShort, NUM_LEDS_SHORT);
  
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void my_loop() {
  unsigned long currentMillis = millis();

  // --- PHASE A: MONITOR THE BUTTON VIA YOUR WORKING TACTILE LATCH ---
  bool currentButtonState = digitalRead(PIN_BUTTON);

  // Trigger instantly on the exact frame the tactile button bridges to GND (LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(25); // Clean mechanical switch contact bounce noise
    if (digitalRead(PIN_BUTTON) == LOW) { 
      
      Serial.println(F("\n[!] BUTTON PRESSED: INTERRUPTING Baseline TO SELECTION..."));
      
      // 1. Pick a truly random track index from 1 to 7 (mapping to loops 1 through 7 in matrix array)
      int randomTrackIndex = random(1, 8); 
      
      // 2. Fetch the assigned track structure data to calculate run duration
      LoopProfile trackSelected = playlist[randomTrackIndex];
      uint32_t trackDurationMs = trackSelected.endMs - trackSelected.startMs;
      
      Serial.println(F("=================================================="));
      Serial.print(F(" -> RANDOMIZER ASSIGNED TRACK : 0000")); 
      Serial.println(trackSelected.trackNumber);
      Serial.print(F(" -> TRACK DURATION CALCULATED : ")); 
      Serial.print(trackDurationMs / 1000); 
      Serial.println(F(" seconds"));
      Serial.println(F("=================================================="));

      // 3. Command the audio module to instantly cut off track 1 and play the random selection
      player.playSpecified(trackSelected.trackNumber);
      
      // 4. Force active flags to true and mark target event timeout boundaries
      isSpecialEventRunning = true;
      eventEndTime = currentMillis + trackDurationMs;

      // Hold execution here until you lift your finger so it doesn't double-trigger
      while(digitalRead(PIN_BUTTON) == LOW) { 
        delay(1); 
      }
    }
  }

  // Lock the current state parameter into cache for the next iteration loop pass
  lastButtonState = currentButtonState;


  // --- PHASE B: MONITOR ACTIVE SPECIAL EVENTS RUNTIME ---
  if (isSpecialEventRunning) {
    // Reverts back to baseline loops naturally when the countdown expires
    if (currentMillis >= eventEndTime) {
      Serial.println(F("Special track ended. Reverting back to baseline track 00001.mp3..."));
      isSpecialEventRunning = false;
      
      // Force return back to baseline tracking audio loop profile
      player.playSpecified(1);
    }
  } 


  // --- PHASE C: LED ANIMATION ROUTER ---
  if (isSpecialEventRunning) {
    // SPECIAL ANIMATION: Fast Red/Blue flashing strobe (police flicker style)
    // beatsin8(frequency) toggles rapidly every 140 beats per minute
    uint8_t togglePattern = beatsin8(140, 0, 255);
    
    for (int i = 0; i < NUM_LEDS_LONG; i++) {
      ledsLong[i] = (togglePattern > 127) ? CRGB::Red : CRGB::Blue;
    }
    for (int i = 0; i < NUM_LEDS_SHORT; i++) {
      ledsShort[i] = (togglePattern > 127) ? CRGB::Blue : CRGB::Red; // Inverted alignment layout
    }
    FastLED.setBrightness(MAX_BRIGHTNESS); 
  } 
  else {
    // DEFAULT ANIMATION: Smooth Sine-Wave Breathing Pure White
    uint8_t dynamicBrightness = beatsin8(30, 10, MAX_BRIGHTNESS);
    FastLED.setBrightness(dynamicBrightness);

    for (int i = 0; i < NUM_LEDS_LONG; i++) {
      ledsLong[i] = CRGB::White;
    }
    for (int i = 0; i < NUM_LEDS_SHORT; i++) {
      ledsShort[i] = CRGB::White;
    }
  }

  // Render everything out to the data lines smoothly
  FastLED.show();
}
