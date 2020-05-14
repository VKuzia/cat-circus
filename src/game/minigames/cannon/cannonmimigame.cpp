#include "cannonmimigame.h"

#include <QKeyEvent>

CannonMinigame::CannonMinigame(GameView* game_view, qreal difficulty,
                               qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void CannonMinigame::Start() { AnimateTutorial(); }

void CannonMinigame::SetUp() {
  background_->SetUp(game_view_, "cannon/circus.png");
  game_view_->scene()->addItem(background_);

  cat_ = new CannonCat(game_view_, kCatWidth, kCatHeight, kCatX, kCatY);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  cannon_ =
      new Cannon(game_view_, kCannonWidth, kCannonHeight, KCannonX, kCannonY);
  cannon_->SetUp();
  game_view_->scene()->addItem(cannon_);

  arrow_ = new Arrow(game_view_, kCatWidth, kCatHeight, -kCatX, -kCatY);
  arrow_->SetUp();
  game_view_->scene()->addItem(arrow_);

  speedometer_ = new Speedometer(game_view_, kCatWidth, kCatHeight, 7, -kCatY);
  speedometer_->SetUp();
  game_view_->scene()->addItem(speedometer_);

  SetUpLabel();

  for (int i = 0; i < sausage_count_; i++) {
    LaunchSausage();
  }

  for (int i = 0; i < number_to_win_; i++) {
    No* no = new No(game_view_, kStatusHeight, kStatusWidth,
                    kStatusStartX + KStatusDeltaX * i, kStatusStartY);
    no->SetUp();
    not_caught_.insert(no);
    game_view_->scene()->addItem(no);
  }
  for (int i = 0; i < number_to_win_; i++) {
    Yes* yes = new Yes(game_view_, kStatusHeight, kStatusWidth,
                       kStatusStartX + KStatusDeltaX * i, kStatusStartY);
    yes->SetUp();
    caught_.insert(yes);
    yes->setVisible(false);
    game_view_->scene()->addItem(yes);
  }
}

void CannonMinigame::SetUpLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void CannonMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] {
    tutorial_label_->setVisible(false);
    StartGame();
  });
}

void CannonMinigame::StartGame() {
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &CannonMinigame::Tick);

  is_running_ = true;

  tick_timer_.start();
}

void CannonMinigame::AnimateOutro() {}

void CannonMinigame::Tick() {
  if (!is_running_) {
    return;
  }
  if (!params_choosen_power_) {
    if (power_increases_) {
      power_ += kPowerDelta;
      arrow_->setRotation(arrow_->rotation() + M_PI * (power_ / 0.12));
      if (power_ >= 0.12) {
        power_increases_ = false;
      }
    } else {
      power_ -= 0.001;
      arrow_->setRotation(arrow_->rotation() - M_PI * (power_ / 0.12));
      if (power_ <= 0) {
        power_increases_ = true;
      }
    }
  }
  if (!params_choosen_angle_) {
    if (angle_increases_) {
      angle_ += kAngleDelta;
      cat_->setRotation(cat_->rotation() - angle_);
      cannon_->setRotation(cat_->rotation() - angle_);
      if (angle_ > M_PI / 2) {
        angle_increases_ = false;
      }
    } else {
      angle_ -= kAngleDelta;
      cat_->setRotation(cat_->rotation() + angle_);
      cannon_->setRotation(cat_->rotation() + angle_);
      if (angle_ <= 0) {
        angle_increases_ = true;
      }
    }
  }

  if (is_cat_flying_) {
    cat_->Update();
    if (cat_->GetLastTickStatus() && cat_->GetCaught() <= number_to_win_) {
      (*(not_caught_.begin() + cat_->GetCaught() - 1))->setVisible(false);
      (*(caught_.begin() + cat_->GetCaught() - 1))->setVisible(true);
    }
  } else if (params_choosen_angle_ && params_choosen_power_) {
    cat_->SetAngle(angle_);
    cat_->SetPower(power_);
    is_cat_flying_ = true;
  }
  if (cat_->GetY() >= kFloorHeight) {
    cat_->SetFallen(true);
    if (cat_->GetCaught() >= number_to_win_) {
      Stop(Status::kPass);
    } else {
      Stop(Status::kFail);
    }
  }
  for (auto item : sausages_) {
    item->Update();
  }
}

void CannonMinigame::SetUpParameters() {
  // Parameters of quadratic equation - (ax^2 + bx + c) generation
  sausage_a_param = QRandomGenerator().global()->bounded(50) * 1.0 / 100;
  sausage_b_param = QRandomGenerator().global()->bounded(100) * 1.0 / 100;
  int32_t difficulty_level = qFloor(difficulty_ / 0.1);
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

void CannonMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  time_bar_->setVisible(false);
  if (status == Status::kPass) {
    score_ = 100;
    Win();
  }
  if (status == Status::kFail) {
    Lose();
  }
}

void CannonMinigame::Win() {
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void CannonMinigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}

void CannonMinigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
  if (event->key() == Qt::Key_A) {
    params_choosen_angle_ = true;
  } else if (event->key() == Qt::Key_D) {
    params_choosen_power_ = true;
  } else if (event->key() == Qt::Key_Space) {
    params_choosen_angle_ = true;
    params_choosen_power_ = true;
  }
}

void CannonMinigame::LaunchSausage() {
  if (sausages_.size() >= sausage_count_) {
    return;
  }

  qreal sausage_x = QRandomGenerator().global()->bounded(kSausageXBoders.x(),
                                                         kSausageXBoders.y()) +
                    QRandomGenerator().global()->bounded(100) * 1.0 / 100;

  CannonSausage* sausage =
      new CannonSausage(game_view_, KSausageRadius, KSausageRadius, sausage_x,
                        sausage_a_param * sausage_x * sausage_x +
                            sausage_b_param * sausage_x - 3);
  if (sausages_.size() % 2 == 0) {
    sausage->move_down = false;
  }
  sausages_.insert(sausage);
  sausage->SetUp();
  game_view_->scene()->addItem(sausage);
}
