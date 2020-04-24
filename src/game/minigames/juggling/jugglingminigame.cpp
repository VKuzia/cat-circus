#include "jugglingminigame.h"

#include <QKeyEvent>

JugglingMinigame::JugglingMinigame(GameView* graphics_view, qreal difficulty)
    : Minigame(graphics_view, difficulty) {}

JugglingMinigame::~JugglingMinigame() { delete cat_; }

void JugglingMinigame::Start() { AnimateTutorial(); }

void JugglingMinigame::SetUp() {
  SetParameters();
  cat_ = new JugglingCat(graphics_view_, 0, 0, 0, 0);
  cat_->SetUp();
  graphics_view_->scene()->addItem(cat_);

  SetLabel();
  time_bar_->setVisible(false);
}

void JugglingMinigame::SetLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void JugglingMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] {
    tutorial_label_->setVisible(false);
    time_bar_->setVisible(true);
    StartGame();
  });
}

void JugglingMinigame::StartGame() {
  timer_.setInterval(time_);
  connect(&timer_, &QTimer::timeout, [this] { Stop(Status::kPass); });

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &JugglingMinigame::Tick);

  is_running_ = true;

  timer_.start();
  tick_timer_.start();
  ball_timer_.start();
}

void JugglingMinigame::AnimateOutro() {}

void JugglingMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  time_bar_->SetProgress(1.0 * timer_.remainingTime() / time_);
  time_bar_->update();
}

void JugglingMinigame::SetParameters() { time_ = kDuration; }

void JugglingMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  timer_.stop();
  ball_timer_.stop();
  time_bar_->setVisible(false);
  if (status == Status::kPass) {
    Win();
  }
  if (status == Status::kFail) {
    Lose();
  }
}

void JugglingMinigame::Win() {
  graphics_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void JugglingMinigame::Lose() {
  graphics_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}

void JugglingMinigame::KeyPressEvent(QKeyEvent*) {
  graphics_view_->scene()->setBackgroundBrush(kKeyPressedBackgroundBrush);
}

void JugglingMinigame::KeyReleaseEvent(QKeyEvent*) {
  graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
}
