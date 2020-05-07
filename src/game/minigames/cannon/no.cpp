#include "no.h"

const qreal No::kZValue = 2;

No::No(GameView *graphics_view, qreal width, qreal height, qreal x, qreal y,
       qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

No::~No() {}

void No::SetUp() {
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "cannon/no.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}
