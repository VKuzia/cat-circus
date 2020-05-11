#include "loadingwidget.h"

#include <QDir>

#include "ui_loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget(parent),
      loading_movie_(QDir::currentPath() + "/data/images/loading/loading.gif"),
      ui_(new Ui::LoadingWidget) {
  ui_->setupUi(this);
}

LoadingWidget::~LoadingWidget() { delete ui_; }

void LoadingWidget::SetUp() {
  this->setVisible(false);
  is_opaque_ = false;
  effect_ = new QGraphicsOpacityEffect();
  setGraphicsEffect(effect_);
  SetOpacity(0);

  animation_.setTargetObject(this);
  animation_.setPropertyName("opacity");
  // Fade in + Fade out + Stay opaque time
  int32_t animation_duration =
      kAnimationFadeDuration * 2 + kAnimationStayDuration;
  animation_.setDuration(animation_duration);
  animation_.setStartValue(0);
  // Stay totally opaque when kAnimationInOutDuration
  // is reached for kAnimationStayDuration
  animation_.setKeyValueAt(kAnimationFadeDuration * 1.0 / animation_duration,
                           255);
  animation_.setKeyValueAt((kAnimationFadeDuration + kAnimationStayDuration) *
                               1.0 / animation_duration,
                           255);
  animation_.setEndValue(0);
  connect(&animation_, &QPropertyAnimation::finished, this, [this] {
    this->setVisible(false);
    is_opaque_ = false;
    loading_movie_.stop();
    emit AnimationFinished();
  });

  ui_->ui_loading_label_->setMovie(&loading_movie_);
}

void LoadingWidget::Animate() {
  this->setVisible(true);
  loading_movie_.setScaledSize(ui_->ui_loading_label_->size());
  loading_movie_.start();
  animation_.start();
}

void LoadingWidget::SetOpacity(int opacity) {
  opacity_ = opacity;
  // To animate opacity of the children
  effect_->setOpacity(opacity_ / 255.0);
  // Background's opacity is not animated with effect
  // (only strict background color is set with StyleSheet)
  // so we need to update it too
  ui_->ui_loading_base_widget_->setStyleSheet(
      QString("background-color: rgba(%1, %2, %3, %4)")
          .arg(kBackgroundColor.red())
          .arg(kBackgroundColor.green())
          .arg(kBackgroundColor.blue())
          .arg(opacity));
  if (opacity == 255 && !is_opaque_) {
    emit BecameOpaque();
    is_opaque_ = true;
  }
}

int LoadingWidget::GetOpacity() const { return opacity_; }
