#include "cannonsatus.h"

CannonStatus::CannonStatus(GameView *game_view, qreal width, qreal height,
                           qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonStatus::SetUp() { setPixmap(LoadPixmap("cannon/fail.png")); }

void CannonStatus::SetOk() { setPixmap(LoadPixmap("cannon/ok.png")); }
