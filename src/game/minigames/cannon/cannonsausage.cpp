#include "cannonsausage.h"

CannonSausage::CannonSausage(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonSausage::SetUp() { setPixmap(LoadPixmap("cannon/sausage.png")); }

void CannonSausage::Update() {
  if (is_caught_) {
    return;
  }
  if (delta_pos >= 1) {
    move_down_ = false;
  } else if (delta_pos <= -1) {
    move_down_ = true;
  }
  if (move_down_) {
    delta_pos += 0.01;
    MoveByMeters(0, 0.01);
  } else {
    delta_pos -= 0.01;
    MoveByMeters(0, -0.01);
  }
}

void CannonSausage::WasCaught() {
  setVisible(false);
  emit CaughtSausage();
}

bool CannonSausage::GetMoveDown() const { return move_down_; }

void CannonSausage::SetMoveDown(bool move_down) { move_down_ = move_down; }
