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
  // Remember, lives_scene_ clears lives_ elements
  lives_.clear();
  lives_scene_->clear();
  delete lives_scene_;
  delete ui_;
}

void PointsPage::SetUp() {
  points_ = 0;
  ui_->ui_points_label_->setText(QString::number(points_));
  ui_->ui_label_->setText("Get ready!");
  ui_->ui_stacked_button_widget_->setCurrentWidget(ui_->ui_pause_button_page_);
  ui_->ui_retry_button_->setVisible(false);
  SetUpLives();
}

void PointsPage::Animate() {
  expire_timer_.setInterval(kExpireTime);
  expire_timer_.start();
}

void PointsPage::MiniGamePassed(int64_t score) {
  ui_->ui_label_->setText("Passed!");
  points_ += score;
  ui_->ui_points_label_->setText(QString::number(points_));
}

void PointsPage::MiniGameFailed() {
  RemoveLive();
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

int32_t PointsPage::GetLivesCount() const { return lives_count_; }

void PointsPage::Pause() {
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

void PointsPage::ReturnToMainMenu() { emit MainMenu(); }

void PointsPage::SetUpLives() {
  ui_->ui_lives_view_->scene()->clear();
  lives_.clear();
  lives_count_ = kBasicLivesCount;
  for (int32_t i = -lives_count_ / 2; i <= (lives_count_ - 1) / 2; i++) {
    QGraphicsEllipseItem* new_live = GetNewLive(i);
    ui_->ui_lives_view_->scene()->addItem(new_live);
    lives_.push_back(new_live);
  }
}

QGraphicsEllipseItem* PointsPage::GetNewLive(int32_t number) const {
  // Will be further replaced with animated sprites
  QGraphicsEllipseItem* new_live = new QGraphicsEllipseItem();
  double diameter =
      ui_->ui_lives_view_->height() * static_cast<double>(kLiveHeightFactor);
  double x = number * (kLiveInterval + diameter);
  double y = 0;
  new_live->setRect(x, y, diameter, diameter);
  new_live->setBrush(kActiveLiveColor);
  return new_live;
}

void PointsPage::RemoveLive() {
  lives_count_--;
  QGraphicsEllipseItem* live = lives_.at(kBasicLivesCount - lives_count_ - 1);
  live->setBrush(kInactiveLiveColor);
}
