#include "jugglinghand.h"

#include <stdexcept>

JugglingHand::JugglingHand(GameView* game_view, qreal width, qreal height,
                           qreal x, qreal y, Side side)
    : GameObject(game_view, width, height, x, y),
      kPixmapFree_(GetPixmapLoader()->GetPixmap(
          "juggling/hand_free.png", boundingRect().size().toSize())),
      kPixmapClosed_(GetPixmapLoader()->GetPixmap(
          "juggling/hand_closed.png", boundingRect().size().toSize())),
      kSide_(side),
      kBasePos_(x, y),
      kThrowPos_(x + GetHorizontalSwing(), y) {}

void JugglingHand::SetUp() { setPixmap(kPixmapFree_); }

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
      AddVelocity(kAcceleration * kUpdateTime);
    }
  }
  Vector2D shift = velocity_ * kUpdateTime;
  // If we are close enough to base_pos_ -> move right to base_pos_
  if (is_coming_back_ &&
      ((kSide_ == Side::kLeft && (GetX() + shift.x()) < kBasePos_.x()) ||
       (kSide_ == Side::kRight && (GetX() + shift.x()) > kBasePos_.x()))) {
    this->setPixmap(kPixmapFree_);
    is_throwing_ = false;
    is_coming_back_ = false;
    SetVelocity(0, 0);
    shift = Vector2D(kBasePos_.x() - GetX(), kBasePos_.y() - GetY());
  }
  MoveByMeters(shift);
  if (current_ball_ != nullptr) {
    current_ball_->MoveByMeters(shift);
  }
}

void JugglingHand::Throw() {
  if (is_throwing_) {
    return;
  }
  this->setPixmap(kPixmapClosed_);
  is_throwing_ = true;
  is_coming_back_ = false;
  SetVelocity(physics::Throw(kBasePos_, kThrowPos_, kThrowTime, kAcceleration));
}

void JugglingHand::SetAimPoint(QPointF point) { aim_point_ = point; }

void JugglingHand::SetBall(JugglingBall* ball) { current_ball_ = ball; }

QPointF JugglingHand::GetBasePos() const { return kBasePos_; }

void JugglingHand::SetBallAirTime(qreal sec) { ball_air_time_ = sec; }

bool JugglingHand::IsThrowing() const { return is_throwing_; }

Vector2D JugglingHand::GetThrowVelocity() const {
  return physics::Throw(GetPos(), aim_point_, ball_air_time_);
}

qreal JugglingHand::GetHorizontalSwing() const {
  switch (kSide_) {
    case Side::kLeft:
      return kSwingXRange;
    case Side::kRight:
      return -kSwingXRange;
  }
  throw std::runtime_error("Unknown hand side");
}
