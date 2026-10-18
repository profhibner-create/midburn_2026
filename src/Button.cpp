#include "Button.h"

void Button::begin() {
  pinMode(pin_, INPUT_PULLUP);
  lastRaw_ = stable_ = digitalRead(pin_);
}

void Button::update(uint32_t now) {
  bool raw = digitalRead(pin_);
  if (raw != lastRaw_) {
    lastRaw_ = raw;
    lastChangeMs_ = now;
  }
  if (raw != stable_ && now - lastChangeMs_ >= debounceMs_) {
    stable_ = raw;
    if (stable_ == LOW) pressed_ = true;
  }
}

bool Button::wasPressed() {
  bool p = pressed_;
  pressed_ = false;
  return p;
}
