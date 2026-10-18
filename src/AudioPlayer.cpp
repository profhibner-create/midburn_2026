#include "AudioPlayer.h"

void AudioPlayer::begin(uint8_t volume) {
  serial_.begin(9600);
  player_.begin();
  delay(600);

  player_.setVolume(volume);
  delay(150);

  player_.setPlayingDevice(DY::Device::Sd);
  delay(150);

  // Idle music loops by itself; show tracks are cut off by the controller.
  player_.setCycleMode(DY::PlayMode::RepeatOne);
  delay(150);
}

void AudioPlayer::play(const Track& track) {
  player_.playSpecified(track.number);
}
