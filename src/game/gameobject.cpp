#include "gameobject.h"

GameObject::GameObject(GameView* game_view, qreal width, qreal height, qreal x,
                       qreal y)
    : GameObject(game_view, width, height, QPointF(x, y)) {}

GameObject::GameObject(GameView* game_view, qreal width, qreal height,
                       QPointF pos)
    : kDefaultBoundingRect(QRectF(-width * game_view->GetPixelsInMeter() / 2,
                                  -height * game_view->GetPixelsInMeter() / 2,
                                  width * game_view->GetPixelsInMeter(),
                                  height * game_view->GetPixelsInMeter())),
      game_view_(game_view),
      width_(width),
      height_(height),
      x_(pos.x()),
      y_(pos.y()) {
  this->setCacheMode(DeviceCoordinateCache);
  setPos(x_ * game_view_->GetPixelsInMeter(),
         y_ * game_view_->GetPixelsInMeter());
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
  moveBy(x * game_view_->GetPixelsInMeter(),
         y * game_view_->GetPixelsInMeter());
}
