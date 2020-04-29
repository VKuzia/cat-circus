#include "loadingwidget.h"

#include "ui_loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget(parent), ui_(new Ui::LoadingWidget) {
  ui_->setupUi(this);
}

LoadingWidget::~LoadingWidget() { delete ui_; }

void LoadingWidget::SetUp() {
  this->setDisabled(true);
  this->setVisible(false);
  ui_->ui_loading_base_widget_->setAutoFillBackground(true);
  is_opaque_ = false;
  SetOpacity(0);

  animation_.setTargetObject(this);
  animation_.setPropertyName("opacity");
  // Fade in + Fade out + Stay opaque time
  int32_t animation_duration =
      kAnimationInOutDuration * 2 + kAnimationStayDuration;
  animation_.setDuration(animation_duration);
  animation_.setStartValue(0);
  animation_.setKeyValueAt(kAnimationInOutDuration * 1.0 / animation_duration,
                           255);
  animation_.setKeyValueAt((kAnimationInOutDuration + kAnimationStayDuration) *
                               1.0 / animation_duration,
                           255);
  animation_.setEndValue(0);
  connect(&animation_, &QPropertyAnimation::finished, this, [this] {
    this->setDisabled(true);
    this->setVisible(false);
    is_opaque_ = false;
    emit AnimationFinished();
  });
}

void LoadingWidget::Animate() {
  this->setVisible(true);
  this->setDisabled(false);
  animation_.start();
}

void LoadingWidget::SetOpacity(int opacity) {
  opacity_ = opacity;
  ui_->ui_loading_base_widget_->setStyleSheet(kBackgroundStyleSheet.chopped(2) +
                                              ", " + QString::number(opacity_) +
                                              ");");
  if (opacity == 255 && !is_opaque_) {
    emit BecameOpaque();
    is_opaque_ = true;
  }
}

int LoadingWidget::GetOpacity() const { return opacity_; }
