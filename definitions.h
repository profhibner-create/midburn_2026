#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <FastLED.h> // Needed so this file understands what "CRGB" is

// Constants and Macros can live entirely in the header
#define LED_PIN     6         
#define NUM_LEDS    100        
#define BRIGHTNESS  150       

// "extern" tells other files: "This array exists, but its memory is allocated in the .cpp file"
extern CRGB leds[NUM_LEDS];          
extern const int builting_led;     
#endif
