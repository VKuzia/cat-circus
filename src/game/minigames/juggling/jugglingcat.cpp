#include "jugglingcat.h"

const qreal JugglingCat::kZValue = 0;
const qreal JugglingCat::kHandsZValue = 1;

JugglingCat::JugglingCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      left_hand_(new JugglingHand(game_view, kHandRadius * 2, kHandRadius * 2,
                                  pos.x() - size.width() / 2, pos.y(),
                                  JugglingHand::Side::kLeft)),
      right_hand_(new JugglingHand(game_view, kHandRadius * 2, kHandRadius * 2,
                                   pos.x() + size.width() / 2, pos.y(),
                                   JugglingHand::Side::kRight)) {}

void JugglingCat::SetUp() {
  SetUpHand(left_hand_, right_hand_->GetBasePos());
  SetUpHand(right_hand_, left_hand_->GetBasePos());
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
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
