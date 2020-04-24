#include "jugglinghand.h"

JugglingHand::JugglingHand(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, bool left)
    : GameObject(graphics_view, width, height, x, y),
      base_pos_(x, y),
      is_left_(left) {}

JugglingHand::~JugglingHand() {}

void JugglingHand::SetUp() {}

void JugglingHand::Update() {}

void JugglingHand::Throw() {}

void JugglingHand::SetAimPoint(const QPointF& point) { aim_point_ = point; }

void JugglingHand::AddBall(JugglingBall* ball) { balls_.insert(ball); }

QPointF JugglingHand::GetBasePos() const { return base_pos_; }

QVector2D JugglingHand::GetThrowVelocity() const {
  return QVector2D(0.0f, 0.0f);
}
