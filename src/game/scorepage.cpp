#include "scorepage.h"

#include <QGraphicsEllipseItem>

#include "ui_scorepage.h"

ScorePage::ScorePage(QWidget* parent)
    : QWidget(parent),
      lives_scene_(new QGraphicsScene(this)),
      ui_(new Ui::ScorePage),
      expire_timer_(this) {
  ui_->setupUi(this);
  connect(&expire_timer_, &QTimer::timeout, this, [=] {
    expire_timer_.stop();
    emit Expired();
  });
  ui_->ui_lives_view_->setRenderHint(QPainter::Antialiasing);
  ui_->ui_lives_view_->setScene(lives_scene_);
}

ScorePage::~ScorePage() {
  // Remember, lives_scene_ clears lives_ elements
  lives_.clear();
  lives_scene_->clear();
  delete lives_scene_;
  delete ui_;
  delete life_movie_;
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
  // To prevent "starting with no end value" while first Animate() called
  score_animation_.setStartValue(0);
  score_animation_.setEndValue(0);

  life_movie_->setScaledSize(QSize(100, 100));
  SetUpLives();
}

void ScorePage::Animate() {
  expire_timer_.setInterval(kExpireTime);
  expire_timer_.start();
  score_animation_.start();
}

void ScorePage::MiniGamePassed(int32_t score) {
  ui_->ui_label_->setText("Passed!");
  score_animation_.setStartValue(score_);
  score_animation_.setEndValue(score_ + score);
}

void ScorePage::MiniGameFailed() {
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
  emit Paused();
}

void ScorePage::Resume() {
  expire_timer_.setInterval(qMax(expire_timer_.remainingTime(), kResumeTime));
  expire_timer_.start();
}

void ScorePage::Retry() {
  emit Retried();
  SetUp();
  Animate();
}

void ScorePage::ReturnToMainMenu() { emit MainMenu(); }

void ScorePage::SetUpLives() {
  ui_->ui_lives_view_->scene()->clear();
  lives_.clear();
  lives_count_ = kBasicLivesCount;
  for (int32_t i = -lives_count_ / 2; i <= (lives_count_ - 1) / 2; i++) {
    QGraphicsPixmapItem* new_life = GetNewLife(i);
    ui_->ui_lives_view_->scene()->addItem(new_life);
    lives_.push_back(new_life);
  }
}

QGraphicsPixmapItem* ScorePage::GetNewLife(int32_t index) const {
  // Will be further replaced with animated sprites
  QGraphicsPixmapItem* new_life = new QGraphicsPixmapItem();
  qreal diameter = ui_->ui_lives_view_->height() * kLiveHeightFactor;
  qreal x = index * (kLifeInterval + diameter);
  qreal y = 0;
  new_life->setOffset(-diameter / 2, -diameter / 2);
  new_life->setPos(x, y);
  life_movie_->jumpToFrame(0);
  new_life->setPixmap(life_movie_->currentPixmap());
  return new_life;
}

void ScorePage::RemoveLife() {
  lives_count_--;
  life_movie_->jumpToFrame(0);
  QGraphicsPixmapItem* life = lives_.at(kBasicLivesCount - lives_count_ - 1);
  connect(life_movie_, &QMovie::frameChanged, this,
          [this, life] { life->setPixmap(life_movie_->currentPixmap()); });
  life_movie_->start();
}

void ScorePage::SetScore(int32_t score) {
  score_ = score;
  ui_->ui_score_label_->setText(QString::number(score_));
}

int32_t ScorePage::GetScore() const { return score_; }
