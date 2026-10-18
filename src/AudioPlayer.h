#pragma once

#include <Arduino.h>

#include "Track.h"

// Plays tracks on the DY-HV20T by pulling its trigger pins low.
class AudioPlayer {
 public:
  void begin();
  void play(const Track& track);

 private:
  static const uint8_t NO_PIN = 0xFF;
  uint8_t activePin_ = NO_PIN;
};
