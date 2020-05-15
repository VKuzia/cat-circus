#include "arrow.h"

Arrow::Arrow(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Arrow::SetUp() { setPixmap(LoadPixmap("cannon/arrow.png")); }
