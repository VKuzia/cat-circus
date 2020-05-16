#include "cannonsatus.h"

CannonStatus::CannonStatus(GameView *game_view, qreal width, qreal height,
                           qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonStatus::SetUp() {
  setPixmap(LoadPixmap("cannon/no.png"));
  success_pixmap_ = LoadPixmap("cannon/ok.png");
}

void CannonStatus::ChangeStatus() { setPixmap(success_pixmap_); }
