#include "button.h"

#include <QDebug>

Button::Button(QWidget* parent) : QPushButton(parent), hover_animation_(this) {
  hover_animation_.setTargetObject(this);
  hover_animation_.setPropertyName("animationProgress");
  hover_animation_.setDuration(kMouseOverDuration_);
  hover_animation_.setStartValue(0);
  hover_animation_.setEndValue(1);
}

void Button::enterEvent(QEvent*) {
  is_mouse_over_ = true;
  if (hover_animation_.state() == QPropertyAnimation::State::Running) {
    hover_animation_.pause();
    hover_animation_.setDirection(QAbstractAnimation::Direction::Forward);
    hover_animation_.resume();
  } else {
    last_size_ = size();
    hover_animation_.setDirection(QAbstractAnimation::Direction::Forward);
    hover_animation_.start();
  }
}

void Button::leaveEvent(QEvent*) {
  is_mouse_over_ = false;
  if (hover_animation_.state() == QPropertyAnimation::State::Running) {
    hover_animation_.pause();
    hover_animation_.setDirection(QAbstractAnimation::Direction::Backward);
    hover_animation_.resume();
  } else {
    hover_animation_.setDirection(QAbstractAnimation::Direction::Backward);
    hover_animation_.start();
  }
}

void Button::SetAnimationProgress(qreal progress) {
  animation_progress_ = progress;
  this->setFixedSize(last_size_ *
                     (1 + (kMouseOverScaleFactor_ - 1) * animation_progress_));
}

qreal Button::GetAnimationProgress() const { return animation_progress_; }
