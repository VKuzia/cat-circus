#include "clickableball.h"

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

ClickableBall::ClickableBall(GameView* game_view, qreal width, qreal height,
                             QPointF pos)
    : GameObject(game_view, width, height, pos) {}

void ClickableBall::SetUp() {
  //  qreal width = boundingRect().width();
  //  qreal height = boundingRect().height();
  //  QPixmap pixmap(boundingRect().size().toSize());
  //  QPainter painter(&pixmap);
  //  painter.setBrush(kBasicColor);
  //  // Some edge pixels left to render ball without edges cut
  //  painter.drawEllipse(1, 1, qFloor(width) - 2, qFloor(height) - 2);
  setPixmap(LoadPixmap("plate/sausage.png"));
}

void ClickableBall::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit Clicked();
}
