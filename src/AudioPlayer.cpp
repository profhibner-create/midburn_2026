#include "AudioPlayer.h"
#include "Config.h"

void AudioPlayer::begin() {
  // Released = input (high impedance), so the module's own pull-ups hold the lines high.
  for (uint8_t i = 0; i < config::NUM_TRIGGER_PINS; i++) {
    pinMode(config::TRIGGER_PINS[i], INPUT);
  }
  // Give the module time to mount the SD card; triggers during start-up may be ignored.
  delay(config::MODULE_BOOT_MS);
}

void AudioPlayer::play(const Track& track) {
  if (track.number < 1 || track.number > config::NUM_TRIGGER_PINS) return;

  // Release the previous track first so two pins are never low at once.
  if (activePin_ != NO_PIN) {
    pinMode(activePin_, INPUT);
    delay(config::TRIGGER_GAP_MS);
  }

  uint8_t pin = config::TRIGGER_PINS[track.number - 1];
  digitalWrite(pin, LOW);  // set the level before enabling the output: never drive high
  pinMode(pin, OUTPUT);
  activePin_ = pin;
}

void AudioPlayer::stop() {
  if (activePin_ == NO_PIN) return;
  pinMode(activePin_, INPUT);
  activePin_ = NO_PIN;
}
