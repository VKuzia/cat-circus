#include "jugglingcat.h"

const qreal JugglingCat::kZValue = 0;
const qreal JugglingCat::kHandsZValue = 1;

JugglingCat::JugglingCat(GameView* graphics_view, qreal width, qreal height,
                         qreal x, qreal y)
    : GameObject(graphics_view, width, height, x, y),
      left_hand_(new JugglingHand(graphics_view, kHandRadius * 2,
                                  kHandRadius * 2, x - width_ / 2, y, true)),
      right_hand_(new JugglingHand(graphics_view, kHandRadius * 2,
                                   kHandRadius * 2, x + width_ / 2, y, false)) {
}

JugglingCat::~JugglingCat() {}

void JugglingCat::SetUp() {
  SetUpHands();
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap = QPixmap(kPathToMinigameImages + "juggling/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void JugglingCat::Update() {}

void JugglingCat::SetUpHands() {
  left_hand_->SetUp();
  right_hand_->SetUp();
  left_hand_->setZValue(kHandsZValue);
  right_hand_->setZValue(kHandsZValue);
  graphics_view_->scene()->addItem(left_hand_);
  graphics_view_->scene()->addItem(right_hand_);
  left_hand_->SetAimPoint(right_hand_->GetBasePos());
  right_hand_->SetAimPoint(left_hand_->GetBasePos());
}
JugglingHand* JugglingCat::GetLeftHand() { return left_hand_; }

JugglingHand* JugglingCat::GetRightHand() { return right_hand_; }
