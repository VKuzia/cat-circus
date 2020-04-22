#include "gameobject.h"

GameObject::GameObject(QGraphicsView* graphics_view, float width, float height,
                       float x, float y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(static_cast<qreal>(x), static_cast<qreal>(y));
}

GameObject::GameObject(QGraphicsView* graphics_view, float width, float height,
                       QPointF pos)
    : GameObject(graphics_view, width, height, static_cast<float>(pos.x()),
                 static_cast<float>(pos.y())) {}

QRectF GameObject::boundingRect() const {
  return QRectF(static_cast<qreal>(-width_ / 2),
                static_cast<qreal>(-height_ / 2), static_cast<qreal>(width_),
                static_cast<qreal>(height_));
}

GameObject::~GameObject() {}
