#include "speedometer.h"

const qreal Speedometer::kZValue_ = 2;

Speedometer::Speedometer(GameView *game_view, qreal width, qreal height,
                         qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Speedometer::SetUp() {
  this->setZValue(kZValue_);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/spedometer.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}
