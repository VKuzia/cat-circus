#include "jugglingminigame.h"

#include <QKeyEvent>
#include <limits>

JugglingMinigame::JugglingMinigame(GameView* game_view, qreal difficulty,
                                   qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void JugglingMinigame::Start() { AnimateTutorial(); }

void JugglingMinigame::SetUp() {
  background_->SetUp(game_view_, "juggling/arena.png");
  game_view_->scene()->addItem(background_);

  cat_ = new JugglingCat(game_view_, kCatWidth, kCatHeight, 0, kCatY);
  cat_->SetUp();
  // Need to set this here because ball_air_time_ is defined by SetParamateres
  cat_->GetLeftHand()->SetBallAirTime(ball_air_time_ / 1000.0);
  cat_->GetRightHand()->SetBallAirTime(ball_air_time_ / 1000.0);
  game_view_->scene()->addItem(cat_);

  ball_timer_.setInterval(ball_launch_period_);
  connect(&ball_timer_, &QTimer::timeout, this, &JugglingMinigame::LaunchBall);
  LaunchBall();
}

void JugglingMinigame::SetUpLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(std::numeric_limits<qreal>::max());
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void JugglingMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] { StartGame(); });
}

void JugglingMinigame::StartGame() {
  time_bar_->Launch(time_);
  time_bar_->setVisible(true);
  tutorial_label_->setVisible(false);
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &JugglingMinigame::Tick);

  is_running_ = true;

  tick_timer_.start();
  ball_timer_.start();
  QTimer::singleShot(time_, this, [this] {
    if (is_running_) {
      Stop(Status::kPass);
    }
  });
}

void JugglingMinigame::AnimateOutro() {}

void JugglingMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  for (auto ball : balls_) {
    ball->Update();
    if (ball->IsFallen()) {
      Stop(Status::kFail);
    }
  }
  cat_->Update();
}

void JugglingMinigame::SeUpParameters() {
  ball_launch_period_ = 500;
  int32_t difficulty_level = qFloor(difficulty_ / 0.1);
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

void JugglingMinigame::Win() {
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void JugglingMinigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}

void JugglingMinigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
  if (event->nativeVirtualKey() == game_view_->GetKey(GameView::Key::kLeft) &&
      !cat_->GetLeftHand()->IsThrowing()) {
    JugglingBall* ball;
    for (auto item : cat_->GetLeftHand()->collidingItems()) {
      ball = dynamic_cast<JugglingBall*>(item);
      if (ball != nullptr) {
        ball->SetCaught(true);
        cat_->GetLeftHand()->SetBall(ball);
      }
    }
    cat_->GetLeftHand()->Throw();
  } else if (event->nativeVirtualKey() ==
                 game_view_->GetKey(GameView::Key::kRight) &&
             !cat_->GetRightHand()->IsThrowing()) {
    JugglingBall* ball;
    for (auto item : cat_->GetRightHand()->collidingItems()) {
      ball = dynamic_cast<JugglingBall*>(item);
      if (ball != nullptr) {
        ball->SetCaught(true);
        cat_->GetRightHand()->SetBall(ball);
      }
    }
    cat_->GetRightHand()->Throw();
  }
}

void JugglingMinigame::LaunchBall() {
  if (balls_.size() >= balls_count_) {
    ball_timer_.stop();
    return;
  }
  JugglingBall* ball =
      new JugglingBall(game_view_, kBallRadius * 2, kBallRadius * 2,
                       (balls_.size() % 2 ? kBallStartX : -kBallStartX),
                       kBallStartY, kFloorHeight);
  QPointF target_pos = balls_.size() % 2 ? cat_->GetRightHand()->GetBasePos()
                                         : cat_->GetLeftHand()->GetBasePos();
  ball->SetVelocity(
      physics::Throw(ball->GetPos(), target_pos, kBallLaunchFlightTime));
  balls_.insert(ball);
  ball->SetUp();
  game_view_->scene()->addItem(ball);
}
