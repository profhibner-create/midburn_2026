#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <FastLED.h>

// Pins for LED strips
#define PIN_STRIP_LONG    5  
#define PIN_STRIP_SHORT   6  

// Pins for DY-HV20T Audio Module (Optimal pins 2 and 3)
#define AUDIO_RX_PIN  2  
#define AUDIO_TX_PIN  3  

#define NUM_LEDS_LONG     194  
#define NUM_LEDS_SHORT    26   
#define MAX_BRIGHTNESS    150       

struct LoopProfile {
  uint16_t trackNumber; 
  uint16_t targetRpm;   
  uint32_t startMs;     
  uint32_t endMs;       
};

extern CRGB ledsLong[NUM_LEDS_LONG];          
extern CRGB ledsShort[NUM_LEDS_SHORT];          

extern const int builtin_led;     
extern bool play;

// FIXED: Defined clearly as an explicit 8-profile matrix structure
extern const LoopProfile playlist[8]; 

#endif
