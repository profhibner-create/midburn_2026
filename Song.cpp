#include "Song.h"

// 🔴 Added the star to LightStyle* style
Song::Song(int trackId, LightStyle* style) {
  _trackId = trackId;
  _style = style; 
  _isPlaying = false;
}

void Song::play() {
  _isPlaying = true;
  if (_style != nullptr) {
    _style->reset(); 
  }
}

void Song::stop() {
  _isPlaying = false;
  FastLED.clear();
  FastLED.show();
}

void Song::update() {
  if (!_isPlaying) return;

  if (_style != nullptr) {
    _style->updateFrame(); 
  }
}
