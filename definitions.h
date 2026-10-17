#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <FastLED.h>

// Pins for LED strips
#define PIN_TOP       5
#define PIN_STRIP_A   6
#define PIN_STRIP_B   7
#define PIN_STRIP_C   8
#define PIN_STRIP_D   9

// Pins for DY-HV20T Audio Module
#define AUDIO_RX_PIN  10  
#define AUDIO_TX_PIN  11  

// PHYSICAL LED counts (Safe full sizes)
#define NUM_LEDS_TOP      168  
#define NUM_LEDS_SHORT    26   
#define BRIGHTNESS        150       

struct LoopProfile {
  uint16_t trackNumber; 
  uint16_t targetRpm;   
  uint32_t startMs;     
  uint32_t endMs;       
};

// Share safe array references across your project files
extern CRGB ledsTop[NUM_LEDS_TOP];          
extern CRGB ledsShort[NUM_LEDS_SHORT]; // Shared memory for strips A, B, C, D          

extern const int builtin_led;     
extern bool play;
extern const LoopProfile playlist[8]; 

#endif
