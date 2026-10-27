#pragma once

#include <FastLED.h>

#include "Config.h"

enum class Strip : uint8_t { Long, Short };

// Owns the two unequal strips and hides the split from animations.
class LedDisplay {
 public:
  void begin();

  void setBrightness(uint8_t brightness) { FastLED.setBrightness(brightness); }
  void fill(const CRGB& longColor, const CRGB& shortColor);
  void fill(const CRGB& color) { fill(color, color); }
  void show() { FastLED.show(); }

  // Turns the short strip's accent lights off (its first ACCENT_SHORT_LEDS LEDs).
  void clearAccent();

  uint16_t numLeds(Strip strip) const;
  void setLed(Strip strip, uint16_t index, const CRGB& color);

 private:
  CRGB longLeds_[config::NUM_LEDS_LONG];
  CRGB shortLeds_[config::NUM_LEDS_SHORT];
};
