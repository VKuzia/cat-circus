#include "minigame.h"

MiniGame::MiniGame(QGraphicsView* graphics_view, qreal difficulty)
    : graphics_view_(graphics_view),
      finish_timer_(new QTimer(this)),
      width_(graphics_view_->width()),
      height_(graphics_view_->height()),
      difficulty_(difficulty) {}

MiniGame::~MiniGame() {
  if (finish_timer_ != nullptr) {
    finish_timer_->stop();
    delete finish_timer_;
  }
}
