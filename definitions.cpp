#include "definitions.h" 

// 1. Allocate the memory for the 5 independent LED strips
CRGB ledsTop[NUM_LEDS_TOP];
CRGB ledsA[NUM_LEDS_SHORT];
CRGB ledsB[NUM_LEDS_SHORT];
CRGB ledsC[NUM_LEDS_SHORT];
CRGB ledsD[NUM_LEDS_SHORT];

// 2. Define the built-in LED pin (must match 'const int' from header)
const int builtin_led = LED_BUILTIN;     

// 3. State tracking variable for your audio / playlist
bool play = false;
