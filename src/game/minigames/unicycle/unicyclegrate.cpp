#include "unicyclegrate.h"

UnicycleGrate::UnicycleGrate(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

void UnicycleGrate::SetUp() {
  QPixmap pixmap(boundingRect().size().toSize());
  QPainter painter(&pixmap);
  painter.setBrush(QColor::fromRgb(200, 200, 200));
  painter.drawRect(pixmap.rect());

  setOffset(-boundingRect().center());
  setPixmap(pixmap);
}

void UnicycleGrate::Close() {
  QPixmap pixmap(boundingRect().size().toSize());
  QPainter painter(&pixmap);
  painter.setBrush(QColor::fromRgb(0, 0, 0));
  painter.drawRect(pixmap.rect());

  setOffset(-boundingRect().center());
  setPixmap(pixmap);
}
