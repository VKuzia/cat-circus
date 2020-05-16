#include "cannoncat.h"

#include "cannonsausage.h"

CannonCat::CannonCat(GameView *game_view, qreal width, qreal height, qreal x,
                     qreal y, qreal floor_y)
    : GameObject(game_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

void CannonCat::SetUp() { setPixmap(LoadPixmap("juggling/cat.png")); }

void CannonCat::Update() {
  if (cat_velocity_.IsZero()) {
    cat_velocity_.setX(cos(angle_) * power_);
    cat_velocity_.setY(-sin(angle_) * power_);
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

int CannonCat::GetCaught() const { return caught_sausages_; }

void CannonCat::CatchSausage() {
  // Check if Sausage is caught
  const QList<QGraphicsItem *> sausages = this->collidingItems();
  //      scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(-30, -30)
  //                                 << mapToScene(30, -30));

  for (QGraphicsItem *item : sausages) {
    if (item == this) {
      continue;
    } else {
      if (dynamic_cast<CannonSausage *>(item)) {
        caught_sausages_++;
        dynamic_cast<CannonSausage *>(item)->WasCaught();
      }
    }
  }
}

// void CannonCat::CaughtSausage() {}
