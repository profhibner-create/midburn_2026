#pragma once

#include <FastLED.h>

enum class Strip : uint8_t { Long, Short };

// Owns the two unequal strips and hides the split from animations.
class LedDisplay {
 public:
  void begin();

  void setBrightness(uint8_t brightness) { FastLED.setBrightness(brightness); }
  void fill(const CRGB& longColor, const CRGB& shortColor);
  void fill(const CRGB& color) { fill(color, color); }
  void show() { FastLED.show(); }

  uint16_t numLeds(Strip strip) const;
  void setLed(Strip strip, uint16_t index, const CRGB& color);

 private:
  CRGB longLeds_[194];
  CRGB shortLeds_[26];
};
