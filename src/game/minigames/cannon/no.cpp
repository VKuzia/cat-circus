#include "no.h"

const qreal No::kZValue_ = 2;

No::No(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void No::SetUp() {
  this->setZValue(kZValue_);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/no.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}
