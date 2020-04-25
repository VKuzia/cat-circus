#include "timebar.h"

#include <limits>

TimeBar::TimeBar(GameView* graphics_view, qreal width, qreal height, qreal x,
                 qreal y)
    : GameObject(graphics_view) {
  setZValue(std::numeric_limits<qreal>::max());
  this->width_ = width;
  this->height_ = height;
  setPos(x, y);
}

TimeBar::TimeBar(GameView* graphics_view, qreal width, qreal height,
                 QPointF pos)
    : TimeBar(graphics_view, width, height, pos.x(), pos.y()) {}

void TimeBar::SetUp() {
  QPixmap pixmap(qRound(width_), qRound(height_));
  QPainter painter(&pixmap);
  painter.setBrush(kBasicColor);
  painter.setPen(Qt::NoPen);
  painter.drawRect(0, 0, qRound(width_), qRound(height_));
  setOffset(-width_ / 2, -height_ / 2);
  setPixmap(pixmap);

  progress_animation_.setTargetObject(this);
  progress_animation_.setPropertyName("progress");
  progress_animation_.setKeyValueAt(0.0, 1.0);
  progress_animation_.setKeyValueAt(1.0, 0.0);
}

QRectF TimeBar::boundingRect() const {
  return QRectF(-width_ / 2, -height_ / 2, width_, height_);
}

void TimeBar::SetProgress(qreal progress) {
  progress_ = qMax(0.0, progress);
  this->setTransform(QTransform::fromScale(progress_, 1.0));
}

qreal TimeBar::GetProgress() const { return progress_; }

void TimeBar::Launch(int32_t millis) {
  progress_animation_.stop();
  progress_animation_.setDuration(millis);
  progress_animation_.start();
}
