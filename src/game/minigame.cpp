#include "minigame.h"

Minigame::Minigame(QGraphicsView* graphics_view, qreal difficulty)
    : graphics_view_(graphics_view),
      timer_(this),
      tick_timer_(this),
      width_(graphics_view_->width()),
      height_(graphics_view_->height()),
      time_bar_(new TimeBar(graphics_view_, width_,
                            height_ * kTimeBarHeightFactor, 0, -height_ / 2)),
      tutorial_label_(new QGraphicsTextItem()),
      difficulty_(difficulty) {}

Minigame::~Minigame() {
  // clear removes and deletes items
  graphics_view_->scene()->clear();
}

void Minigame::Init() {
  graphics_view_->scene()->addItem(time_bar_);
  graphics_view_->scene()->addItem(tutorial_label_);
  SetUp();
}
