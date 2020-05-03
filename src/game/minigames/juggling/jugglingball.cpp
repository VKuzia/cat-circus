#include "jugglingball.h"

const qreal JugglingBall::kZValue = 2;

JugglingBall::JugglingBall(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

void JugglingBall::SetUp() {
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/ball.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void JugglingBall::Update() {
  if (is_caught_ || is_fallen_) {
    return;
  }
  AddVelocity(0, physics::kGravity.y() * kUpdateTime);
  qreal x_difference = velocity_.x() * kUpdateTime;
  qreal y_difference = velocity_.y() * kUpdateTime;
  // Checking if the floor was reached
  if (GetY() + y_difference + radius_ > floor_y_) {
    y_difference = floor_y_ - radius_ - GetY();
    is_fallen_ = true;
  }
  this->MoveByMeters(x_difference, y_difference);
}

void JugglingBall::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal JugglingBall::GetRadius() const { return radius_; }

void JugglingBall::SetFallen(bool is_fallen) { is_fallen_ = is_fallen; }

bool JugglingBall::IsFallen() const { return is_fallen_; }
