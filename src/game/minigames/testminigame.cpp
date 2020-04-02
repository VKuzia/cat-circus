#include "testminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator64>

#include "src/game/game_objects/clickableball.h"

TestMiniGame::TestMiniGame(QGraphicsView* graphics_view, qreal difficulty)
    : MiniGame(graphics_view, difficulty) {
  // Random coefs just for testing the game loop
  time_ = qRound(kBasicDuration / (difficulty_ * 1.5 + 1.0));
  balls_count_ = kBasicBallNumber + qRound((difficulty_ / 0.2));
  ball_raduis_ = qRound(kBasicBallRadius * (1 - difficulty_));
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
  AddBall();

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

void TestMiniGame::MousePressEvent(QMouseEvent* event) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(
      QBrush(QColor::fromRgb(200, 0, 0)));
  ClickableBall* ball_at =
      dynamic_cast<ClickableBall*>(graphics_view_->itemAt(event->pos()));
  if (ball_at != nullptr) {
    graphics_view_->scene()->removeItem(ball_at);
    delete ball_at;
    balls_count_--;
    if (balls_count_ == 0) {
      Win();
    } else {
      AddBall();
    }
  }
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

void TestMiniGame::AddBall() {
  graphics_view_->scene()->addItem(new ClickableBall(
      graphics_view_, ball_raduis_ * 2, ball_raduis_ * 2,
      QRandomGenerator::global()->bounded(graphics_view_->width()) -
          graphics_view_->width() / 2,
      QRandomGenerator::global()->bounded(graphics_view_->height()) -
          graphics_view_->height() / 2));
}

void TestMiniGame::Stop() {
  is_running_ = false;
  finish_timer_->stop();
  tick_timer_->stop();
  if (balls_count_ == 0) {
    Win();
  } else {
    Lose();
  }
}

void TestMiniGame::Win() {
  graphics_view_->scene()->setBackgroundBrush(Qt::NoBrush);
  emit Passed(0);
}

void TestMiniGame::Lose() {
  graphics_view_->scene()->setBackgroundBrush(Qt::NoBrush);
  emit Failed();
}
