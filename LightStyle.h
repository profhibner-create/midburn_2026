#ifndef LIGHT_STYLE_H
#define LIGHT_STYLE_H

#include <Arduino.h>
#include <FastLED.h>
#include "definitions.h" // Gives all styles access to the global 'leds' array

class LightStyle {
  public:
    virtual ~LightStyle() {} // Virtual destructor for memory safety
    
    // Virtual reset method called when a song first starts up
    virtual void reset() = 0; 
    
    // Virtual frame method called continuously in loop()
    virtual void updateFrame() = 0; 
};

#endif
