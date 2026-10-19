#pragma once

#include <Arduino.h>

namespace config {

// LED strips
constexpr uint8_t  PIN_STRIP_LONG   = 5;
constexpr uint8_t  PIN_STRIP_SHORT  = 4;
constexpr uint16_t NUM_LEDS_LONG    = 192;
constexpr uint16_t NUM_LEDS_SHORT   = 26;
constexpr uint8_t  MAX_BRIGHTNESS   = 150;
// Accent lights: the last this-many LEDs of the long strip and the first this-many LEDs of the
// short strip. They stay off except during the rise and the part after it.
constexpr uint16_t ACCENT_LEDS_PER_STRIP = 12;

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

// Motor: a PWM speed-controller board. Pin 3 replaces its speed potentiometer: it sends a
// PWM signal to the board's 0-5V input (pot removed, Arduino GND joined to the board's GND,
// the board's 5V pin left unconnected). The motor only runs during a show.
constexpr uint8_t PIN_MOTOR_SPEED = 3;   // Timer2 PWM output (OC2B)
// Voltage sent to the speed input, in millivolts (0 = stopped, 5000 = full speed).
// Tune it by counting shaft turns; about 70 RPM is the target.
constexpr uint16_t MOTOR_SPEED_MILLIVOLTS = 5000;   // full speed
constexpr uint8_t  MOTOR_SPEED_DUTY =
    static_cast<uint8_t>(static_cast<uint32_t>(MOTOR_SPEED_MILLIVOLTS) * 255 / 5000);
constexpr uint8_t  STEPPER_MOTOR_RPM = 70;   // target, for reference only

// Silence between the end of a show and the idle music starting again
constexpr uint16_t SHOW_END_SILENCE_MS = 1000;

// Idle breathing
constexpr uint8_t  IDLE_BREATH_BPM = 30;
constexpr uint8_t  IDLE_MIN_BRIGHTNESS = 10;

}  // namespace config
