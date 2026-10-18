#include "src/Config.h"
#include "src/AudioPlayer.h"
#include "src/Button.h"
#include "src/LedDisplay.h"
#include "src/MotorController.h"
#include "src/ShowController.h"

Button          button(config::PIN_BUTTON, config::DEBOUNCE_MS);
AudioPlayer     audio(config::PIN_AUDIO_RX, config::PIN_AUDIO_TX);
LedDisplay      display;
MotorController motor;
ShowController  show(button, audio, display, motor);

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));

  button.begin();
  display.begin();
  motor.begin();
  audio.begin(config::AUDIO_VOLUME);
  show.begin();
}

void loop() {
  show.update(millis());
}
