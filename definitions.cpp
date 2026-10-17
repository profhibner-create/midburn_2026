#include <Arduino.h>      
#include <FastLED.h>      
#include "definitions.h" 

// Allocate the exact memory blocks for the two unequal strips
CRGB ledsLong[NUM_LEDS_LONG];
CRGB ledsShort[NUM_LEDS_SHORT];

const int builtin_led = LED_BUILTIN;     
bool play = false;

// FIXED: Added array identifier sizing to perfectly lock down alignment matrix compilation
const LoopProfile playlist[8] = {
  {1, 108, 0, 0},             // 00001.mp3 -> Idle Profile
  {2, 125, 39000,  54000},    // 00002.mp3 -> Loop 1
  {3, 121, 98000,  106000},   // 00003.mp3 -> Loop 2
  {4, 117, 100000, 113000},   // 00004.mp3 -> Loop 3
  {5, 125, 57000,  69000},    // 00005.mp3 -> Loop 4
  {6, 130, 56000,  67000},    // 00006.mp3 -> Loop 5
  {7, 125, 49000,  62000},    // 00007.mp3 -> Loop 6
  {8, 124, 46000,  61000}     // 00008.mp3 -> Loop 7
};
