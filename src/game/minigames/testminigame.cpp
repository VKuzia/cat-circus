#include "testminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator64>

TestMinigame::TestMinigame(QGraphicsView* graphics_view, qreal difficulty)
    : Minigame(graphics_view, difficulty) {}

void TestMinigame::SetUp() {
  // Random coefs just for testing the basic game loop
  time_ = qRound(kBasicDuration / (difficulty_ * 1.5 + 1.0));
  balls_count_ = kBasicBallNumber + qRound(difficulty_ / 0.2);
  ball_radius_ = qRound(kBasicBallRadius * (1 - difficulty_));
  time_bar_->setVisible(false);

  graphics_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
  AddBall();
}

void TestMinigame::Start() { AnimateTutorial(); }

void TestMinigame::AnimateTutorial() {
  // Random coefs just for testing the basic game loop
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::white);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);

  QTimer::singleShot(kTutorialDuration, this, [this] { StartGame(); });
}

void TestMinigame::StartGame() {
  tutorial_label_->setVisible(false);
  time_bar_->setVisible(true);
  timer_.setInterval(time_);
  connect(&timer_, &QTimer::timeout, this, &TestMinigame::Stop);

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TestMinigame::Tick);

  is_running_ = true;

  timer_.start();
  tick_timer_.start();
}

void TestMinigame::AnimateOutro() {}

void TestMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  time_bar_->SetProgress(1.0 * timer_.remainingTime() / time_);
  time_bar_->update();
}

void TestMinigame::AddBall() {
  QPointF center = GetRandomBallCenter();
  ClickableBall* ball = new ClickableBall(graphics_view_, ball_radius_ * 2,
                                          ball_radius_ * 2, center);
  connect(ball, &ClickableBall::Clicked, this, &TestMinigame::DeleteBall);
  current_ball_ = ball;
  graphics_view_->scene()->addItem(ball);
}

void TestMinigame::DeleteBall() {
  if (current_ball_ == nullptr || !is_running_) {
    return;
  }
  graphics_view_->scene()->removeItem(current_ball_);
  delete current_ball_;
  current_ball_ = nullptr;
  balls_count_--;
  if (balls_count_ == 0) {
    time_left_ = timer_.remainingTime();
    Stop();
  } else {
    AddBall();
  }
}

QPointF TestMinigame::GetRandomBallCenter() const {
  // Scene's (0,0) point is in its centre.
  // That's why we subtract a half of width(height)
  // Then scale for center being inside but the edges
  qreal x = (QRandomGenerator::global()->bounded(graphics_view_->width()) -
             graphics_view_->width() / 2) *
            kCenterRegionFactor;
  qreal y = (QRandomGenerator::global()->bounded(graphics_view_->height()) -
             graphics_view_->height() / 2) *
            kCenterRegionFactor;
  return QPointF(x, y);
}

void TestMinigame::Stop() {
  is_running_ = false;
  tick_timer_.stop();
  timer_.stop();
  time_bar_->setVisible(false);
  if (balls_count_ == 0) {
    Win();
  } else {
    Lose();
  }
}

void TestMinigame::Win() {
  graphics_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    score_ = 100 + time_left_ * 10 / timer_.interval();
    emit Passed(score_);
  });
  timer_.start();
}

void TestMinigame::Lose() {
  graphics_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
  timer_.start();
}

void TestMinigame::MousePressEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(kMousePressedBackgroundBrush);
}

void TestMinigame::MouseReleaseEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
}

void TestMinigame::MouseMoveEvent(QMouseEvent*) {}

void TestMinigame::KeyPressEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(kKeyPressedBackgroundBrush);
}

void TestMinigame::KeyReleaseEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  graphics_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
}
