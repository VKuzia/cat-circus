#include "jugglingball.h"

const qreal JugglingBall::kZValue = 2;

JugglingBall::JugglingBall(GameView* game_view, qreal radius, qreal x, qreal y,
                           qreal floor_y)
    : GameObject(game_view, radius * 2, radius * 2, x, y),
      radius_(radius),
      floor_y_(floor_y) {}

void JugglingBall::SetUp() {
  setZValue(kZValue);
  setOffset(boundingRect().topLeft());
  setPixmap(GameObject::pixmap_loader_.GetPixmap(
      "juggling/ball.png", boundingRect().size().toSize()));
}

void JugglingBall::Update() {
  if (is_caught_ || is_fallen_) {
    return;
  }
  AddVelocity(0, physics::kGravity.y() * kUpdateTime);
  Vector2D shift = velocity_ * kUpdateTime;
  // Checking if the floor was reached
  if (GetY() + shift.y() + radius_ > floor_y_) {
    shift.setY(floor_y_ - radius_ - GetY());
    is_fallen_ = true;
  }
  this->MoveByMeters(shift);
}

void JugglingBall::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal JugglingBall::GetRadius() const { return radius_; }

void JugglingBall::SetFallen(bool is_fallen) { is_fallen_ = is_fallen; }

bool JugglingBall::IsFallen() const { return is_fallen_; }
