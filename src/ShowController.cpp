#include "ShowController.h"
#include "Config.h"
#include "Playlist.h"

void ShowController::begin() {
  startIdle();
}

void ShowController::startIdle() {
  state_ = State::Idle;
  track_ = &playlist::idle();
  motor_.stop();
  audio_.play(*track_);
  Serial.println(F("[show] idle"));
}

void ShowController::startShow(uint32_t now) {
  state_ = State::Playing;
  track_ = &playlist::pickRandomShow();
  trackStartMs_ = now;
  audio_.play(*track_);
  motor_.start();
  Serial.print(F("[show] button pressed, clock="));
  Serial.println(now);
  Serial.print(F("[show] playing track "));
  Serial.print(track_->number);
  Serial.print(F(", "));
  Serial.print(track_->durationMs / 1000);
  Serial.println(F(" s"));
}

Phase ShowController::phaseAt(uint32_t elapsedMs) const {
  if (elapsedMs < track_->dropStartMs) return Phase::Intro;
  if (elapsedMs < track_->dropEndMs)   return Phase::Drop;
  return Phase::Outro;
}

void ShowController::startSilence(uint32_t now) {
  state_ = State::Silence;
  silenceStartMs_ = now;
  audio_.stop();
  motor_.stop();
  Serial.println(F("[show] silence"));
}

void ShowController::update(uint32_t now) {
  button_.update(now);
  bool pressed = button_.wasPressed();  // always consume, so presses mid-show don't queue up

  switch (state_) {
    case State::Idle:
      if (pressed) startShow(now);
      break;
    case State::Playing:
      if (now - trackStartMs_ >= track_->durationMs) {
        Serial.print(F("[show] finished: clock counted "));
        Serial.print(now - trackStartMs_);
        Serial.println(F(" ms since the press"));
        startSilence(now);
      }
      break;
    case State::Silence:
      if (now - silenceStartMs_ >= config::SHOW_END_SILENCE_MS) startIdle();
      break;
  }

  ShowContext ctx = {Phase::Idle, 0, track_};
  Animation* animation = &breathing_;
  if (state_ == State::Playing) {
    ctx.elapsedMs = now - trackStartMs_;
    ctx.phase = phaseAt(ctx.elapsedMs);
    // The rise is the Drop phase; before and after it the triplet flicker runs.
    animation = (ctx.phase == Phase::Drop) ? static_cast<Animation*>(&rise_)
                                           : static_cast<Animation*>(&flicker_);
  }

  animation->render(display_, ctx);

  // The accent lights are only on during the rise and after it, never at idle or in the intro.
  bool accentOn = state_ == State::Playing &&
                  (ctx.phase == Phase::Drop || ctx.phase == Phase::Outro);
  if (!accentOn) display_.clearAccent();

  display_.show();
}
