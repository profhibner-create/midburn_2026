#pragma once

#include <Arduino.h>

namespace config {

// LED strips
constexpr uint8_t  PIN_STRIP_LONG   = 5;
constexpr uint8_t  PIN_STRIP_SHORT  = 6;
constexpr uint16_t NUM_LEDS_LONG    = 194;
constexpr uint16_t NUM_LEDS_SHORT   = 26;
constexpr uint8_t  MAX_BRIGHTNESS   = 150;

// DY-HV20T audio module (SoftwareSerial)
constexpr uint8_t PIN_AUDIO_RX = 2;
constexpr uint8_t PIN_AUDIO_TX = 3;
constexpr uint8_t AUDIO_VOLUME = 25;

// Trigger button (normally open, to GND)
constexpr uint8_t  PIN_BUTTON      = 12;
constexpr uint16_t DEBOUNCE_MS     = 25;

// Show timing
// Strobe flashes per second = bpm / STROBE_BPM_DIVISOR
constexpr uint8_t STROBE_BPM_DIVISOR = 4;
// Consecutive flashes before the colour pair flips (blue,red,blue -> red,blue,red)
constexpr uint8_t STROBE_GROUP_SIZE  = 3;
// Motor RPM = bpm / MOTOR_BPM_DIVISOR (expected 2..4)
constexpr uint8_t MOTOR_BPM_DIVISOR  = 4;

// Idle breathing
constexpr uint8_t  IDLE_BREATH_BPM = 30;
constexpr uint8_t  IDLE_MIN_BRIGHTNESS = 10;

}  // namespace config
