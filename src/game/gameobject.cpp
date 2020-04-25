#include "gameobject.h"

#include <QDir>

const QString GameObject::kPathToMinigameImages =
    QDir::currentPath() + "/data/images/minigames/";

GameObject::GameObject(GameView* graphics_view)
    : graphics_view_(graphics_view) {
  this->setCacheMode(ItemCoordinateCache);
}

GameObject::GameObject(GameView* graphics_view, qreal width, qreal height,
                       qreal x, qreal y)
    : GameObject(graphics_view, width, height, QPointF(x, y)) {}

GameObject::GameObject(GameView* graphics_view, qreal width, qreal height,
                       QPointF pos)
    : kDefaultBoundingRect(
          QRectF(-width * graphics_view->GetPixelsInMeter() / 2,
                 -height * graphics_view->GetPixelsInMeter() / 2,
                 width * graphics_view->GetPixelsInMeter(),
                 height * graphics_view->GetPixelsInMeter())),
      graphics_view_(graphics_view),
      width_(width),
      height_(height),
      x_(pos.x()),
      y_(pos.y()) {
  this->setCacheMode(ItemCoordinateCache);
  setPos(x_ * graphics_view_->GetPixelsInMeter(),
         y_ * graphics_view_->GetPixelsInMeter());
}

void GameObject::SetUp() {}
void GameObject::Update() {}

QRectF GameObject::boundingRect() const { return kDefaultBoundingRect; }

qreal GameObject::GetX() const { return x_; }

void GameObject::SetX(qreal x) { x_ = x; }

qreal GameObject::GetY() const { return y_; }

void GameObject::SetY(qreal y) { y_ = y; }

QPointF GameObject::GetPos() const { return QPointF(GetX(), GetY()); }

void GameObject::SetPos(QPointF pos) {
  SetX(pos.x());
  SetY(pos.y());
}

void GameObject::AddVelocity(qreal x, qreal y) { velocity_ += Vector2D(x, y); }

void GameObject::SetVelocity(qreal x, qreal y) { velocity_ = Vector2D(x, y); }

void GameObject::SetVelocity(Vector2D velocity) { velocity_ = velocity; }

void GameObject::MoveByMeters(qreal x, qreal y) {
  SetX(x + GetX());
  SetY(y + GetY());
  moveBy(x * graphics_view_->GetPixelsInMeter(),
         y * graphics_view_->GetPixelsInMeter());
}
