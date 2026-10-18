#pragma once

#include "Animations.h"
#include "AudioPlayer.h"
#include "Button.h"
#include "LedDisplay.h"
#include "MotorController.h"
#include "ShowContext.h"

// Two states: Idle (looping track 1, white breathing) and Playing (random
// show track). A button press in Idle starts a show; presses are ignored
// until the track's duration has elapsed, then we return to Idle.
class ShowController {
 public:
  ShowController(Button& button, AudioPlayer& audio, LedDisplay& display, MotorController& motor)
      : button_(button), audio_(audio), display_(display), motor_(motor) {}

  void begin();
  void update(uint32_t now);

 private:
  void startIdle();
  void startShow(uint32_t now);
  Phase phaseAt(uint32_t elapsedMs) const;

  Button&          button_;
  AudioPlayer&     audio_;
  LedDisplay&      display_;
  MotorController& motor_;

  BreathingWhite breathing_;
  TripletStrobe  strobe_;
  DropEffect     dropEffect_;

  bool         playing_ = false;
  const Track* track_ = nullptr;
  uint32_t     trackStartMs_ = 0;
};
