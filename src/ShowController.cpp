#include "ShowController.h"
#include "Playlist.h"

void ShowController::begin() {
  startIdle();
}

void ShowController::startIdle() {
  playing_ = false;
  track_ = &playlist::idle();
  motor_.stop();
  audio_.play(*track_);
  Serial.println(F("[show] idle"));
}

void ShowController::startShow(uint32_t now) {
  playing_ = true;
  track_ = &playlist::pickRandomShow();
  trackStartMs_ = now;
  audio_.play(*track_);
  motor_.startShow(*track_);
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

void ShowController::update(uint32_t now) {
  button_.update(now);
  bool pressed = button_.wasPressed();  // always consume, so presses mid-show don't queue up

  if (!playing_ && pressed) {
    startShow(now);
  } else if (playing_ && now - trackStartMs_ >= track_->durationMs) {
    startIdle();
  }

  ShowContext ctx = {Phase::Idle, 0, track_};
  Animation* animation = &breathing_;
  if (playing_) {
    ctx.elapsedMs = now - trackStartMs_;
    ctx.phase = phaseAt(ctx.elapsedMs);
    animation = (ctx.phase == Phase::Drop) ? static_cast<Animation*>(&dropEffect_)
                                           : static_cast<Animation*>(&strobe_);
  }

  motor_.update(ctx);
  animation->render(display_, ctx);
  display_.show();
}
