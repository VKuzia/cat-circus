#include "trampolinecat.h"

TrampolineCat::TrampolineCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

TrampolineCat::~TrampolineCat() {}

void TrampolineCat::SetUp() {
  setPixmap(GetPixmapFrom("trampoline/cat.png"));

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

void TrampolineCat::SetMoving(bool moving) { is_moving_ = moving; }

bool TrampolineCat::IsMoving() const { return is_moving_; }

void TrampolineCat::SetFlying(bool flying) { is_flying_ = flying; }

bool TrampolineCat::IsFlying() const { return is_flying_; }

void TrampolineCat::SetJustFlipped(bool flipped) { is_just_flipped_ = flipped; }

bool TrampolineCat::IsJustFlipped() const { return is_just_flipped_; }

void TrampolineCat::SetRotation(qreal rotation) {
  if (!is_moving_) {
    return;
  }
  setRotation(rotation);
}
