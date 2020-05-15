#include "cannon.h"

Cannon::Cannon(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Cannon::SetUp() { setPixmap(LoadPixmap("cannon/cannon.png")); }
