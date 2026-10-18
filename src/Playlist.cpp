#include "Playlist.h"

namespace playlist {

namespace {

const Track IDLE = {1, 108, 31000UL, 0, 0};

// Files 00002..00005 on the card.
const Track SHOW[] = {
  {2, 125,  68000UL,  39000UL,  54000UL},
  {3, 121, 122000UL,  98000UL, 106000UL},
  {4, 125,  88000UL,  57000UL,  69000UL},
  {5, 124,  85000UL,  46000UL,  61000UL},
};
const uint8_t SHOW_COUNT = sizeof(SHOW) / sizeof(SHOW[0]);

}  // namespace

const Track& idle() { return IDLE; }

const Track& pickRandomShow() { return SHOW[random(SHOW_COUNT)]; }

}  // namespace playlist
