#pragma once

#include <FastLED.h>

// Owns the two unequal strips and hides the split from animations.
class LedDisplay {
 public:
  void begin();

  void setBrightness(uint8_t brightness) { FastLED.setBrightness(brightness); }
  void fill(const CRGB& longColor, const CRGB& shortColor);
  void fill(const CRGB& color) { fill(color, color); }
  void show() { FastLED.show(); }

 private:
  CRGB longLeds_[194];
  CRGB shortLeds_[26];
};
