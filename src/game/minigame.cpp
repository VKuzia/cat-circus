#include "minigame.h"

#include <limits>

#include "src/game/gameview.h"

Minigame::Minigame(GameView* game_view, qreal difficulty, qreal pixels_in_meter)
    : game_view_(game_view),
      timer_(this),
      tick_timer_(this),
      tutorial_label_(new QGraphicsTextItem()),
      background_(new BackgroundObject()),
      difficulty_(difficulty),
      pixels_in_meter_(pixels_in_meter) {}

Minigame::~Minigame() {
  // Сlear removes items from scene and deletes them
  game_view_->scene()->clear();
}

void Minigame::Init() {
  game_view_->SetPixelsInMeter(pixels_in_meter_);
  width_ = game_view_->width() / game_view_->GetPixelsInMeter();
  height_ = game_view_->height() / game_view_->GetPixelsInMeter();

  // Timebar needs game_view_ to know pixels in meter
  time_bar_ = new TimeBar(game_view_, width_, height_ * kTimeBarHeightFactor, 0,
                          -height_ / 2);
  time_bar_->SetUp();
  time_bar_->setVisible(false);
  game_view_->scene()->addItem(time_bar_);
  game_view_->scene()->addItem(tutorial_label_);
  SetUpParameters();
  SetUp();
}

void Minigame::MousePressEvent(QMouseEvent*) {}

void Minigame::MouseReleaseEvent(QMouseEvent*) {}

void Minigame::MouseMoveEvent(QMouseEvent*) {}

void Minigame::KeyPressEvent(QKeyEvent*) {}

void Minigame::KeyReleaseEvent(QKeyEvent*) {}

void Minigame::Win() {
  Audio::PlaySound("win.wav");
  game_view_->AnimateOutro(MinigameStatus::kPassed);
}

void Minigame::Lose() {
  Audio::PlaySound("lose1.mp3");
  game_view_->AnimateOutro(MinigameStatus::kFailed);
}

int32_t Minigame::GetScore() const { return score_; }

void Minigame::SetUpLabel(const QString& text) {
  tutorial_label_->setHtml(text);
  tutorial_label_->setFont(QFont("Verdana", 25));
  tutorial_label_->setDefaultTextColor(QColor::fromRgb(10, 201, 16));
  tutorial_label_->setTextWidth(game_view_->width() / 2);
  tutorial_label_->setZValue(std::numeric_limits<qreal>::max());
  tutorial_label_->setPos(-tutorial_label_->boundingRect().center());
}

void Minigame::WheelEvent(QWheelEvent*) {}
