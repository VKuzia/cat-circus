#include "cannoncat.h"

#include "cannonsausage.h"

CannonCat::CannonCat(GameView* game_view, qreal width, qreal height, qreal x,
                     qreal y, qreal floor_y)
    : GameObject(game_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

void CannonCat::SetUp() { setPixmap(LoadPixmap("cannon/cat.png", true)); }

void CannonCat::Update() {
  if (cat_velocity_.IsZero()) {
    cat_velocity_.setX(cos(angle_) * power_);
    cat_velocity_.setY(-sin(angle_) * power_);
    Audio::PlaySound("cannon.wav");
  }
  if (is_in_flight_) {
    AddVelocity(cat_velocity_.x(), cat_velocity_.y());
    cat_velocity_ += kGravityCannon;
    Vector2D shift = velocity_ * kUpdateTime;
    this->MoveByMeters(shift);
    setRotation(rotation() + atan(shift.x() / shift.y()));
  }
  CatchSausage();
}

qreal CannonCat::GetRadius() const { return radius_; }

void CannonCat::SetAngle(qreal angle) { angle_ = angle; }

void CannonCat::SetPower(qreal power) { power_ = power; }

void CannonCat::CatchSausage() {
  const QList<QGraphicsItem*> items = this->collidingItems();
  for (QGraphicsItem* item : items) {
    if (item == this) {
      continue;
    }
    if (dynamic_cast<CannonSausage*>(item)) {
      dynamic_cast<CannonSausage*>(item)->WasCaught();
    }
  }
}
