#include "gameobject.h"

GameObject::GameObject(QGraphicsView* graphics_view, float width, float height,
                       float x, float y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(static_cast<double>(x), static_cast<double>(y));
}

QRectF GameObject::boundingRect() const {
  return QRectF(static_cast<double>(-width_ / 2),
                static_cast<double>(-height_ / 2), static_cast<double>(width_),
                static_cast<double>(height_));
}

GameObject::~GameObject() {}
