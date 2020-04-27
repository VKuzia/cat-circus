#include "scorepage.h"

#include <QDebug>

#include "ui_scorepage.h"

ScorePage::ScorePage(QWidget* parent)
    : QWidget(parent),
      lives_scene_(new QGraphicsScene(this)),
      ui_(new Ui::ScorePage),
      expire_timer_(this) {
  ui_->setupUi(this);
  connect(&expire_timer_, &QTimer::timeout, this, [=] {
    expire_timer_.stop();
    life_movie_->stop();
    emit Expired();
  });
  ui_->ui_lives_view_->setRenderHint(QPainter::Antialiasing);
  ui_->ui_lives_view_->setScene(lives_scene_);

  connect(life_movie_, &QMovie::frameChanged, this, [this] {
    if (life_movie_->state() != QMovie::Running) {
      return;
    }
    for (int32_t i = kBasicLivesCount - 1; i >= kBasicLivesCount - lives_count_;
         i--) {
      lives_.at(i)->setPixmap(life_movie_->currentPixmap());
    }
  });

  connect(life_disappear_movie_, &QMovie::frameChanged, this, [this] {
    if (life_disappear_movie_->state() != QMovie::Running) {
      return;
    }
    lives_.at(kBasicLivesCount - lives_count_ - 1)
        ->setPixmap(life_disappear_movie_->currentPixmap());
  });
}

ScorePage::~ScorePage() {
  // Remember, lives_scene_ clears lives_ elements
  lives_.clear();
  lives_scene_->clear();
  delete lives_scene_;
  delete ui_;
  life_movie_->stop();
  life_disappear_movie_->stop();
  delete life_movie_;
  delete life_disappear_movie_;
}

void ScorePage::SetUp() {
  score_ = 0;
  ui_->ui_score_label_->setText(QString::number(score_));
  ui_->ui_label_->setText("Get ready!");
  ui_->ui_stacked_button_widget_->setCurrentWidget(ui_->ui_pause_button_page_);
  ui_->ui_retry_button_->setVisible(false);

  score_animation_.setPropertyName("score");
  score_animation_.setTargetObject(this);
  score_animation_.setDuration(kScoreAnimationTime);

  is_minigame_passed_ = false;

  life_height_ = qRound(ui_->ui_lives_view_->height() * kLiveScaleYFactor);
  life_width_ = qRound(ui_->ui_lives_view_->width() * kLiveScaleXFactor);
  life_movie_->setScaledSize(QSize(life_width_, life_height_));
  life_disappear_movie_->setScaledSize(QSize(life_width_, life_height_));
  life_disappear_movie_->setSpeed(kLifeDisappearSpeed);
  SetUpLives();
}

void ScorePage::Animate() {
  expire_timer_.setInterval(kExpireTime);
  expire_timer_.start();
  if (is_minigame_passed_) {
    score_animation_.start();
  }
  life_movie_->start();
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
  if (lives_count_ == 0) {
    ui_->ui_label_->setText("You lost...");
    expire_timer_.stop();
    ui_->ui_retry_button_->setVisible(true);
    ui_->ui_stacked_button_widget_->setCurrentWidget(
        ui_->ui_main_menu_button_page_);
  } else {
    ui_->ui_label_->setText("Failed :(");
  }
}

int32_t ScorePage::GetLivesCount() const { return lives_count_; }

void ScorePage::Pause() {
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = expire_timer_.remainingTime();
  expire_timer_.stop();
  expire_timer_.setInterval(remaining_time_);
  life_movie_->setPaused(true);
  life_disappear_movie_->setPaused(true);
  emit Paused();
}

void ScorePage::Resume() {
  expire_timer_.setInterval(qMax(expire_timer_.remainingTime(), kResumeTime));
  expire_timer_.start();
  life_movie_->setPaused(false);
  if (life_disappear_movie_->state() == QMovie::Running) {
    life_disappear_movie_->setPaused(false);
  }
}

void ScorePage::Retry() {
  life_movie_->stop();
  life_disappear_movie_->stop();
  emit Retried();
  SetUp();
  Animate();
}

void ScorePage::ReturnToMainMenu() { emit MainMenu(); }

void ScorePage::SetUpLives() {
  lives_count_ = kBasicLivesCount;
  if (lives_.empty()) {
    for (int32_t i = -lives_count_ / 2; i <= (lives_count_ - 1) / 2; i++) {
      QGraphicsPixmapItem* new_life = GetNewLife(i);
      ui_->ui_lives_view_->scene()->addItem(new_life);
      lives_.push_back(new_life);
    }
  } else {
    life_movie_->jumpToFrame(0);
    for (auto life : lives_) {
      life->setPixmap(life_movie_->currentPixmap());
    }
  }
}

QGraphicsPixmapItem* ScorePage::GetNewLife(int32_t index) const {
  QGraphicsPixmapItem* new_life = new QGraphicsPixmapItem();
  qreal x = index * (life_width_ * (kLifeIntervalXFactor + 1));
  qreal y = 0;
  new_life->setOffset(-life_width_ / 2, -life_height_ / 2);
  new_life->setPos(x, y);
  life_movie_->jumpToFrame(0);
  new_life->setPixmap(life_movie_->currentPixmap());
  return new_life;
}

void ScorePage::RemoveLife() {
  lives_count_--;
  life_disappear_movie_->start();
}

void ScorePage::SetScore(int32_t score) {
  score_ = score;
  ui_->ui_score_label_->setText(QString::number(score_));
}

int32_t ScorePage::GetScore() const { return score_; }
