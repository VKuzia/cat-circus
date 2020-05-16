#include "timebar.h"

#include <limits>

TimeBar::TimeBar(GameView* game_view, qreal width, qreal height, qreal x,
                 qreal y)
    : GameObject(game_view, width, height, x, y) {
  setZValue(std::numeric_limits<qreal>::max());
}

TimeBar::TimeBar(GameView* game_view, qreal width, qreal height, QPointF pos)
    : TimeBar(game_view, width, height, pos.x(), pos.y()) {}

void TimeBar::SetUp() {
  int32_t width = qRound(boundingRect().width());
  int32_t height = qRound(boundingRect().height());
  QPixmap pixmap(width, height);
  QPainter painter(&pixmap);
  painter.setBrush(kBasicColor);
  painter.setPen(Qt::NoPen);
  painter.drawRect(0, 0, width, height);
  setOffset(-width / 2, -height / 2);
  setPixmap(pixmap);

  progress_animation_.setTargetObject(this);
  progress_animation_.setPropertyName("progress");
  progress_animation_.setKeyValueAt(0.0, 1.0);
  progress_animation_.setKeyValueAt(1.0, 0.0);
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

int32_t TimeBar::GetCurrentTime() const {
  return progress_animation_.currentTime();
}
