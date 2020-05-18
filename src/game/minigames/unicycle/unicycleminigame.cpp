#include "unicycleminigame.h"

#include <QKeyEvent>

UnicycleMinigame::UnicycleMinigame(GameView* game_view, qreal difficulty,
                                   qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void UnicycleMinigame::Start() { AnimateTutorial(); }

void UnicycleMinigame::SetUp() {
  background_->SetUp(game_view_, "unicycle/background.png");
  game_view_->scene()->addItem(background_);

  cat_ = new UnicycleCat(game_view_, kCatSize_, kCatStartPos_);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  tiger_ = new UnicycleTiger(game_view_, kTigerSize_, kTigerStartPos_);
  tiger_->SetUp();
  tiger_->SetVelocity(tiger_velocity_);
  game_view_->scene()->addItem(tiger_);

  grate_ = new UnicycleGrate(game_view_, kGrateSize_, kGratePos_);
  grate_->SetUp();
  game_view_->scene()->addItem(grate_);
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

  cat_->StartAnimation();

  is_running_ = true;
  tick_timer_.start();
}

void UnicycleMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  cat_->Update();
  qreal progress =
      (cat_->GetX() - kCatStartPos_.x()) / (kCatGoalX_ - kCatStartPos_.x());
  time_bar_->SetProgress(1 - progress);
  if (progress >= 1) {
    grate_->Close();
    tiger_->Stop();
    Stop(MinigameStatus::kPassed);
  }
  tiger_->Update();
  if (tiger_->collidesWithItem(cat_)) {
    Stop(MinigameStatus::kFailed);
  }
}

void UnicycleMinigame::SetUpParameters() {
  int32_t difficulty_level = qFloor(difficulty_ / (0.1));
  switch (difficulty_level) {
    case 0:
      cat_step_acceleration_ = {0.2, 0};
      tiger_velocity_ = {0.5, 0};
      break;
    case 1:
      cat_step_acceleration_ = {0.17, 0};
      tiger_velocity_ = {0.6, 0};
      break;
    case 2:
      cat_step_acceleration_ = {0.17, 0};
      tiger_velocity_ = {0.7, 0};
      break;
    case 3:
      cat_step_acceleration_ = {0.17, 0};
      tiger_velocity_ = {0.8, 0};
      break;
    case 4:
      cat_step_acceleration_ = {0.15, 0};
      tiger_velocity_ = {0.8, 0};
      break;
    case 5:
      cat_step_acceleration_ = {0.15, 0};
      tiger_velocity_ = {0.8, 0};
      break;
    case 6:
      cat_step_acceleration_ = {0.15, 0};
      tiger_velocity_ = {0.8, 0};
      break;
    case 7:
      cat_step_acceleration_ = {0.12, 0};
      tiger_velocity_ = {0.8, 0};
      break;
    default:
      cat_step_acceleration_ = {0.12, 0};
      tiger_velocity_ = {0.9, 0};
      break;
  }
}

void UnicycleMinigame::Stop(MinigameStatus status) {
  is_running_ = false;
  cat_->StopAnimation();
  tick_timer_.stop();
  time_bar_->setVisible(false);
  switch (status) {
    case MinigameStatus::kPassed:
      score_ = 100;
      Win();
      break;
    case MinigameStatus::kFailed:
      Lose();
      break;
  }
}

void UnicycleMinigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
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
