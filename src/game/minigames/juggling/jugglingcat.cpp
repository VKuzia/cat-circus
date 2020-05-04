#include "jugglingcat.h"

const qreal JugglingCat::kZValue = 0;
const qreal JugglingCat::kHandsZValue = 1;

JugglingCat::JugglingCat(GameView* game_view, qreal width, qreal height,
                         qreal x, qreal y)
    : GameObject(game_view, width, height, x, y),
      left_hand_(new JugglingHand(game_view, kHandRadius * 2,
                                  kHandRadius * 2, x - width_ / 2, y, true)),
      right_hand_(new JugglingHand(game_view, kHandRadius * 2,
                                   kHandRadius * 2, x + width_ / 2, y, false)) {
}

void JugglingCat::SetUp() {
  SetUpHand(left_hand_, right_hand_->GetBasePos());
  SetUpHand(right_hand_, left_hand_->GetBasePos());
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void JugglingCat::Update() {
  left_hand_->Update();
  right_hand_->Update();
}
JugglingHand* JugglingCat::GetLeftHand() { return left_hand_; }

JugglingHand* JugglingCat::GetRightHand() { return right_hand_; }

void JugglingCat::SetUpHand(JugglingHand* hand, QPointF aim_point) {
  hand->SetUp();
  hand->setZValue(kHandsZValue);
  hand->SetAimPoint(aim_point);
  game_view_->scene()->addItem(hand);
}
