#include "cannonsausage.h"

CannonSausage::CannonSausage(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonSausage::SetUp() { setPixmap(LoadPixmap("cannon/sausage.png")); }

void CannonSausage::Update() {
  if (is_caught_) {
    return;
  }
  if (delta_pos_ >= 1) {
    is_moving_down_ = false;
  } else if (delta_pos_ <= -1) {
    is_moving_down_ = true;
  }
  if (is_moving_down_) {
    delta_pos_ += one_step_;
    MoveByMeters(0, one_step_);
  } else {
    delta_pos_ -= one_step_;
    MoveByMeters(0, -one_step_);
  }
}

void CannonSausage::WasCaught() {
  setVisible(false);
  emit CaughtSausage();
}

bool CannonSausage::IsMovingDown() const { return is_moving_down_; }

void CannonSausage::SetMovingDown(bool is_moving_down) {
  is_moving_down_ = is_moving_down;
}
