#include "arrow.h"

const qreal Arrow::kZValue_ = 2;

Arrow::Arrow(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Arrow::SetUp() {
  this->setZValue(kZValue_);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/arrow.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}
