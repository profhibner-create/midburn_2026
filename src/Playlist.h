#pragma once

#include "Track.h"

namespace playlist {

// Track 1: looping idle music.
const Track& idle();

// A random show track (00002..00005).
const Track& pickRandomShow();

}  // namespace playlist
