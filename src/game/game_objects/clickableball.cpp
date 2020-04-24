#include "clickableball.h"

ClickableBall::ClickableBall(GameView* graphics_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(graphics_view, width, height, x, y) {}

ClickableBall::ClickableBall(GameView* graphics_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(graphics_view, width, height, pos) {}

void ClickableBall::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                          QWidget*) {
  painter->setBrush(kBasicColor);
  painter->drawEllipse(boundingRect());
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
