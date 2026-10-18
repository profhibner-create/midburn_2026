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
// Intro/outro flicker: steps per minute = bpm * STROBE_FLASHES_PER_BEAT
constexpr uint8_t STROBE_FLASHES_PER_BEAT = 2;
// LEDs per group that is switched on/off together (triplet 0 = LEDs 0-2, ...)
constexpr uint8_t LEDS_PER_TRIPLET = 3;
// White strobe during the rise: on/off cycles per minute = bpm * RISE_FLASHES_PER_BEAT
constexpr uint8_t RISE_FLASHES_PER_BEAT = 2;
// Motor RPM = bpm / MOTOR_BPM_DIVISOR (expected 2..4)
constexpr uint8_t MOTOR_BPM_DIVISOR  = 4;

// Silence between the end of a show and the idle music starting again
constexpr uint16_t SHOW_END_SILENCE_MS = 1000;

// Idle breathing
constexpr uint8_t  IDLE_BREATH_BPM = 30;
constexpr uint8_t  IDLE_MIN_BRIGHTNESS = 10;

}  // namespace config
