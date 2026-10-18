#pragma once

#include "Animations.h"
#include "AudioPlayer.h"
#include "Button.h"
#include "LedDisplay.h"
#include "MotorController.h"
#include "ShowContext.h"

// Three states:
//   Idle    - looping track 1, white breathing. A button press starts a show.
//   Playing - random show track until its duration has elapsed.
//   Silence - music off for SHOW_END_SILENCE_MS, then back to Idle.
// Button presses are ignored outside Idle.
class ShowController {
 public:
  ShowController(Button& button, AudioPlayer& audio, LedDisplay& display, MotorController& motor)
      : button_(button), audio_(audio), display_(display), motor_(motor) {}

  void begin();
  void update(uint32_t now);

 private:
  void startIdle();
  void startSilence(uint32_t now);
  void startShow(uint32_t now);
  Phase phaseAt(uint32_t elapsedMs) const;

  Button&          button_;
  AudioPlayer&     audio_;
  LedDisplay&      display_;
  MotorController& motor_;

  BreathingWhite breathing_;
  TripletFlicker flicker_;
  RiseStrobe     rise_;

  enum class State { Idle, Playing, Silence };
  State        state_ = State::Idle;
  const Track* track_ = nullptr;
  uint32_t     trackStartMs_ = 0;
  uint32_t     silenceStartMs_ = 0;
};
