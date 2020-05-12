#include "gameobject.h"

PixmapLoader GameObject::pixmap_loader_ = PixmapLoader();

GameObject::GameObject(GameView* game_view, qreal width, qreal height, qreal x,
                       qreal y)
    : GameObject(game_view, width, height, QPointF(x, y)) {}

GameObject::GameObject(GameView* game_view, qreal width, qreal height,
                       QPointF pos)
    : GameObject(game_view, QSizeF(width, height), pos) {}

GameObject::GameObject(GameView* game_view, QSizeF size, QPointF pos)
    : kDefaultBoundingRect(
          QRectF(-size.width() * game_view->GetPixelsInMeter() / 2,
                 -size.height() * game_view->GetPixelsInMeter() / 2,
                 size.width() * game_view->GetPixelsInMeter(),
                 size.height() * game_view->GetPixelsInMeter())),
      game_view_(game_view),
      size_(size),
      pos_(pos) {
  this->setCacheMode(DeviceCoordinateCache);
  setPos(pos_ * game_view_->GetPixelsInMeter());
}

void GameObject::SetUp() {}

void GameObject::Update() {}

QRectF GameObject::boundingRect() const { return kDefaultBoundingRect; }

qreal GameObject::GetX() const { return pos_.x(); }

void GameObject::SetX(qreal x) { pos_.setX(x); }

qreal GameObject::GetY() const { return pos_.y(); }

void GameObject::SetY(qreal y) { pos_.setY(y); }

QPointF GameObject::GetPos() const { return pos_; }

void GameObject::SetPos(QPointF pos) { pos_ = pos; }

void GameObject::AddVelocity(qreal x, qreal y) { velocity_ += Vector2D(x, y); }

void GameObject::AddVelocity(Vector2D rhs) { velocity_ += rhs; }

void GameObject::SetVelocity(qreal x, qreal y) { velocity_ = Vector2D(x, y); }

void GameObject::SetVelocity(Vector2D velocity) { velocity_ = velocity; }

void GameObject::MoveByMeters(qreal x, qreal y) {
  SetX(x + GetX());
  SetY(y + GetY());
  moveBy(x * game_view_->GetPixelsInMeter(),
         y * game_view_->GetPixelsInMeter());
}

void GameObject::MoveByMeters(Vector2D shift) {
  pos_ += shift;
  moveBy(shift.x() * game_view_->GetPixelsInMeter(),
         shift.y() * game_view_->GetPixelsInMeter());
}
