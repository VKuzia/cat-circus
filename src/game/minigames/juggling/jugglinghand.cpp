#include "jugglinghand.h"

JugglingHand::JugglingHand(GameView* game_view, qreal width, qreal height,
                           qreal x, qreal y, Side side)
    : GameObject(game_view, width, height, x, y),
      kSide_(side),
      kBasePos_(x, y),
      kThrowPos_(x_ + GetHorizontalSwing(), y_) {}

void JugglingHand::SetUp() {
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  pixmap_free_ =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/hand_free.png");
  pixmap_free_.setMask(pixmap_free_.createHeuristicMask());
  pixmap_free_ = pixmap_free_.scaled(qRound(boundingRect().width()),
                                     qRound(boundingRect().height()));

  pixmap_closed_ = QPixmap(game_view_->GetPathToMinigameImages() +
                           "juggling/hand_closed.png");
  pixmap_closed_.setMask(pixmap_closed_.createHeuristicMask());
  pixmap_closed_ = pixmap_closed_.scaled(qRound(boundingRect().width()),
                                         qRound(boundingRect().height()));
  this->setPixmap(pixmap_free_);
}

void JugglingHand::Update() {
  if (!is_throwing_) {
    return;
  }
  // If hand still holds some balls
  if (!is_coming_back_) {
    // If distance passed is sufficient for a throw
    if (qAbs(kBasePos_.x() - GetX()) >= kSwingXRange) {
      is_coming_back_ = true;
      // Return to base_pos_
      SetVelocity(-GetHorizontalSwing() / kComeBackTime, 0);
      // If there are several balls caught, we need to throw all of them
      if (current_ball_ != nullptr) {
        current_ball_->SetVelocity(GetThrowVelocity());
        current_ball_->SetCaught(false);
        // Release the ball
        current_ball_ = nullptr;
      }
    } else {
      AddVelocity(kAcceleration.x() * kUpdateTime,
                  kAcceleration.y() * kUpdateTime);
    }
  }
  qreal x_difference = velocity_.x() * kUpdateTime;
  qreal y_difference = velocity_.y() * kUpdateTime;
  // If we are close enough to base_pos_ -> move right to base_pos_
  if (is_coming_back_ &&
      ((kSide_ == Side::kLeft && (GetX() + x_difference) < kBasePos_.x()) ||
       (kSide_ == Side::kRight && (GetX() + x_difference) > kBasePos_.x()))) {
    this->setPixmap(pixmap_free_);
    is_throwing_ = false;
    is_coming_back_ = false;
    SetVelocity(0, 0);
    x_difference = (kBasePos_.x() - GetX());
    y_difference = (kBasePos_.y() - GetY());
  }
  MoveByMeters(x_difference, y_difference);
  if (current_ball_ != nullptr) {
    current_ball_->MoveByMeters(x_difference, y_difference);
  }
}

void JugglingHand::Throw() {
  if (is_throwing_) {
    return;
  }
  this->setPixmap(pixmap_closed_);
  is_throwing_ = true;
  is_coming_back_ = false;
  SetVelocity(physics::Throw(kBasePos_, kThrowPos_, kThrowTime, kAcceleration));
}

void JugglingHand::SetAimPoint(const QPointF& point) { aim_point_ = point; }

void JugglingHand::SetBall(JugglingBall* ball) { current_ball_ = ball; }

QPointF JugglingHand::GetBasePos() const { return kBasePos_; }

void JugglingHand::SetBallAirTime(qreal sec) { ball_air_time_ = sec; }

bool JugglingHand::IsThrowing() const { return is_throwing_; }

Vector2D JugglingHand::GetThrowVelocity() const {
  return physics::Throw(GetPos(), aim_point_, ball_air_time_);
}

qreal JugglingHand::GetHorizontalSwing() const {
  qreal swing;
  switch (kSide_) {
    case Side::kLeft:
      swing = kSwingXRange;
      break;
    case Side::kRight:
      swing = -kSwingXRange;
      break;
  }
  return swing;
}
