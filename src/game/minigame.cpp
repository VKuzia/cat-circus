#include "minigame.h"

Minigame::Minigame(QGraphicsView* graphics_view, float difficulty)
    : graphics_view_(graphics_view),
      timer_(new QTimer(this)),
      tick_timer_(new QTimer(this)),
      width_(graphics_view_->width()),
      height_(graphics_view_->height()),
      time_bar_(new TimeBar(graphics_view_, width_,
                            height_ * kTimeBarHeightFactor, 0, -height_ / 2)),
      tutorial_label_(new QGraphicsTextItem()),
      difficulty_(difficulty) {
  graphics_view_->scene()->addItem(time_bar_);
  graphics_view_->scene()->addItem(tutorial_label_);
}

Minigame::~Minigame() {
  if (timer_ != nullptr) {
    timer_->stop();
    delete timer_;
  }
  if (tick_timer_ != nullptr) {
    tick_timer_->stop();
    delete tick_timer_;
  }
  // clear removes and deletes items
  graphics_view_->scene()->clear();
}
