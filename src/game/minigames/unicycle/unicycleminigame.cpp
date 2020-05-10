#include "unicycleminigame.h"

#include <QKeyEvent>

UnicycleMinigame::UnicycleMinigame(GameView* game_view, qreal difficulty,
                                   qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void UnicycleMinigame::Start() { AnimateTutorial(); }

void UnicycleMinigame::SetUp() {
  cat_ = new UnicycleCat(game_view_, kCatSize_, kCatStartPos_);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  tiger_ = new UnicycleTiger(game_view_, kTigerSize_, kTigerStartPos_);
  tiger_->SetUp();
  tiger_->SetVelocity(tiger_velocity_);
  game_view_->scene()->addItem(tiger_);
}

void UnicycleMinigame::SetUpLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(std::numeric_limits<qreal>::max());
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void UnicycleMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] { StartGame(); });
}

void UnicycleMinigame::StartGame() {
  time_bar_->setVisible(true);
  tutorial_label_->setVisible(false);
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &UnicycleMinigame::Tick);

  is_running_ = true;
  tick_timer_.start();
}

void UnicycleMinigame::AnimateOutro() {}

void UnicycleMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  cat_->Update();
  qreal progress =
      (cat_->GetX() - kCatStartPos_.x()) / (kCatGoalX_ - kCatStartPos_.x());
  time_bar_->SetProgress(1 - progress);
  if (progress >= 1) {
    Stop(Status::kPass);
  }
  tiger_->Update();
  if (tiger_->collidesWithItem(cat_)) {
    Stop(Status::kFail);
  }
}

void UnicycleMinigame::SetUpParameters() {
  cat_step_acceleration_ = {0.2, 0};
  tiger_velocity_ = {0.4, 0};
}

void UnicycleMinigame::Stop(Minigame::Status status) {
  is_running_ = false;
  tick_timer_.stop();
  time_bar_->setVisible(false);
  switch (status) {
    case Status::kPass:
      score_ = 100;
      Win();
      break;
    case Status::kFail:
      Lose();
      break;
  }
}

void UnicycleMinigame::Win() {
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush_);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush_);
    emit Passed(score_);
  });
}

void UnicycleMinigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush_);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush_);
    emit Failed();
  });
}

void UnicycleMinigame::KeyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_A &&
      (current_key_ == CurrentKey::kLeft || current_key_ == CurrentKey::kAny)) {
    current_key_ = CurrentKey::kRight;
    cat_->AddVelocity(cat_step_acceleration_);
  } else if (event->key() == Qt::Key_D && (current_key_ == CurrentKey::kRight ||
                                           current_key_ == CurrentKey::kAny)) {
    current_key_ = CurrentKey::kLeft;
    cat_->AddVelocity(cat_step_acceleration_);
  }
}

void UnicycleMinigame::KeyReleaseEvent(QKeyEvent*) {}
