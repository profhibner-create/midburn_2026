#include "Animations.h"
#include "Config.h"

namespace {

// Deterministic "random" byte: the same inputs always give the same value, so a
// colour stays fixed for the whole flick without the animation storing any state.
uint8_t hashByte(uint32_t flick, uint16_t triplet, uint8_t salt) {
  uint32_t x = flick * 2654435761UL + triplet * 40503UL + salt * 2246822519UL;
  x ^= x >> 15;
  x *= 2246822519UL;
  x ^= x >> 13;
  return static_cast<uint8_t>(x >> 24);
}

void renderTriplets(LedDisplay& display, Strip strip, uint32_t flick, bool evenOn) {
  const uint16_t n = display.numLeds(strip);
  const uint8_t salt = static_cast<uint8_t>(strip);
  for (uint16_t t = 0; t * config::LEDS_PER_TRIPLET < n; t++) {
    bool on = ((t & 1) == 0) == evenOn;
    CRGB color = on ? CRGB(CHSV(hashByte(flick, t, salt), 255, 255)) : CRGB(CRGB::Black);
    for (uint8_t k = 0; k < config::LEDS_PER_TRIPLET; k++) {
      display.setLed(strip, t * config::LEDS_PER_TRIPLET + k, color);
    }
  }
}

}  // namespace

void BreathingWhite::render(LedDisplay& display, const ShowContext&) {
  display.setBrightness(beatsin8(config::IDLE_BREATH_BPM, config::IDLE_MIN_BRIGHTNESS,
                                 config::MAX_BRIGHTNESS));
  display.fill(CRGB::White);
}

void TripletFlicker::render(LedDisplay& display, const ShowContext& ctx) {
  // flicks/min = bpm * flashesPerBeat  ->  flick index = elapsedMs * bpm * perBeat / 60000
  uint32_t flick = ctx.elapsedMs * ctx.track->bpm * config::STROBE_FLASHES_PER_BEAT / 60000UL;
  bool evenOn = (flick & 1) == 0;

  display.setBrightness(config::MAX_BRIGHTNESS);
  renderTriplets(display, Strip::Long, flick, evenOn);
  renderTriplets(display, Strip::Short, flick, evenOn);
}

void RiseStrobe::render(LedDisplay& display, const ShowContext& ctx) {
  // One on/off cycle is two steps, so steps/min = bpm * RISE_FLASHES_PER_BEAT * 2.
  uint32_t step = ctx.elapsedMs * ctx.track->bpm * (config::RISE_FLASHES_PER_BEAT * 2UL) / 60000UL;

  display.setBrightness(config::MAX_BRIGHTNESS);
  display.fill((step & 1) == 0 ? CRGB(CRGB::White) : CRGB(CRGB::Black));
}
