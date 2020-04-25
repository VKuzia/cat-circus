#include "clickableball.h"

ClickableBall::ClickableBall(GameView* graphics_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(graphics_view, width, height, x, y) {}

ClickableBall::ClickableBall(GameView* graphics_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(graphics_view, width, height, pos) {}

void ClickableBall::SetUp() {
  qreal width = width_ * graphics_view_->GetPixelsInMeter();
  qreal height = height_ * graphics_view_->GetPixelsInMeter();
  QPixmap pixmap(qRound(width), qRound(height));
  QPainter painter(&pixmap);
  painter.setBrush(kBasicColor);
  painter.drawEllipse(1, 1, qFloor(width) - 2, qFloor(height) - 2);
  this->setOffset(-width / 2, -height / 2);
  this->setPixmap(pixmap);
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
