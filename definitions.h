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
#define AUDIO_RX_PIN  10  // Connects to DY-HV20T TX
#define AUDIO_TX_PIN  11  // Connects to DY-HV20T RX

// LED counts for each strip
#define NUM_LEDS_TOP      168  
#define NUM_LEDS_SHORT    26   
#define BRIGHTNESS        150       

extern CRGB ledsTop[NUM_LEDS_TOP];          
extern CRGB ledsA[NUM_LEDS_SHORT];          
extern CRGB ledsB[NUM_LEDS_SHORT];          
extern CRGB ledsC[NUM_LEDS_SHORT];          
extern CRGB ledsD[NUM_LEDS_SHORT];          

extern const int builtin_led;     
#endif
