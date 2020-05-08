#include "trampolinecat.h"

TrampolineCat::TrampolineCat(GameView* game_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(game_view, width, height, pos) {}

TrampolineCat::~TrampolineCat() {}

TrampolineCat::TrampolineCat(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)

    : TrampolineCat(game_view, width, height, QPointF(x, y)) {}

void TrampolineCat::SetUp() {
  int32_t width = boundingRect().size().toSize().width();
  int32_t height = boundingRect().size().toSize().height();
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "trampoline/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  setOffset(-width / 2, -height / 2);
  setPixmap(pixmap.scaled(width, height));

  rotation_animation_.setPropertyName("rotation");
  rotation_animation_.setTargetObject(this);
  rotation_animation_.setKeyValueAt(0, 0);
  rotation_animation_.setKeyValueAt(1, 360);
}

void TrampolineCat::Update() {
  if (!is_moving_) {
    return;
  }
  AddVelocity(0, physics::kGravity.y() * kUpdateTime);
  MoveByMeters(velocity_.x() * kUpdateTime, velocity_.y() * kUpdateTime);
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
