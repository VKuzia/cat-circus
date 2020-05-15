#include "yes.h"

Yes::Yes(GameView *game_view, qreal width, qreal height, qreal x, qreal y)
    : GameObject(game_view, width, height, x, y) {}

void Yes::SetUp() { setPixmap(LoadPixmap("cannon/ok.png")); }
