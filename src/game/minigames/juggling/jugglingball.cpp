#include "jugglingball.h"

JugglingBall::JugglingBall(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

JugglingBall::~JugglingBall() {}

void JugglingBall::SetUp() {}

void JugglingBall::Update() {}

void JugglingBall::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal JugglingBall::GetRadius() const { return radius_; }
