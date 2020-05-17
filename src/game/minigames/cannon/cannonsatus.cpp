#include "cannonsatus.h"

CannonStatus::CannonStatus(GameView *game_view, qreal width, qreal height,
                           qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void CannonStatus::SetUp() { setPixmap(LoadPixmap("cannon/no.png")); }

void CannonStatus::ChangeStatus() { setPixmap(LoadPixmap("cannon/ok.png")); }
