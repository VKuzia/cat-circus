#include "gameobject.h"

GameObject::GameObject(QGraphicsView* graphics_view, qreal width, qreal height,
                       qreal x, qreal y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(x, y);
}

GameObject::GameObject(QGraphicsView* graphics_view, qreal width, qreal height,
                       QPointF pos)
    : GameObject(graphics_view, width, height, pos.x(), pos.y()) {}

QRectF GameObject::boundingRect() const {
  return QRectF(-width_ / 2, -height_ / 2, width_, height_);
}
