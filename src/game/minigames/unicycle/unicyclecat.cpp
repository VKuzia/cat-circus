#include "unicyclecat.h"

UnicycleCat::UnicycleCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

void UnicycleCat::SetUp() {
  QPixmap pixmap(boundingRect().size().toSize());
  QPainter painter(&pixmap);
  painter.setBrush(QColor::fromRgb(0, 100, 10));
  painter.drawRect(pixmap.rect());

  setOffset(-boundingRect().center());
  setPixmap(pixmap);

  SetVelocity(0, 0);
}

void UnicycleCat::Update() {
  MoveByMeters(velocity_ * kUpdateTime);
  if (velocity_.x() >= speed_loss_.x()) {
    velocity_ -= speed_loss_;
  } else {
    velocity_ = {0, 0};
  }
}
