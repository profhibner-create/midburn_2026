#pragma once

#include <Arduino.h>

// Turns the motor on and off by sending a PWM voltage to its controller board's speed
// input (see Config.h).
class MotorController {
 public:
  void begin();
  void start();  // send MOTOR_SPEED_MILLIVOLTS
  void stop();   // 0 V
};
