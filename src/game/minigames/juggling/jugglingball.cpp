#include "jugglingball.h"

const qreal JugglingBall::kZValue = 2;

JugglingBall::JugglingBall(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

JugglingBall::~JugglingBall() {}

void JugglingBall::SetUp() {
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap = QPixmap(kPathToMinigameImages + "juggling/ball.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void JugglingBall::Update() {
  if (is_caught_) {
    return;
  }
  if (GetY() < floor_y_ - radius_) {
    AddVelocity(0, physics::kGravity.y() * kUpdateTime);
  } else {
    SetVelocity(0.0, 0.0);
  }
  qreal x_difference = static_cast<double>(velocity_.x()) * kUpdateTime;
  qreal y_difference = static_cast<double>(velocity_.y()) * kUpdateTime;
  if (GetY() + y_difference > floor_y_ - radius_) {
    y_difference = floor_y_ - radius_ - GetY();
  }
  this->MoveByMeters(x_difference, y_difference);
}

void JugglingBall::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal JugglingBall::GetRadius() const { return radius_; }
