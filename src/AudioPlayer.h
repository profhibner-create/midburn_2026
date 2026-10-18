#pragma once

#include <SoftwareSerial.h>
#include <DYPlayerArduino.h>

#include "Track.h"

// Thin wrapper around the DY-HV20T module.
class AudioPlayer {
 public:
  AudioPlayer(uint8_t rxPin, uint8_t txPin) : serial_(rxPin, txPin), player_(&serial_) {}

  void begin(uint8_t volume);
  void play(const Track& track);

 private:
  SoftwareSerial serial_;
  DY::Player     player_;
};
