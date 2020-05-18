#include "clickableball.h"

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(game_view, width, height, pos) {}

void ClickableBall::SetUp() {
  setPixmap(LoadPixmap("plate/sausage.png", true));
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
