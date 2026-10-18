#pragma once

#include "LedDisplay.h"
#include "ShowContext.h"

// Animations are stateless: they render purely from the context, so they
// cannot drift out of sync with the music.
class Animation {
 public:
  virtual ~Animation() {}
  virtual void render(LedDisplay& display, const ShowContext& ctx) = 0;
};

// Idle: white sine-wave breathing.
class BreathingWhite : public Animation {
 public:
  void render(LedDisplay& display, const ShowContext& ctx) override;
};

// Before and after the rise: LEDs are grouped in triplets (0-2, 3-5, ...) per strip.
// On every flick the even triplets light up in random colours while the odd ones are
// off; on the next flick it is the other way round.
class TripletFlicker : public Animation {
 public:
  void render(LedDisplay& display, const ShowContext& ctx) override;
};

// During the rise: all LEDs flash white, on/off at bpm * RISE_FLASHES_PER_BEAT cycles per minute.
class RiseStrobe : public Animation {
 public:
  void render(LedDisplay& display, const ShowContext& ctx) override;
};
