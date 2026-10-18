#pragma once

#include <Arduino.h>

// Time source that stays accurate while FastLED is drawing.
//
// FastLED.show() runs with interrupts off and distorts millis(): we measured it
// running about 6% fast, which cut shows short. On a 16 MHz AVR we count with
// Timer1 instead, which keeps counting in hardware. Elsewhere it falls back to millis().
//
// Note: begin() takes over Timer1, which turns off analogWrite() on pins 9 and 10.
namespace showclock {

void begin();

// Milliseconds since begin().
uint32_t nowMs();

}  // namespace showclock
