#include "jugglinghand.h"

JugglingHand::JugglingHand(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, bool left)
    : GameObject(graphics_view, width, height, x, y),
      is_left_(left),
      base_pos_(x, y),
      throw_pos_(x_ + (is_left_ ? kThrowXRange : -kThrowXRange), y_) {}

JugglingHand::~JugglingHand() {
  delete pixmap_free_;
  delete pixmap_closed_;
}

void JugglingHand::SetUp() {
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  pixmap_free_ = new QPixmap(kPathToMinigameImages + "juggling/hand_free.png");
  pixmap_free_->setMask(pixmap_free_->createHeuristicMask());
  *pixmap_free_ = pixmap_free_->scaled(qRound(boundingRect().width()),
                                       qRound(boundingRect().height()));

  pixmap_closed_ =
      new QPixmap(kPathToMinigameImages + "juggling/hand_closed.png");
  pixmap_closed_->setMask(pixmap_closed_->createHeuristicMask());
  *pixmap_closed_ = pixmap_closed_->scaled(qRound(boundingRect().width()),
                                           qRound(boundingRect().height()));
  this->setPixmap(*pixmap_free_);
}

void JugglingHand::Update() {
  if (!is_throwing_) {
    return;
  }
  if (!is_just_thrown_) {
    if (qAbs(base_pos_.x() - GetX()) >= kThrowXRange) {
      is_just_thrown_ = true;
      SetVelocity(kThrowXRange * (is_left_ ? -1.0 : 1.0) / (kComeBackTime), 0);
      for (auto ball : balls_) {
        balls_.remove(ball);
        ball->SetVelocity(GetThrowVelocity());
        ball->SetCaught(false);
      }
    } else {
      AddVelocity(0, kAcceleration.y() * kUpdateTime);
    }
  }
  qreal x_difference = static_cast<qreal>(velocity_.x()) * kUpdateTime;
  qreal y_difference = static_cast<qreal>(velocity_.y()) * kUpdateTime;
  if (is_just_thrown_ &&
      ((is_left_ && (GetX() + x_difference) < base_pos_.x()) ||
       (!is_left_ && (GetX() + x_difference) > base_pos_.x()))) {
    this->setPixmap(*pixmap_free_);
    is_throwing_ = false;
    SetVelocity(0, 0);
    x_difference = (base_pos_.x() - GetX());
    y_difference = (base_pos_.y() - GetY());
  }
  MoveByMeters(x_difference, y_difference);
  for (auto ball : balls_) {
    ball->MoveByMeters(x_difference, y_difference);
  }
}

void JugglingHand::Throw() {
  if (is_throwing_) {
    return;
  }
  this->setPixmap(*pixmap_closed_);
  is_throwing_ = true;
  is_just_thrown_ = false;
  SetVelocity(physics::Throw(base_pos_, throw_pos_, kThrowTime, kAcceleration));
}

void JugglingHand::SetAimPoint(const QPointF& point) { aim_point_ = point; }

void JugglingHand::AddBall(JugglingBall* ball) { balls_.insert(ball); }

QPointF JugglingHand::GetBasePos() const { return base_pos_; }

Vector2D JugglingHand::GetThrowVelocity() const { return Vector2D(0.0, 0.0); }
