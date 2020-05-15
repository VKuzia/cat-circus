#include "trampolinecat.h"

TrampolineCat::TrampolineCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      kPixmapNormal_(LoadPixmap("trampoline/cat_normal.png")),
      kPixmapHappy_(LoadPixmap("trampoline/cat_happy.png")),
      kPixmapSad_(LoadPixmap("trampoline/cat_sad.png")) {}

void TrampolineCat::SetUp() {
  setPixmap(kPixmapNormal_);

  rotation_animation_.setPropertyName("rotation");
  rotation_animation_.setTargetObject(this);
  rotation_animation_.setKeyValueAt(0, 0);
  rotation_animation_.setKeyValueAt(1, 360);
}

void TrampolineCat::Update() {
  if (!is_rotating_) {
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

void TrampolineCat::SetRotating(bool rotating) { is_rotating_ = rotating; }

bool TrampolineCat::IsRotating() const { return is_rotating_; }

void TrampolineCat::SetFlying(bool flying) { is_flying_ = flying; }

bool TrampolineCat::IsFlying() const { return is_flying_; }

void TrampolineCat::SetJustFlipped(bool flipped) { is_just_flipped_ = flipped; }

bool TrampolineCat::IsJustFlipped() const { return is_just_flipped_; }

void TrampolineCat::SetRotation(qreal rotation) {
  if (!is_rotating_) {
    return;
  }
  setRotation(rotation);
}