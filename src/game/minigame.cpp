#include "minigame.h"

MiniGame::MiniGame(QGraphicsView* graphics_view, qreal difficulty)
    : graphics_view_(graphics_view),
      finish_timer_(new QTimer(this)),
      tick_timer_(new QTimer(this)),
      width_(graphics_view_->width()),
      height_(graphics_view_->height()),
      time_bar_(new TimeBar(graphics_view_, width_,
                            height_ * kTimeBarHeightFactor, 0, -height_ / 2)),
      difficulty_(difficulty) {
  graphics_view_->scene()->addItem(time_bar_);
}

MiniGame::~MiniGame() {
  if (finish_timer_ != nullptr) {
    finish_timer_->stop();
    delete finish_timer_;
  }
  if (tick_timer_ != nullptr) {
    tick_timer_->stop();
    delete tick_timer_;
  }
  graphics_view_->scene()->removeItem(time_bar_);
  delete time_bar_;
}
