#pragma once

#include <Arduino.h>

// Non-blocking debounced active-low button (INPUT_PULLUP).
class Button {
 public:
  Button(uint8_t pin, uint16_t debounceMs) : pin_(pin), debounceMs_(debounceMs) {}

  void begin();
  void update(uint32_t now);

  // True once per press; reading clears it.
  bool wasPressed();

 private:
  uint8_t  pin_;
  uint16_t debounceMs_;
  bool     lastRaw_ = HIGH;
  bool     stable_ = HIGH;
  uint32_t lastChangeMs_ = 0;
  bool     pressed_ = false;
};
