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
  ui->_score_label->setText("You won and scored\n" + QString::number(score) +
                            " points");
}

void PointsPage::MiniGameFailed() { ui->_score_label->setText("You lost :("); }
