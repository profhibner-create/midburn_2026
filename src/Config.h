#pragma once

#include <Arduino.h>

namespace config {

// LED strips
constexpr uint8_t  PIN_STRIP_LONG   = 5;
constexpr uint8_t  PIN_STRIP_SHORT  = 4;
constexpr uint16_t NUM_LEDS_LONG    = 194;
constexpr uint16_t NUM_LEDS_SHORT   = 26;
constexpr uint8_t  MAX_BRIGHTNESS   = 150;

// DY-HV20T audio module, driven in its I/O trigger mode (not UART).
// Pulling module IOn low plays 0000(n+1).mp3. Entry i is the Arduino pin wired
// to module IOi. Pins are only ever pulled low or released, never driven high.
constexpr uint8_t TRIGGER_PINS[] = {10, 9, 8, 7, 6};
constexpr uint8_t NUM_TRIGGER_PINS = sizeof(TRIGGER_PINS) / sizeof(TRIGGER_PINS[0]);
// Pause between releasing one track's pin and pulling the next, so two pins are never low together.
constexpr uint16_t TRIGGER_GAP_MS = 50;
// Time to wait for the module to finish starting up before the first trigger.
constexpr uint16_t MODULE_BOOT_MS = 1500;

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
