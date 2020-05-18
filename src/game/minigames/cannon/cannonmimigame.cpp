#include "cannonmimigame.h"

#include <QKeyEvent>

CannonMinigame::CannonMinigame(GameView* game_view, qreal difficulty,
                               qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void CannonMinigame::Start() { AnimateTutorial(); }

void CannonMinigame::SetUp() {
  background_->SetUp(game_view_, "cannon/circus.png");
  game_view_->scene()->addItem(background_);

  SetUpLabel(kTutorialText_);

  cat_ = new CannonCat(game_view_, kCatWidth, kCatHeight, kCatX, kCatY);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  cannon_ = new GameObject(game_view_, {kCannonWidth, kCannonHeight},
                           {KCannonX, kCannonY});
  cannon_->setPixmap(GameObject::LoadPixmap(
      "cannon/cannon.png", cannon_->boundingRect().size().toSize()));
  game_view_->scene()->addItem(cannon_);

  arrow_ =
      new GameObject(game_view_, {kCatWidth, kCatHeight}, {-kCatX, -kCatY});
  arrow_->setPixmap(GameObject::LoadPixmap(
      "cannon/arrow.png", arrow_->boundingRect().size().toSize()));
  game_view_->scene()->addItem(arrow_);

  speedometer_ = new GameObject(game_view_, {kCatWidth, kCatHeight},
                                {kSpeedometerX, kSpeedometerY});
  speedometer_->setPixmap(GameObject::LoadPixmap(
      "cannon/spedometer.png", speedometer_->boundingRect().size().toSize(),
      true));
  game_view_->scene()->addItem(speedometer_);

  for (int i = 0; i < sausage_count_; i++) {
    LaunchSausage();
  }

  for (int i = 0; i < number_to_win_; i++) {
    CannonStatus* status_elem =
        new CannonStatus(game_view_, kStatusHeight, kStatusWidth,
                         kStatusStartX + KStatusDeltaX * i, kStatusStartY);
    status_elem->SetUp();
    status_bar_.push_front(status_elem);
    game_view_->scene()->addItem(status_elem);
  }
}

void CannonMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, [this] { StartGame(); });
}

void CannonMinigame::StartGame() {
  time_bar_->Launch(time_);
  time_bar_->setVisible(true);
  tutorial_label_->setVisible(false);
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &CannonMinigame::Tick);

  is_running_ = true;

  tick_timer_.start();
  QTimer::singleShot(time_, this, [this] {
    if (is_running_ && (!params_choosen_angle_ || !params_choosen_power_)) {
      Stop(MinigameStatus::kFailed);
    }
  });
}

void CannonMinigame::Tick() {
  ChangeParameters();
  if (is_cat_flying_) {
    cat_->Update();
  } else if (params_choosen_angle_ && params_choosen_power_) {
    cat_->SetAngle(angle_);
    cat_->SetPower(power_);
    is_cat_flying_ = true;
  }
  if (cat_->GetY() >= kFloorHeight) {
    if (current_score_ >= number_to_win_) {
      Stop(MinigameStatus::kPassed);
    } else {
      Stop(MinigameStatus::kFailed);
    }
  }
  for (auto item : sausages_) {
    item->Update();
  }
}

void CannonMinigame::ChangeParameters() {
  if (!params_choosen_power_) {
    if (power_increases_) {
      power_ += kPowerDelta;
      arrow_->setRotation(arrow_->rotation() + M_PI * (power_ / kMaxPower));
      if (power_ >= kMaxPower) {
        power_increases_ = false;
      }
    } else {
      power_ -= kPowerDelta;
      arrow_->setRotation(arrow_->rotation() - M_PI * (power_ / kMaxPower));
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
}

void CannonMinigame::SetUpParameters() {
  time_ = 10000;
  sausage_a_param = QRandomGenerator().global()->bounded(50) / 100.0;
  sausage_b_param = QRandomGenerator().global()->bounded(100) / 100.0;
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

void CannonMinigame::Stop(MinigameStatus status) {
  is_running_ = false;
  tick_timer_.stop();
  switch (status) {
    case MinigameStatus::kPassed:
      score_ = 100;
      Win();
      break;
    case MinigameStatus::kFailed:
      Lose();
  }
}

void CannonMinigame::SausageWasCaught() {
  current_score_++;
  if (current_score_ <= number_to_win_) {
    status_bar_[current_score_ - 1]->SetOk();
  }
}

void CannonMinigame::KeyPressEvent(QKeyEvent* event) {
  if (!is_running_) {
    return;
  }
  if (event->key() == Qt::Key_A) {
    params_choosen_angle_ = true;
    if (params_choosen_power_) {
      time_bar_->setVisible(false);
    }
  } else if (event->key() == Qt::Key_D) {
    params_choosen_power_ = true;
    if (params_choosen_angle_) {
      time_bar_->setVisible(false);
    }
  } else if (event->key() == Qt::Key_Space) {
    params_choosen_angle_ = true;
    params_choosen_power_ = true;
    time_bar_->setVisible(false);
  }
}

void CannonMinigame::LaunchSausage() {
  if (sausages_.size() >= sausage_count_) {
    return;
  }

  qreal sausage_x = QRandomGenerator().global()->bounded(kSausageXBoders.x(),
                                                         kSausageXBoders.y()) +
                    QRandomGenerator().global()->bounded(100) / 100.0;

  CannonSausage* sausage =
      new CannonSausage(game_view_, KSausageRadius, KSausageRadius, sausage_x,
                        sausage_a_param * sausage_x * sausage_x +
                            sausage_b_param * sausage_x - 3);
  connect(sausage, &CannonSausage::CaughtSausage, this,
          &CannonMinigame::SausageWasCaught);
  if (sausages_.size() % 2 == 0) {
    sausage->SetMovingDown(false);
  }
  sausages_.insert(sausage);
  sausage->SetUp();
  game_view_->scene()->addItem(sausage);
}
