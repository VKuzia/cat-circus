#include "cannonmimigame.h"

#include <QKeyEvent>

Cannonmimigame::Cannonmimigame(GameView* game_view, qreal difficulty,
                               qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

Cannonmimigame::~Cannonmimigame() {
  delete cat_;
  delete cannon_;
}

void Cannonmimigame::Start() { AnimateTutorial(); }

void Cannonmimigame::SetUp() {
  background_->SetUp(game_view_, "cannon/circus.png");
  game_view_->scene()->addItem(background_);

  // Create cannon
  cannon_ = new Cannon(game_view_, kCatWidth, kCatHeight, -6, kCatY);
  cannon_->SetUp();
  game_view_->scene()->addItem(cannon_);
  // Create cat
  cat_ = new Cannoncat(game_view_, kCatWidth, kCatHeight, -6, kCatY);
  cat_->SetUp();
  // Need to set this here because ball_air_time_ is defined by SetParamateres
  game_view_->scene()->addItem(cat_);
  // Create cannon
  cannon_ =
      new Cannon(game_view_, 2.5 * kCatWidth, 1.5 * kCatHeight, -6, kCatY);
  cannon_->SetUp();
  game_view_->scene()->addItem(cannon_);

  arrow_ = new Arrow(game_view_, kCatWidth, kCatHeight, 6, -kCatY);
  arrow_->SetUp();
  // Need to set this here because ball_air_time_ is defined by SetParamateres
  game_view_->scene()->addItem(arrow_);

  speedometer = new Speedometer(game_view_, kCatWidth, kCatHeight, 7, -kCatY);
  speedometer->SetUp();
  // Need to set this here because ball_air_time_ is defined by SetParamateres
  game_view_->scene()->addItem(speedometer);

  SetUpLabel();
  time_bar_->setVisible(false);
  ball_timer_.setInterval(sausage_launch_period_);
  connect(&ball_timer_, &QTimer::timeout, this, &Cannonmimigame::LaunchSausage);
  LaunchSausage();

  for (int i = 0; i < number_to_win_; i++) {
    No* no = new No(game_view_, 1, 1, -7 + 1.5 * i, -kCatY - 1.5);
    no->SetUp();
    not_caught.insert(no);
    game_view_->scene()->addItem(no);
  }
}

void Cannonmimigame::SetUpLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void Cannonmimigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] {
    tutorial_label_->setVisible(false);
    StartGame();
  });
}

void Cannonmimigame::StartGame() {
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &Cannonmimigame::Tick);

  is_running_ = true;

  tick_timer_.start();
  ball_timer_.start();
}

void Cannonmimigame::AnimateOutro() {}

void Cannonmimigame::Tick() {
  if (!is_running_) {
    return;
  }
  if (!params_choosen_power) {
    if (power_increases) {
      power += 0.001;
      arrow_->setRotation(arrow_->rotation() + M_PI * (power / 0.12));
      if (power >= 0.12) {
        power_increases = false;
      }
    } else {
      power -= 0.001;
      arrow_->setRotation(arrow_->rotation() - M_PI * (power / 0.12));
      if (power <= 0) {
        power_increases = true;
      }
    }
  }
  if (!params_choosen_angle) {
    if (angle_increases) {
      angle += M_PI / 200;
      cat_->setRotation(cat_->rotation() - angle);
      cannon_->setRotation(cat_->rotation() - angle);
      if (angle > M_PI / 2) {
        angle_increases = false;
      }
    } else {
      angle -= M_PI / 200;
      cat_->setRotation(cat_->rotation() + angle);
      cannon_->setRotation(cat_->rotation() + angle);
      if (angle <= 0) {
        angle_increases = true;
      }
    }
  }

  if (cat_flight) {
    cat_->Update();
    if (cat_->was_caught_last_tick && caught.size() < number_to_win_) {
      delete *(not_caught.begin() + caught.size());
      Yes* yes =
          new Yes(game_view_, 1, 1, -7 + 1.5 * caught.size(), -kCatY - 1.5);
      yes->SetUp();
      game_view_->scene()->addItem(yes);
      caught.insert(yes);
    }
  } else if (params_choosen_angle && params_choosen_power) {
    cat_->SetAngle(angle);
    cat_->SetPower(power);
    cat_flight = true;
  }
  if (cat_->GetY() >= kFloorHeight) {
    cat_->SetFallen(true);
    if (cat_->GetCaught() >= number_to_win_) {
      difficulty_++;
      Stop(Status::kPass);
    } else {
      Stop(Status::kFail);
    }
  }
}

void Cannonmimigame::SetUpParameters() {
  sausage_launch_period_ = 100;
  sausage_a_param = generator_.generateDouble();
  sausage_b_param = generator_.generateDouble();
  int32_t difficulty_level = difficulty_ + 1;
  switch (difficulty_level) {
    case 1:
      sausage_count_ = 7;
      number_to_win_ = 2;
      break;
    case 2:
      sausage_count_ = 7;
      number_to_win_ = 3;
      break;
    case 3:
      sausage_count_ = 6;
      number_to_win_ = 3;
      break;
    case 4:
      sausage_count_ = 6;
      number_to_win_ = 4;
      break;
    case 5:
      sausage_count_ = 5;
      number_to_win_ = 4;
      break;
    case 6:
      sausage_count_ = 5;
      number_to_win_ = 4;
      break;
    case 7:
      sausage_count_ = 4;
      number_to_win_ = 4;
      break;
    case 8:
      sausage_count_ = 4;
      number_to_win_ = 4;
      break;
    case 9:
      sausage_count_ = 4;
      number_to_win_ = 4;
      break;
    default:
      sausage_count_ = 3;
      number_to_win_ = 3;
      break;
  }
}

void Cannonmimigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  ball_timer_.stop();
  time_bar_->setVisible(false);
  if (status == Status::kPass) {
    difficulty_++;
    score_ = 100;
    Win();
  }
  if (status == Status::kFail) {
    Lose();
  }
}

void Cannonmimigame::Win() {
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void Cannonmimigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}

void Cannonmimigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
  if (event->key() == Qt::Key_A) {
    params_choosen_angle = true;
  } else if (event->key() == Qt::Key_D) {
    params_choosen_power = true;
  } else if (event->key() == Qt::Key_Space) {
    params_choosen_angle = true;
    params_choosen_power = true;
  }
}

void Cannonmimigame::LaunchSausage() {
  if (balls_.size() >= sausage_count_) {
    return;
  }

  qreal SausageX = generator_.bounded(-6, 6) + generator_.generateDouble();

  Sausage* ball =
      new Sausage(game_view_, KSausageRadius * 2, KSausageRadius * 2, SausageX,
                  sausage_a_param * SausageX * SausageX / 2 +
                      sausage_b_param * SausageX - 3,
                  kFloorHeight);

  balls_.insert(ball);
  ball->SetUp();
  game_view_->scene()->addItem(ball);
}
