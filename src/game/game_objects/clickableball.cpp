#include "clickableball.h"

ClickableBall::ClickableBall(QGraphicsView* graphics_view, float width,
                             float height, float x, float y)
    : GameObject(graphics_view, width, height, x, y) {}

ClickableBall::ClickableBall(QGraphicsView* graphics_view, float width,
                             float height, QPointF pos)
    : GameObject(graphics_view, width, height, static_cast<float>(pos.x()),
                 static_cast<float>(pos.y())) {}

ClickableBall::~ClickableBall() {}

void ClickableBall::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                          QWidget*) {
  painter->setBrush(kBasicColor);
  painter->drawEllipse(boundingRect());
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
