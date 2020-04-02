#include "testminigame.h"

TestMiniGame::TestMiniGame(QGraphicsView* graphics_view, qreal difficulty)
    : MiniGame(graphics_view, difficulty) {
  time_ = kBasicDuration;
}

TestMiniGame::~TestMiniGame() {}

void TestMiniGame::Start() {
  finish_timer_->setInterval(kBasicDuration);
  connect(finish_timer_, &QTimer::timeout, this, &TestMiniGame::Stop);

  tick_timer_->setInterval(1000 / kFps);
  connect(tick_timer_, &QTimer::timeout, this, &TestMiniGame::Tick);

  is_running_ = true;
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(227, 124, 7)));

  finish_timer_->start();
  tick_timer_->start();
}

void TestMiniGame::Pause() {
  is_running_ = false;
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = finish_timer_->remainingTime();
  finish_timer_->stop();
  finish_timer_->setInterval(remaining_time_);
}

void TestMiniGame::Resume() {
  is_running_ = true;
  finish_timer_->start();
}

void TestMiniGame::MousePressEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(200, 0, 0)));
}

void TestMiniGame::MouseReleaseEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(227, 124, 7)));
}

void TestMiniGame::MouseMoveEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(0, 200, 0)));
}

void TestMiniGame::KeyPressEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(0, 0, 200)));
}

void TestMiniGame::KeyReleaseEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(227, 124, 7)));
}

void TestMiniGame::Tick() {
  if (!is_running_) {
    return;
  }
  time_bar_->SetProgress(1.0 * finish_timer_->remainingTime() / kBasicDuration);

  time_bar_->update();
}

void TestMiniGame::Stop() {
  is_running_ = false;
  finish_timer_->stop();
  tick_timer_->stop();
  graphics_view_->scene()->setBackgroundBrush(Qt::NoBrush);
  emit Passed(0);
}

void TestMiniGame::Win() {}

void TestMiniGame::Lose() {}
