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

// Show: blue/red flashes at bpm/STROBE_BPM_DIVISOR per second, in groups of three.
class TripletStrobe : public Animation {
 public:
  void render(LedDisplay& display, const ShowContext& ctx) override;
};

// Placeholder for the special effect between drop start and drop end.
class DropEffect : public TripletStrobe {
  // TODO: design the drop effect; override render().
};
