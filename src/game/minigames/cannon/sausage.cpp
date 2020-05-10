#include "sausage.h"

const qreal Sausage::kZValue = 2;

Sausage::Sausage(GameView* graphics_view, qreal width, qreal height, qreal x,
                 qreal y, qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

Sausage::~Sausage() {}

void Sausage::SetUp() {
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/sausage.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void Sausage::Update() {
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

void Sausage::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal Sausage::GetRadius() const { return radius_; }
