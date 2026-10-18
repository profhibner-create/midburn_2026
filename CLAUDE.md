# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Arduino sketch (`midburn_2026.ino`) for an interactive sound, light and (planned) stepper-motor installation.

- **Idle:** track `00001.mp3` loops and the LEDs breathe white.
- **Show:** a button press plays a random track from `00002`–`00008`. The LEDs flash blue/red in groups of three at bpm/4 flashes per second. The stepper (not yet built) turns at bpm/N RPM, with N≈2–4. The button is locked out until the track's full duration elapses, then it returns to idle.

There is no build system, test suite or linter in the repo, and `arduino-cli` isn't installed here, so nothing has been compile-checked. Compile and upload with the Arduino IDE or `arduino-cli` using the repo root as the sketch folder. The target board isn't recorded. Libraries needed: `FastLED`, `DYPlayerArduino`, `SoftwareSerial`. Serial monitor runs at 115200 baud.

## Architecture

`midburn_2026.ino` only builds the objects and calls `show.update(millis())`. Everything else is in `src/` (the Arduino build compiles it recursively):

- `ShowController` is the state machine (Idle ↔ Playing) and the only place that makes decisions. It owns the lockout. Presses are consumed and ignored while a show plays, and the show ends when `now - trackStartMs >= durationMs`.
- The phase (Intro / Drop / Outro) is derived from elapsed time in `phaseAt()`, not stored.
- `Animations` are stateless: they render purely from a `ShowContext` (phase, elapsedMs, track), so they can't drift from the music. `TripletStrobe` and `DropEffect` derive the flash index as `elapsedMs * bpm / (divisor * 1000)`. `DropEffect` is currently an empty subclass of `TripletStrobe`, a placeholder for the special drop effect.
- `MotorController` is a stub (no driver, pins or library chosen). It logs the target RPM only. Real stepper code goes in `startShow`, `stop` and `update`.
- `Playlist.cpp` holds the track table. `Track` has bpm, `durationMs` (full song), and `dropStartMs`/`dropEndMs` (positions within the track).
- `Button` is a non-blocking millis()-based debounce. `AudioPlayer` and `LedDisplay` wrap the DY-HV20T and the two WS2815 strips.
- Tunables (pins, divisors, brightness, strobe group size) live in `Config.h`.

## Gotchas

- Track numbers must match the SD card filenames (`0000N.mp3`). The `Track.number` field is passed straight to `playSpecified()`.
- The lockout uses `durationMs` (full song length), not the drop window. The audio start offset isn't compensated for: the module takes some tens to hundreds of ms to start playing after the command, so timing is only approximate.
- SD card prep (module may fail to recognise the card or play the wrong track):
  - Format as FAT32 with the **MBR** scheme (not GUID), on a card of 32 GB or less.
  - `playSpecified(n)` follows the order files were written to the card, not the filename. Copy `00001.mp3` to `00008.mp3` one at a time, in order, onto a freshly formatted card.
  - On macOS, remove hidden entries (`dot_clean`, `.Spotlight-V100`, `.fseventsd`, `.Trashes`, `._*` files) and run `mdutil -i off` on the volume.
- Power: the audio module's startup current can brown it out if it shares a weak 5 V rail with the LED strips. Use a common ground and a bulk capacitor, or a separate supply.
- `FastLED.show()` on ~220 WS2815 LEDs disables interrupts for several ms per frame. This will jitter stepper pulses and can drop `SoftwareSerial` bytes, so keep it in mind when choosing the stepper library.
- `LedDisplay.h` hardcodes the buffer sizes (194 and 26). A `static_assert` in `LedDisplay.cpp` fails the build if `Config.h` disagrees.
- LED type is `WS2815` with `GRB` ordering. Both strips share the global `FastLED.setBrightness()`.
