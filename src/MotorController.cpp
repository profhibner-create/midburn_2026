#include "MotorController.h"
#include "Config.h"

void MotorController::startShow(const Track& track) {
  // TODO: configure the stepper for this speed.
  Serial.print(F("[motor] target RPM: "));
  Serial.println(track.bpm / config::MOTOR_BPM_DIVISOR);
}

void MotorController::stop() {
  // TODO: stop the stepper.
}

void MotorController::update(const ShowContext&) {
  // TODO: run the stepper (e.g. AccelStepper::run()) and react to Phase::Drop.
}
