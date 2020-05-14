#include "cannon.h"

Cannon::Cannon(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Cannon::SetUp() {
  this->setOffset(boundingRect().topLeft());
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/cannon.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}
