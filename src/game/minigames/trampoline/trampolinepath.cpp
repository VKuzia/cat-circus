#include "trampolinepath.h"

TrampolinePath::TrampolinePath(GameView* game_view) : game_view_(game_view) {
  // Path needs to be displayed under the cursor, but scene origin is not in an
  // upper left corner
  setPos(-game_view_->width() / 2, -game_view_->height() / 2);

  opacity_animation_.setTargetObject(this);
  opacity_animation_.setPropertyName("opacity");
  opacity_animation_.setKeyValueAt(0.0, 1.0);
  opacity_animation_.setKeyValueAt(1.0, 0.0);
}

void TrampolinePath::MoveTo(QPointF point) { path_.moveTo(point); }

void TrampolinePath::LineTo(QPointF point) {
  path_.lineTo(point);
  setPath(path_);
}

void TrampolinePath::FadeAway(int32_t millis) {
  opacity_animation_.setDuration(millis);
  opacity_animation_.start();
  connect(&opacity_animation_, &QPropertyAnimation::finished, this,
          [this] { emit FadedAway(); });
}
