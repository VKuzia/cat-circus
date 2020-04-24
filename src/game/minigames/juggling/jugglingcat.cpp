#include "jugglingcat.h"

JugglingCat::JugglingCat(GameView* graphics_view, qreal width, qreal height,
                         qreal x, qreal y)
    : GameObject(graphics_view, width, height, x, y),
      left_hand_(new JugglingHand(graphics_view, kHandRadius * 2,
                                  kHandRadius * 2, x - width_ / 2, y, true)),
      right_hand_(new JugglingHand(graphics_view, kHandRadius * 2,
                                   kHandRadius * 2, x + width_ / 2, y, false)) {
}

JugglingCat::~JugglingCat() {}

void JugglingCat::SetUp() { SetUpHands(); }

void JugglingCat::Update() {}

void JugglingCat::SetUpHands() {
  left_hand_->SetUp();
  right_hand_->SetUp();
  graphics_view_->scene()->addItem(left_hand_);
  graphics_view_->scene()->addItem(right_hand_);
}
JugglingHand* JugglingCat::GetLeftHand() { return left_hand_; }

JugglingHand* JugglingCat::GetRightHand() { return right_hand_; }
