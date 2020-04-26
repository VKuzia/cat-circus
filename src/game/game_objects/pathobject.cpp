#include "pathobject.h"

PathObject::PathObject(GameView* graphics_view)
    : graphics_view_(graphics_view) {
  setPos(-graphics_view_->width() / 2, -graphics_view_->height() / 2);
}

void PathObject::MoveTo(const QPointF point) { path_.moveTo(point); }

void PathObject::LineTo(const QPointF& point) {
  path_.lineTo(point);
  setPath(path_);
}

void PathObject::FadeAway(int32_t millis) {
  animation_.setTargetObject(this);
  animation_.setPropertyName("opacity");
  animation_.setKeyValueAt(0.0, 1.0);
  animation_.setKeyValueAt(1.0, 0.0);
  animation_.setDuration(millis);
  animation_.start();
  connect(&animation_, &QPropertyAnimation::finished, this,
          [this] { emit FadedAway(); });
}
