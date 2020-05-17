#include "button.h"

Button::Button(QWidget* parent) : QPushButton(parent), hover_animation_(this) {
  hover_animation_.setTargetObject(this);
  hover_animation_.setPropertyName("animationProgress");
  hover_animation_.setDuration(kMouseHoverAnimationDuration_);
  hover_animation_.setStartValue(0);
  hover_animation_.setEndValue(1);
}

void Button::Resize(qreal scale) { setFixedSize(size() * scale); }

void Button::enterEvent(QEvent*) {
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
                     (1 + (kMouseHoverScaleFactor_ - 1) * animation_progress_));
}

qreal Button::GetAnimationProgress() const { return animation_progress_; }
