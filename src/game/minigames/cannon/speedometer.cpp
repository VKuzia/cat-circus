#include "speedometer.h"

Speedometer::Speedometer(GameView *game_view, qreal width, qreal height,
                         qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Speedometer::SetUp() { setPixmap(LoadPixmap("cannon/spedometer.png")); }
