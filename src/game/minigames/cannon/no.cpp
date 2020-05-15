#include "no.h"

No::No(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void No::SetUp() { setPixmap(LoadPixmap("cannon/no.png")); }
