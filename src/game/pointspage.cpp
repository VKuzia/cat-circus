#include "pointspage.h"

#include "ui_pointspage.h"

PointsPage::PointsPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PointsPage), expire_timer_(new QTimer(this)) {
  ui->setupUi(this);
  connect(expire_timer_, &QTimer::timeout, this, [=] {
    expire_timer_->stop();
    emit Expired();
  });
}

void PointsPage::Animate() {
  expire_timer_->stop();
  expire_timer_->setInterval(kExpireTime);
  expire_timer_->start();
}

void PointsPage::MiniGamePassed(int64_t score) {
  ui->_points_label->setText("You won and scored\n" + QString::number(score) +
                             " points");
}

void PointsPage::MiniGameFailed() { ui->_points_label->setText("You lost :("); }

void PointsPage::Pause() {
  // There are no pause/resume in QTimer
  int32_t remaining_time_ = expire_timer_->remainingTime();
  expire_timer_->stop();
  expire_timer_->setInterval(remaining_time_);
  emit Paused();
}

void PointsPage::Resume() {
  expire_timer_->setInterval(qMax(expire_timer_->remainingTime(), kResumeTime));
  expire_timer_->start();
}
