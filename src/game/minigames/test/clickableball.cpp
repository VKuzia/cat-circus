#include "clickableball.h"

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(game_view, width, height, pos) {}

void ClickableBall::SetUp() {
  qreal width = width_ * game_view_->GetPixelsInMeter();
  qreal height = height_ * game_view_->GetPixelsInMeter();
  QPixmap pixmap(qRound(width), qRound(height));
  QPainter painter(&pixmap);
  painter.setBrush(kBasicColor);
  // Some edge pixels left to render ball without edges cut
  painter.drawEllipse(1, 1, qFloor(width) - 2, qFloor(height) - 2);
  this->setOffset(-width / 2, -height / 2);
  this->setPixmap(pixmap);
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
