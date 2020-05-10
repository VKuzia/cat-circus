#include "unicycletiger.h"

UnicycleTiger::UnicycleTiger(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

void UnicycleTiger::SetUp() {
  QPixmap pixmap(boundingRect().size().toSize());
  QPainter painter(&pixmap);
  painter.setBrush(QColor::fromRgb(100, 10, 10));
  painter.drawRect(pixmap.rect());

  setOffset(-boundingRect().center());
  setPixmap(pixmap);

  SetVelocity(0, 0);
}

void UnicycleTiger::Update() { MoveByMeters(velocity_ * kUpdateTime); }

void UnicycleTiger::Stop() { SetVelocity(0, 0); }
