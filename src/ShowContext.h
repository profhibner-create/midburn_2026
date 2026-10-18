#pragma once

#include "Track.h"

enum class Phase { Idle, Intro, Drop, Outro };

// What animations and the motor need to know about "now".
struct ShowContext {
  Phase        phase;
  uint32_t     elapsedMs;  // time since the current track started
  const Track* track;
};
