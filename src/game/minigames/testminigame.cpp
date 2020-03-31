#include "testminigame.h"

TestMiniGame::TestMiniGame(QGraphicsView* graphics_view, qreal difficulty)
    : MiniGame(graphics_view, difficulty) {}

TestMiniGame::~TestMiniGame() {}

void TestMiniGame::Start() {
  finish_timer_->setInterval(kBasicDuration);
  connect(finish_timer_, &QTimer::timeout, this, &TestMiniGame::Stop);
  is_running_ = true;
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(227, 124, 7)));
  finish_timer_->start();
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

void TestMiniGame::Stop() {
  is_running_ = false;
  finish_timer_->stop();
  graphics_view_->scene()->setBackgroundBrush(Qt::NoBrush);
  emit Passed(0);
}

void TestMiniGame::Win() {}

void TestMiniGame::Lose() {}
