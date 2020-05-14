#include "cannonsausage.h"

CannonSausage::CannonSausage(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonSausage::SetUp() {
  this->setOffset(boundingRect().topLeft());
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/sausage.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}

void CannonSausage::Update() {
  if (is_caught_) {
    return;
  }
  if (delta_pos >= 1) {
    move_down = false;
  } else if (delta_pos <= -1) {
    move_down = true;
  }
  if (move_down) {
    delta_pos += 0.01;
    MoveByMeters(0, 0.01);
  } else {
    delta_pos -= 0.01;
    MoveByMeters(0, -0.01);
  }
}

void CannonSausage::SetCaught(bool is_caught) { is_caught_ = is_caught; }
