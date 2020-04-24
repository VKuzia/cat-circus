#include "gameobject.h"

GameObject::GameObject(GameView* graphics_view, qreal width, qreal height,
                       qreal x, qreal y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(x, y);
}

GameObject::GameObject(GameView* graphics_view, qreal width, qreal height,
                       QPointF pos)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(pos);
}

void GameObject::SetUp() {}
void GameObject::Update() {}

QRectF GameObject::boundingRect() const {
  return QRectF(-width_ / 2, -height_ / 2, width_, height_);
}
void GameObject::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
