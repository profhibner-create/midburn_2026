#pragma once

#include "ShowContext.h"

// Stepper motor, turning at bpm / MOTOR_BPM_DIVISOR RPM during a show.
// Hardware (driver, pins, library) is not decided yet, so this is a stub.
class MotorController {
 public:
  void begin() {}
  void startShow(const Track& track);
  void stop();
  void update(const ShowContext& ctx);
};
