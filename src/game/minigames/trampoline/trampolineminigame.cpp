#include "trampolineminigame.h"

#include <QMouseEvent>

TrampolineMinigame::TrampolineMinigame(GameView* graphics_view,
                                       qreal difficulty)
    : Minigame(graphics_view, difficulty) {
  graphics_view->SetPixelsInMeter(kPixelsInMeter);
}

void TrampolineMinigame::Start() { AnimateTutorial(); }

void TrampolineMinigame::SetUp() {
  SetParameters();
  time_bar_->setVisible(false);

  cat_ = new TrampolineCat(graphics_view_, kCatWidth, kCatHeight, kCatStartPos);
  cat_->SetUp();
  graphics_view_->scene()->addItem(cat_);

  trampoline_ = new Trampoline(graphics_view_, kTrampolineWidth,
                               kTrampolineHeight, kTrampolineStartPos);
  trampoline_->SetUp();
  graphics_view_->scene()->addItem(trampoline_);

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TrampolineMinigame::Tick);

  is_running_ = true;
  SetLabel();
}

void TrampolineMinigame::SetLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void TrampolineMinigame::SetParameters() {
  flip_count_ = 3;
  flip_time_ = 1000;
  drags_count_ = 2;
}

void TrampolineMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, this, &TrampolineMinigame::StartGame);
}

void TrampolineMinigame::StartGame() {
  tutorial_label_->setVisible(false);
  tick_timer_.start();
}

void TrampolineMinigame::AnimateOutro() {}

void TrampolineMinigame::Tick() {
  cat_->Update();
  if (cat_->collidesWithItem(trampoline_)) {
    if (cat_->GetFlying()) {
      cat_->SetFlying(false);
      cat_->SetVelocity(0, -cat_->GetVelocity().y());
    }
  } else if (!cat_->GetFlying()) {
    cat_->SetFlying(true);
  }
}

void TrampolineMinigame::MakeFlip() {}

void TrampolineMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  if (status == Status::kPass) {
    score_ = 100;
    Win();
  }
  if (status == Status::kFail) {
    Lose();
  }
}

void TrampolineMinigame::Win() {
  graphics_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void TrampolineMinigame::Lose() {
  graphics_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}
void TrampolineMinigame::MousePressEvent(QMouseEvent* event) {
  is_mouse_pressed_ = true;
  first_mouse_pressed_ = event->pos();
  last_mouse_pressed_ = first_mouse_pressed_;
}

void TrampolineMinigame::MouseReleaseEvent(QMouseEvent*) {
  is_mouse_pressed_ = false;
}

void TrampolineMinigame::MouseMoveEvent(QMouseEvent* event) {
  if (!is_mouse_pressed_) {
    return;
  }
  last_mouse_pressed_ = event->pos();
}
