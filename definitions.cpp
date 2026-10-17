#include <Arduino.h>      
#include <FastLED.h>      
#include "definitions.h" 

// Allocate the optimized physical memory blocks
CRGB ledsTop[NUM_LEDS_TOP];
CRGB ledsShort[NUM_LEDS_SHORT]; // Shared memory footprint (Saves 234 bytes of RAM!)

const int builtin_led = LED_BUILTIN;     
bool play = false;

// Complete Playlist Data Matrix mapping Tracks, RPM targets, and Drop Windows
const LoopProfile playlist[8] = {
  {1, 108, 0, 0},             // 0001.mp3 -> Idle Profile
  {2, 125, 39000,  54000},    // 0002.mp3 -> Loop 1
  {3, 121, 98000,  106000},   // 0003.mp3 -> Loop 2
  {4, 117, 100000, 113000},   // 0004.mp3 -> Loop 3
  {5, 125, 57000,  69000},    // 0005.mp3 -> Loop 4
  {6, 130, 56000,  67000},    // 0006.mp3 -> Loop 5
  {7, 125, 49000,  62000},    // 0007.mp3 -> Loop 6
  {8, 124, 46000,  61000}     // 0008.mp3 -> Loop 7
};
