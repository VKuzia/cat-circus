#include "jugglingminigame.h"

#include <QKeyEvent>

JugglingMinigame::JugglingMinigame(GameView* graphics_view, qreal difficulty)
    : Minigame(graphics_view, difficulty) {
  graphics_view_->SetPixelsInMeter(kBasicPixelsInMeter);
}

JugglingMinigame::~JugglingMinigame() { delete cat_; }

void JugglingMinigame::Start() { AnimateTutorial(); }

void JugglingMinigame::SetUp() {
  SetParameters();
  time_bar_->setVisible(false);
  cat_ = new JugglingCat(graphics_view_, kCatWidth, kCatHeight, 0, kCatY);
  cat_->SetUp();
  cat_->GetLeftHand()->SetBallAirTime(ball_air_time_ / 1000.0);
  cat_->GetRightHand()->SetBallAirTime(ball_air_time_ / 1000.0);
  graphics_view_->scene()->addItem(cat_);

  SetLabel();
  time_bar_->setVisible(false);
  ball_timer_.setInterval(ball_launch_period_);
  connect(&ball_timer_, &QTimer::timeout, this, &JugglingMinigame::LaunchBall);
  LaunchBall();
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
  time_bar_->Launch(time_);
  connect(&timer_, &QTimer::timeout, [this] { Stop(Status::kPass); });

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &JugglingMinigame::Tick);

  is_running_ = true;

  tick_timer_.start();
  ball_timer_.start();
  QTimer::singleShot(time_, this, [this] { Stop(Status::kPass); });
}

void JugglingMinigame::AnimateOutro() {}

void JugglingMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  for (auto ball : balls_) {
    ball->Update();
    if (ball->GetY() >= kFloorHeight - kBallRadius) {
      ball->SetFallen(true);
      Stop(Status::kFail);
    }
  }
  cat_->GetLeftHand()->Update();
  cat_->GetRightHand()->Update();
}

void JugglingMinigame::SetParameters() {
  ball_launch_period_ = 500;
  int32_t difficulty_level = qFloor(difficulty_ / 0.1);
  difficulty_level = 7;
  switch (difficulty_level) {
    case 1:
      balls_count_ = 2;
      time_ = 4000;
      ball_air_time_ = 1300;
      break;
    case 2:
      balls_count_ = 3;
      time_ = 4000;
      ball_air_time_ = 1300;
      break;
    case 3:
      balls_count_ = 3;
      time_ = 6000;
      ball_air_time_ = 1300;
      break;
    case 4:
      balls_count_ = 4;
      time_ = 5000;
      ball_air_time_ = 1500;
      ball_launch_period_ = 400;
      break;
    case 5:
      balls_count_ = 4;
      time_ = 7000;
      ball_air_time_ = 1500;
      ball_launch_period_ = 400;
      break;
    case 6:
      balls_count_ = 4;
      time_ = 8000;
      ball_air_time_ = 1400;
      ball_launch_period_ = 350;
      break;
    case 7:
      balls_count_ = 5;
      time_ = 7000;
      ball_air_time_ = 1550;
      ball_launch_period_ = 340;
      break;
    case 8:
      balls_count_ = 5;
      time_ = 8000;
      ball_air_time_ = 1400;
      ball_launch_period_ = 300;
      break;
    case 9:
      balls_count_ = 5;
      time_ = 9000;
      ball_air_time_ = 1400;
      ball_launch_period_ = 300;
      break;
    default:
      balls_count_ = 5;
      time_ = 10000;
      ball_air_time_ = 1350;
      ball_launch_period_ = 300;
      break;
  }
}

void JugglingMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  ball_timer_.stop();
  time_bar_->setVisible(false);
  if (status == Status::kPass) {
    score_ = 100;
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

void JugglingMinigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
  if (event->key() == Qt::Key_A) {
    JugglingBall* ball;
    for (auto item : cat_->GetLeftHand()->collidingItems()) {
      ball = dynamic_cast<JugglingBall*>(item);
      if (ball != nullptr) {
        ball->SetCaught(true);
        cat_->GetLeftHand()->AddBall(ball);
      }
    }
    cat_->GetLeftHand()->Throw();
  } else if (event->key() == Qt::Key_D) {
    JugglingBall* ball;
    for (auto item : cat_->GetRightHand()->collidingItems()) {
      ball = dynamic_cast<JugglingBall*>(item);
      if (ball != nullptr) {
        ball->SetCaught(true);
        cat_->GetRightHand()->AddBall(ball);
      }
    }
    cat_->GetRightHand()->Throw();
  }
}

void JugglingMinigame::LaunchBall() {
  if (balls_.size() >= balls_count_) {
    return;
  }
  JugglingBall* ball =
      new JugglingBall(graphics_view_, kBallRadius * 2, kBallRadius * 2,
                       (balls_.size() % 2 ? kBallStartX : -kBallStartX),
                       kBallStartY, kFloorHeight);
  ball->SetVelocity(
      physics::Throw(ball->GetPos(),
                     (balls_.size() % 2 ? cat_->GetRightHand()->GetBasePos()
                                        : cat_->GetLeftHand()->GetBasePos()),
                     kBallLaunchFlightTime));
  balls_.insert(ball);
  ball->SetUp();
  graphics_view_->scene()->addItem(ball);
}
