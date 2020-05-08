#include "trampolinepath.h"

TrampolinePath::TrampolinePath(GameView* game_view) : game_view_(game_view) {
  setPos(-game_view_->width() / 2, -game_view_->height() / 2);

  animation_.setTargetObject(this);
  animation_.setPropertyName("opacity");
  animation_.setKeyValueAt(0.0, 1.0);
  animation_.setKeyValueAt(1.0, 0.0);
}

void TrampolinePath::MoveTo(QPointF point) { path_.moveTo(point); }

void TrampolinePath::LineTo(QPointF point) {
  path_.lineTo(point);
  setPath(path_);
}

void TrampolinePath::FadeAway(int32_t millis) {
  animation_.setDuration(millis);
  animation_.start();
  connect(&animation_, &QPropertyAnimation::finished, this,
          [this] { emit FadedAway(); });
}
