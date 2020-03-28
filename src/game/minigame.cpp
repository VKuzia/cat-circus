#include "minigame.h"

MiniGame::MiniGame(QGraphicsView* render_area, double difficulty)
    : render_area_(render_area), difficulty_(difficulty) {}

MiniGame::~MiniGame() {}
