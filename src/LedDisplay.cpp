#include "LedDisplay.h"
#include "Config.h"

static_assert(config::NUM_LEDS_LONG == 194 && config::NUM_LEDS_SHORT == 26,
              "Update the buffer sizes in LedDisplay.h");

void LedDisplay::begin() {
  FastLED.addLeds<WS2815, config::PIN_STRIP_LONG,  GRB>(longLeds_,  config::NUM_LEDS_LONG);
  FastLED.addLeds<WS2815, config::PIN_STRIP_SHORT, GRB>(shortLeds_, config::NUM_LEDS_SHORT);
  FastLED.setBrightness(config::MAX_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void LedDisplay::fill(const CRGB& longColor, const CRGB& shortColor) {
  fill_solid(longLeds_,  config::NUM_LEDS_LONG,  longColor);
  fill_solid(shortLeds_, config::NUM_LEDS_SHORT, shortColor);
}

uint16_t LedDisplay::numLeds(Strip strip) const {
  return strip == Strip::Long ? config::NUM_LEDS_LONG : config::NUM_LEDS_SHORT;
}

void LedDisplay::setLed(Strip strip, uint16_t index, const CRGB& color) {
  if (index >= numLeds(strip)) return;
  (strip == Strip::Long ? longLeds_ : shortLeds_)[index] = color;
}
