#include "scorepage.h"

#include <QDir>

#include "ui_scorepage.h"

ScorePage::ScorePage(QWidget* parent)
    : QWidget(parent),
      lives_scene_(new QGraphicsScene(this)),
      ui_(new Ui::ScorePage),
      life_movie_(QDir::currentPath() + "/data/images/score/life.gif"),
      life_disappear_movie_(QDir::currentPath() +
                            "/data/images/score/life_disappear.gif"),
      expire_timer_(this) {
  ui_->setupUi(this);
  connect(&expire_timer_, &QTimer::timeout, this, [this] {
    expire_timer_.stop();
    life_movie_.stop();
    emit Expired();
  });
  ui_->ui_lives_view_->setRenderHint(QPainter::Antialiasing);
  ui_->ui_lives_view_->setScene(lives_scene_);
  SetUpAnimations();
}

ScorePage::~ScorePage() {
  // Remember, lives_scene_ clears lives_ elements
  lives_.clear();
  lives_scene_->clear();
  delete lives_scene_;
  delete ui_;
}

void ScorePage::SetUp() {
  score_ = 0;
  is_minigame_passed_ = false;

  ui_->ui_score_label_->setText(QString::number(score_));
  ui_->ui_label_->setText("Get ready!");
  ui_->ui_stacked_button_widget_->setCurrentWidget(ui_->ui_pause_button_page_);
  ui_->ui_retry_button_->setVisible(false);

  life_size_.setWidth(qRound(ui_->ui_lives_view_->width() * kLiveScaleXFactor));
  life_size_.setHeight(
      qRound(ui_->ui_lives_view_->height() * kLiveScaleYFactor));
  life_movie_.setScaledSize(life_size_);
  life_disappear_movie_.setScaledSize(life_size_);
  life_disappear_movie_.setSpeed(kLifeDisappearSpeed);
  SetUpLives();
}

void ScorePage::Animate() {
  expire_timer_.setInterval(kExpireTime);
  expire_timer_.start();
  if (is_minigame_passed_) {
    score_animation_.start();
  }
  life_movie_.start();
}

void ScorePage::MiniGamePassed(int32_t score) {
  is_minigame_passed_ = true;
  ui_->ui_label_->setText("Passed!");
  score_animation_.setStartValue(score_);
  score_animation_.setEndValue(score_ + score);
}

void ScorePage::MiniGameFailed() {
  is_minigame_passed_ = false;
  RemoveLife();
  if (remaining_lives_ == 0) {
    ui_->ui_label_->setText("You lost...");
    expire_timer_.stop();
    ui_->ui_retry_button_->setVisible(true);
    ui_->ui_stacked_button_widget_->setCurrentWidget(
        ui_->ui_main_menu_button_page_);
  } else {
    ui_->ui_label_->setText("Failed :(");
  }
}

int32_t ScorePage::GetLivesCount() const { return remaining_lives_; }

void ScorePage::Pause() {
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = expire_timer_.remainingTime();
  expire_timer_.stop();
  expire_timer_.setInterval(remaining_time_);

  life_movie_.setPaused(true);
  life_disappear_movie_.setPaused(true);
  emit Paused();
}

void ScorePage::Resume() {
  expire_timer_.setInterval(qMax(expire_timer_.remainingTime(), kResumeTime));
  expire_timer_.start();
  life_movie_.setPaused(false);
  // To prevent double disappearing animation
  if (is_life_disappearing_) {
    life_disappear_movie_.setPaused(false);
  }
}

void ScorePage::Retry() {
  life_movie_.stop();
  life_disappear_movie_.stop();
  emit Retried();
  SetUp();
  Animate();
}

void ScorePage::ReturnToMainMenu() { emit MainMenu(); }

void ScorePage::SetUpLives() {
  remaining_lives_ = kLivesCount;
  // If just started -- create lives, update them with start frame otherwise
  if (lives_.empty()) {
    for (int32_t i = -remaining_lives_ / 2; i <= (remaining_lives_ - 1) / 2;
         i++) {
      QGraphicsPixmapItem* new_life = GetNewLife(i);
      ui_->ui_lives_view_->scene()->addItem(new_life);
      lives_.push_back(new_life);
    }
  } else {
    life_movie_.jumpToFrame(0);
    for (auto life : lives_) {
      life->setPixmap(life_movie_.currentPixmap());
    }
  }
}

QGraphicsPixmapItem* ScorePage::GetNewLife(int32_t index) const {
  QGraphicsPixmapItem* new_life = new QGraphicsPixmapItem();
  qreal x = index * (life_size_.width() * (kLifeIntervalXFactor + 1));
  qreal y = 0;
  new_life->setOffset(-life_size_.width() / 2, -life_size_.height() / 2);
  new_life->setPos(x, y);
  return new_life;
}

void ScorePage::RemoveLife() {
  remaining_lives_--;
  is_life_disappearing_ = true;
  life_disappear_movie_.start();
}

void ScorePage::SetUpAnimations() {
  connect(&life_movie_, &QMovie::frameChanged, this, [this] {
    if (life_movie_.state() != QMovie::Running) {
      return;
    }
    for (int32_t i = kLivesCount - 1; i >= kLivesCount - remaining_lives_;
         i--) {
      lives_.at(i)->setPixmap(life_movie_.currentPixmap());
    }
  });

  connect(&life_disappear_movie_, &QMovie::frameChanged, this, [this] {
    if (life_disappear_movie_.state() != QMovie::Running ||
        remaining_lives_ >= kLivesCount || remaining_lives_ < 0) {
      return;
    }
    lives_.at(kLivesCount - remaining_lives_ - 1)
        ->setPixmap(life_disappear_movie_.currentPixmap());
  });

  connect(&life_disappear_movie_, &QMovie::finished, this,
          [this] { is_life_disappearing_ = false; });

  score_animation_.setPropertyName("score");
  score_animation_.setTargetObject(this);
  score_animation_.setDuration(kScoreAnimationTime);
}

void ScorePage::SetScore(int32_t score) {
  score_ = score;
  ui_->ui_score_label_->setText(QString::number(score_));
}

int32_t ScorePage::GetScore() const { return score_; }
