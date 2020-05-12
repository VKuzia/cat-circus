#include "minigame.h"

#include "src/game/gameview.h"

Minigame::Minigame(GameView* game_view, qreal difficulty, qreal pixels_in_meter)
    : game_view_(game_view),
      timer_(this),
      tick_timer_(this),
      width_(game_view_->width() / pixels_in_meter),
      height_(game_view_->height() / pixels_in_meter),
      tutorial_label_(new QGraphicsTextItem()),
      background_(new BackgroundObject()),
      difficulty_(difficulty),
      pixels_in_meter_(pixels_in_meter) {}

Minigame::~Minigame() {
  // Сlear removes and deletes items
  game_view_->scene()->clear();
  GameObject::pixmap_loader_.ClearPixmaps();
}

void Minigame::Init() {
  game_view_->SetPixelsInMeter(pixels_in_meter_);
  // Timebar needs game_view_ to know pixels_in_meter_
  time_bar_ = new TimeBar(game_view_, width_, height_ * kTimeBarHeightFactor, 0,
                          -height_ / 2);
  time_bar_->SetUp();
  time_bar_->setVisible(false);
  game_view_->scene()->addItem(time_bar_);
  game_view_->scene()->addItem(tutorial_label_);
  SetUpParameters();
  SetUpLabel();
  SetUp();
}

void Minigame::MousePressEvent(QMouseEvent*) {}

void Minigame::MouseReleaseEvent(QMouseEvent*) {}

void Minigame::MouseMoveEvent(QMouseEvent*) {}

void Minigame::KeyPressEvent(QKeyEvent*) {}

void Minigame::KeyReleaseEvent(QKeyEvent*) {}
