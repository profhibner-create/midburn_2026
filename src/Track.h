#pragma once

#include <Arduino.h>

// One audio file on the SD card, named 0000<number>.mp3.
struct Track {
  uint8_t  number;
  uint16_t bpm;
  uint32_t durationMs;    // full length of the track; the button is locked out this long
  uint32_t dropStartMs;   // position in the track where the drop begins (0 if none)
  uint32_t dropEndMs;     // position in the track where the drop ends (0 if none)
};
