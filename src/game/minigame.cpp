#include "minigame.h"

MiniGame::MiniGame(QGraphicsView* graphics_view, int32_t width, int32_t height,
                   qreal difficulty)
    : graphics_view_(graphics_view),
      finish_timer_(new QTimer(this)),
      width_(width),
      height_(height),
      difficulty_(difficulty) {}

MiniGame::~MiniGame() {
  if (finish_timer_ != nullptr) {
    finish_timer_->stop();
    delete finish_timer_;
  }
}
