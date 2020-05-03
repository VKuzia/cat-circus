#include "minigame.h"

#include "src/game/gameview.h"

Minigame::Minigame(GameView* graphics_view, qreal difficulty)
    : game_view_(graphics_view),
      timer_(this),
      tick_timer_(this),
      width_(game_view_->width()),
      height_(game_view_->height()),
      time_bar_(new TimeBar(game_view_, width_, height_ * kTimeBarHeightFactor,
                            0, -height_ / 2)),
      tutorial_label_(new QGraphicsTextItem()),
      background_(new BackgroundObject()),
      difficulty_(difficulty) {}

Minigame::~Minigame() {
  // clear removes and deletes items
  game_view_->scene()->clear();
}

void Minigame::Init() {
  time_bar_->SetUp();
  time_bar_->setVisible(false);
  game_view_->scene()->addItem(time_bar_);
  game_view_->scene()->addItem(tutorial_label_);
  SeUptParameters();
  SetUpLabel();
  SetUp();
}

void Minigame::MousePressEvent(QMouseEvent*) {}

void Minigame::MouseReleaseEvent(QMouseEvent*) {}

void Minigame::MouseMoveEvent(QMouseEvent*) {}

void Minigame::KeyPressEvent(QKeyEvent*) {}

void Minigame::KeyReleaseEvent(QKeyEvent*) {}
