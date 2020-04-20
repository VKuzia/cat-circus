#include "pointspage.h"

#include <QGraphicsEllipseItem>

#include "ui_pointspage.h"

PointsPage::PointsPage(QWidget* parent)
    : QWidget(parent),
      lives_scene_(new QGraphicsScene(this)),
      ui_(new Ui::PointsPage),
      expire_timer_(this) {
  ui_->setupUi(this);
  connect(&expire_timer_, &QTimer::timeout, this, [=] {
    expire_timer_.stop();
    emit Expired();
  });
  ui_->ui_lives_view_->setScene(lives_scene_);
}

PointsPage::~PointsPage() {
  delete lives_scene_;
  delete ui_;
}

void PointsPage::SetUp() {
  points_ = 0;
  ui_->ui_points_label_->setText(QString::number(points_));
  ui_->ui_label_->setText("Get ready!");
  ui_->ui_pause_button_->setText("Pause");
  ui_->ui_retry_button_->setVisible(false);
  SetUpLives();
}

void PointsPage::Animate() {
  if (lives_count_ <= 0) {
    return;
  }
  expire_timer_.setInterval(kExpireTime);
  expire_timer_.start();
}

void PointsPage::MiniGamePassed(int64_t score) {
  ui_->ui_label_->setText("Passed!");
  points_ += score;
  ui_->ui_points_label_->setText(QString::number(points_));
}

void PointsPage::MiniGameFailed() {
  UpdateLive(--lives_count_);
  if (lives_count_ == 0) {
    ui_->ui_label_->setText("You lost...");
    expire_timer_.stop();
    ui_->ui_retry_button_->setVisible(true);
    ui_->ui_pause_button_->setText("Main Menu");
  } else {
    ui_->ui_label_->setText("Failed :(");
  }
}

void PointsPage::Pause() {
  if (lives_count_ <= 0) {
    emit MainMenu();
  }
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = expire_timer_.remainingTime();
  expire_timer_.stop();
  expire_timer_.setInterval(remaining_time_);
  emit Paused();
}

void PointsPage::Resume() {
  expire_timer_.setInterval(qMax(expire_timer_.remainingTime(), kResumeTime));
  expire_timer_.start();
}

void PointsPage::Retry() {
  emit Retried();
  SetUp();
  Animate();
}

void PointsPage::SetUpLives() {
  ui_->ui_lives_view_->scene()->clear();
  lives_count_ = kBasicLivesCount;
  for (int32_t i = -lives_count_ / 2; i <= (lives_count_ - 1) / 2; i++) {
    // Will be further replaced with animated sprites
    QGraphicsEllipseItem* new_live = new QGraphicsEllipseItem(
        i * (kLiveInterval + ui_->ui_lives_view_->height() * 0.9), 0,
        ui_->ui_lives_view_->height() * 0.9,
        ui_->ui_lives_view_->height() * 0.9);
    new_live->setBrush(kActiveLiveColor);
    ui_->ui_lives_view_->scene()->addItem(new_live);
  }
}

void PointsPage::UpdateLive(int32_t live_num) {
  QGraphicsEllipseItem* live = dynamic_cast<QGraphicsEllipseItem*>(
      ui_->ui_lives_view_->scene()->items().at(live_num));
  if (live == nullptr) {
    return;
  }
  live->setBrush(kInactiveLiveColor);
}
