#include "cannon.h"

const qreal Cannon::kZValue_ = 2;

Cannon::Cannon(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Cannon::SetUp() {
  this->setZValue(kZValue_);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/cannon.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}
