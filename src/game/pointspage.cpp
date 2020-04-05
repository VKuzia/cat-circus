#include "pointspage.h"

#include <QGraphicsEllipseItem>

#include "ui_pointspage.h"

PointsPage::PointsPage(QWidget* parent)
    : QWidget(parent), ui(new Ui::PointsPage), expire_timer_(new QTimer(this)) {
  ui->setupUi(this);
  connect(expire_timer_, &QTimer::timeout, this, [=] {
    expire_timer_->stop();
    emit Expired();
  });
  ui->_lives_view->setScene(new QGraphicsScene());
}

void PointsPage::SetUp() {
  points_ = 0;
  ui->_points_label->setText("0");
  ui->_label->setText("Get ready!");
  ui->_pause_button->setText("Pause");
  ui->_retry_button->setVisible(false);
  SetUpLives();
}

void PointsPage::Animate() {
  if (lives_count_ <= 0) {
    return;
  }
  expire_timer_->stop();
  expire_timer_->setInterval(kExpireTime);
  expire_timer_->start();
}

void PointsPage::MiniGamePassed(int64_t score) {
  ui->_label->setText("Passed!");
  points_ += score;
  ui->_points_label->setText(QString::number(points_));
}

void PointsPage::MiniGameFailed() {
  UpdateLive(--lives_count_);
  if (lives_count_ == 0) {
    ui->_label->setText("You lost...");
    expire_timer_->stop();
    ui->_retry_button->setVisible(true);
    ui->_pause_button->setText("Main Menu");
  } else {
    ui->_label->setText("Failed :(");
  }
}

void PointsPage::Pause() {
  if (lives_count_ <= 0) {
    emit MainMenu();
  }
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = expire_timer_->remainingTime();
  expire_timer_->stop();
  expire_timer_->setInterval(remaining_time_);
  emit Paused();
}

void PointsPage::Resume() {
  if (lives_count_ <= 0) {
    return;
  }
  expire_timer_->setInterval(qMax(expire_timer_->remainingTime(), kResumeTime));
  expire_timer_->start();
}

void PointsPage::Retry() {
  emit Retryed();
  SetUp();
  Animate();
}

void PointsPage::SetUpLives() {
  ui->_lives_view->scene()->clear();
  lives_count_ = kBasicLivesCount;
  for (int32_t i = -lives_count_ / 2; i <= lives_count_ / 2; i++) {
    // Will be further replaced with animated sprites
    QGraphicsEllipseItem* new_live = new QGraphicsEllipseItem(
        i * (kLiveInterval + ui->_lives_view->height() * 0.9), 0,
        ui->_lives_view->height() * 0.9, ui->_lives_view->height() * 0.9);
    new_live->setBrush(QColor::fromRgb(10, 230, 10, 200));
    ui->_lives_view->scene()->addItem(new_live);
  }
}

void PointsPage::UpdateLive(int32_t live_num) {
  QGraphicsEllipseItem* live = dynamic_cast<QGraphicsEllipseItem*>(
      ui->_lives_view->scene()->items().at(live_num));
  if (live == nullptr) {
    return;
  }
  live->setBrush(QColor::fromRgb(230, 10, 10, 200));
}
