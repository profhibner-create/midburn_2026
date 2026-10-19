#include "MotorController.h"
#include "Config.h"

void MotorController::begin() {
#if defined(__AVR_ATmega328P__)
  // Timer2 drives pin 3. Speed it up from 490 Hz to about 62 kHz (prescaler 1), so the
  // board's input sees a much smoother level.
  TCCR2B = (TCCR2B & 0xF8) | _BV(CS20);
#endif
  stop();
}

void MotorController::start() {
  analogWrite(config::PIN_MOTOR_SPEED, config::MOTOR_SPEED_DUTY);
  Serial.print(F("[motor] on, duty "));
  Serial.print(config::MOTOR_SPEED_DUTY);
  Serial.println(F("/255"));
}

void MotorController::stop() {
  analogWrite(config::PIN_MOTOR_SPEED, 0);
}
