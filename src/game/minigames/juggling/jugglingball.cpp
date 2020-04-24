#include "jugglingball.h"

const qreal JugglingBall::kZValue = 2;

JugglingBall::JugglingBall(GameView* graphics_view, qreal width, qreal height,
                           qreal x, qreal y, qreal floor_y)
    : GameObject(graphics_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

JugglingBall::~JugglingBall() {}

void JugglingBall::SetUp() {
  this->setZValue(kZValue);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap = QPixmap(GetPathToMinigameImages() + "juggling/ball.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(qRound(boundingRect().width()),
                                qRound(boundingRect().height())));
}

void JugglingBall::Update() {}

void JugglingBall::SetCaught(bool is_caught) { is_caught_ = is_caught; }

qreal JugglingBall::GetRadius() const { return radius_; }
