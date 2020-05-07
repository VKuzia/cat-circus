#include "cannon.h"

Cannon::Cannon(GameView* graphics_view, qreal width, qreal height, qreal x,
               qreal y)
    : GameObject(graphics_view, width, height, x, y), base_pos_(x, y) {}

void Cannon::SetUp() {}

void Cannon::Update() {
  if (!is_throwing_) {
    return;
  }
  // If hand still holds some balls
  if (!is_just_thrown_) {
    // If distance passed is sufficient for a throw
    if (qAbs(base_pos_.x() - GetX()) >= kThrowXRange) {
      is_just_thrown_ = true;
      // Return to base_pos_
      SetVelocity(kThrowXRange / (kComeBackTime), 0);
      // If there are several balls caught, we need to throw all of them
    } else {
      AddVelocity(0, kAcceleration.y() * kUpdateTime);
    }
  }
  qreal x_difference = static_cast<qreal>(velocity_.x()) * kUpdateTime;
  qreal y_difference = static_cast<qreal>(velocity_.y()) * kUpdateTime;
  // If we are close enough to base_pos_ -> move right to base_pos_
  if (is_just_thrown_ && ((GetX() + x_difference < base_pos_.x()) ||
                          ((GetX() + x_difference) > base_pos_.x()))) {
    this->setPixmap(pixmap_free_);
    is_throwing_ = false;
    SetVelocity(0, 0);
    x_difference = (base_pos_.x() - GetX());
    y_difference = (base_pos_.y() - GetY());
  }
  MoveByMeters(x_difference, y_difference);
  cat_->MoveByMeters(x_difference, y_difference);
}

void Cannon::Throw() {
  if (is_throwing_) {
    return;
  }
  this->setPixmap(pixmap_closed_);
  is_throwing_ = true;
  is_just_thrown_ = false;
  SetVelocity(physics::Throw(base_pos_, throw_pos_, kThrowTime, kAcceleration));
}

void Cannon::SetAimPoint(const QPointF& point) { aim_point_ = point; }

void Cannon::AddCat(Cannoncat* cat) { cat_ = cat; }

QPointF Cannon::GetBasePos() const { return base_pos_; }

void Cannon::SetBallAirTime(qreal sec) { ball_air_time_ = sec; }

Vector2D Cannon::GetThrowVelocity() const {
  return physics::Throw(GetPos(), aim_point_, ball_air_time_);
}
