#include "minigame.h"

MiniGame::MiniGame(QGraphicsView* graphics_view, int32_t width, int32_t height,
                   qreal difficulty)
    : graphics_view_(graphics_view),
      width_(width),
      height_(height),
      difficulty_(difficulty) {}
