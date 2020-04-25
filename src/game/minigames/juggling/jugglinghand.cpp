#include "jugglinghand.h"

JugglingHand::JugglingHand(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, bool left)
    : GameObject(graphics_view, width, height, x, y),
      base_pos_(x, y),
      is_left_(left) {}

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

void JugglingHand::Update() {}

void JugglingHand::Throw() {}

void JugglingHand::SetAimPoint(const QPointF& point) { aim_point_ = point; }

void JugglingHand::AddBall(JugglingBall* ball) { balls_.insert(ball); }

QPointF JugglingHand::GetBasePos() const { return base_pos_; }

Vector2D JugglingHand::GetThrowVelocity() const { return Vector2D(0.0, 0.0); }
