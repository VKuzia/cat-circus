#include "testminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator64>

TestMinigame::TestMinigame(GameView* graphics_view, qreal difficulty)
    : Minigame(graphics_view, difficulty) {
  game_view_->SetPixelsInMeter(kPixelsInMeter);
}

void TestMinigame::SetUp() {
  game_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
  AddBall();
}

void TestMinigame::SetUpLabel() {
  // Random coefs just for testing the basic game loop
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::white);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(std::numeric_limits<qreal>::max());
}

void TestMinigame::SeUpParameters() {
  // Random coefs just for testing the basic game loop
  time_ = qRound(kBasicDuration / (difficulty_ * 1.5 + 1.0));
  balls_count_ = kBasicBallNumber + qRound(difficulty_ / 0.2);
  ball_radius_ = qRound(kBasicBallRadius * (1 - difficulty_));
}
void TestMinigame::Start() { AnimateTutorial(); }

void TestMinigame::AnimateTutorial() {
  SetUpLabel();
  QTimer::singleShot(kTutorialDuration, this, [this] { StartGame(); });
}

void TestMinigame::StartGame() {
  tutorial_label_->setVisible(false);
  time_bar_->Launch(time_);
  time_bar_->setVisible(true);
  timer_.setInterval(time_);
  connect(&timer_, &QTimer::timeout, this, [this] { Stop(Status::kFail); });

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TestMinigame::Tick);

  is_running_ = true;

  timer_.start();
  tick_timer_.start();
}

void TestMinigame::AnimateOutro() {}

void TestMinigame::Tick() {}

void TestMinigame::AddBall() {
  QPointF center = GetRandomBallCenter();
  ClickableBall* ball =
      new ClickableBall(game_view_, ball_radius_ * 2, ball_radius_ * 2, center);
  ball->SetUp();
  connect(ball, &ClickableBall::Clicked, this, &TestMinigame::DeleteBall);
  current_ball_ = ball;
  game_view_->scene()->addItem(ball);
}

void TestMinigame::DeleteBall() {
  if (current_ball_ == nullptr || !is_running_) {
    return;
  }
  game_view_->scene()->removeItem(current_ball_);
  delete current_ball_;
  current_ball_ = nullptr;
  balls_count_--;
  if (balls_count_ == 0) {
    time_left_ = timer_.remainingTime();
    Stop(Status::kPass);
  } else {
    AddBall();
  }
}

QPointF TestMinigame::GetRandomBallCenter() const {
  // Scene's (0,0) point is in its centre.
  // That's why we subtract a half of width(height)
  // Then scale for center being inside but the edges
  qreal x = (QRandomGenerator::global()->bounded(game_view_->width()) -
             game_view_->width() / 2) *
            kCenterRegionFactor;
  qreal y = (QRandomGenerator::global()->bounded(game_view_->height()) -
             game_view_->height() / 2) *
            kCenterRegionFactor;
  x /= game_view_->GetPixelsInMeter();
  y /= game_view_->GetPixelsInMeter();
  return QPointF(x, y);
}

void TestMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  timer_.stop();
  time_bar_->setVisible(false);
  if (status == Status::kPass) {
    Win();
  } else {
    Lose();
  }
}

void TestMinigame::Win() {
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    score_ = 100 + time_left_ * 10 / timer_.interval();
    emit Passed(score_);
  });
  timer_.start();
}

void TestMinigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
  timer_.start();
}

void TestMinigame::MousePressEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  game_view_->scene()->setBackgroundBrush(kMousePressedBackgroundBrush);
}

void TestMinigame::MouseReleaseEvent(QMouseEvent*) {
  if (!is_running_) {
    return;
  }
  game_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
}

void TestMinigame::KeyPressEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  game_view_->scene()->setBackgroundBrush(kKeyPressedBackgroundBrush);
}

void TestMinigame::KeyReleaseEvent(QKeyEvent*) {
  if (!is_running_) {
    return;
  }
  game_view_->scene()->setBackgroundBrush(kSimpleBackgroundBrush);
}
