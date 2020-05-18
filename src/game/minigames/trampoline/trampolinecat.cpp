#include "trampolinecat.h"

TrampolineCat::TrampolineCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      kPixmapNormal_(LoadPixmap("trampoline/cat_normal.png", true)),
      kPixmapHappy_(LoadPixmap("trampoline/cat_happy.png", true)),
      kPixmapSad_(LoadPixmap("trampoline/cat_sad.png", true)) {}

void TrampolineCat::SetUp() {
  setPixmap(kPixmapNormal_);

  rotation_animation_.setPropertyName("rotation");
  rotation_animation_.setTargetObject(this);
  rotation_animation_.setKeyValueAt(0, 0);
  rotation_animation_.setKeyValueAt(1, 360);
}

void TrampolineCat::Update() {
  if (!is_moving_) {
    return;
  }
  AddVelocity(physics::kGravity * kUpdateTime);
  MoveByMeters(velocity_ * kUpdateTime);
}

void TrampolineCat::RotateFor(int32_t millis) {
  rotation_animation_.stop();
  rotation_animation_.setDuration(millis);
  rotation_animation_.start();
}

void TrampolineCat::SetMood(TrampolineCat::Mood mood) {
  switch (mood) {
    case Mood::kNormal:
      setPixmap(kPixmapNormal_);
      break;
    case Mood::kHappy:
      setPixmap(kPixmapHappy_);
      break;
    case Mood::kSad:
      setPixmap(kPixmapSad_);
      break;
  }
}

void TrampolineCat::SetMoving(bool moving) { is_moving_ = moving; }

bool TrampolineCat::IsMoving() const { return is_moving_; }

void TrampolineCat::SetInAir(bool in_air) { is_in_air_ = in_air; }

bool TrampolineCat::IsInAir() const { return is_in_air_; }

void TrampolineCat::SetJustFlipped(bool flipped) { is_flip_started_ = flipped; }

bool TrampolineCat::IsJustFlipped() const { return is_flip_started_; }

void TrampolineCat::SetRotation(qreal rotation) {
  if (!is_moving_) {
    return;
  }
  setRotation(rotation);
}
