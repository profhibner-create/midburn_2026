#include "Animations.h"
#include "Config.h"

void BreathingWhite::render(LedDisplay& display, const ShowContext&) {
  display.setBrightness(beatsin8(config::IDLE_BREATH_BPM, config::IDLE_MIN_BRIGHTNESS,
                                 config::MAX_BRIGHTNESS));
  display.fill(CRGB::White);
}

void TripletStrobe::render(LedDisplay& display, const ShowContext& ctx) {
  // flashes/s = bpm / divisor  ->  flash index = elapsedMs * bpm / (divisor * 1000)
  uint32_t flash = ctx.elapsedMs * ctx.track->bpm / (config::STROBE_BPM_DIVISOR * 1000UL);

  bool oddFlash = flash & 1;
  bool flipped  = (flash / config::STROBE_GROUP_SIZE) & 1;
  bool longIsBlue = (oddFlash != flipped);

  display.setBrightness(config::MAX_BRIGHTNESS);
  // The short strip always shows the opposite colour of the long one.
  display.fill(longIsBlue ? CRGB::Blue : CRGB::Red, longIsBlue ? CRGB::Red : CRGB::Blue);
}
