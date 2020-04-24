#include "timebar.h"

#include <limits>

TimeBar::TimeBar(GameView* graphics_view, qreal width, qreal height, qreal x,
                 qreal y)
    : GameObject(graphics_view, width, height, x, y) {
  this->setCacheMode(ItemCoordinateCache);
  this->setZValue(std::numeric_limits<qreal>::max());
}

TimeBar::TimeBar(GameView* graphics_view, qreal width, qreal height,
                 QPointF pos)
    : TimeBar(graphics_view, width, height, pos.x(), pos.y()) {}

void TimeBar::SetUp() {
  timeline_.setEasingCurve(QEasingCurve::Linear);
  animation_.setTimeLine(&timeline_);
  animation_.setItem(this);
}

void TimeBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                    QWidget*) {
  painter->setBrush(kBasicColor);
  painter->setPen(Qt::NoPen);
  painter->drawRect(boundingRect());
}

void TimeBar::SetProgress(qreal progress) {
  progress_ = qMax(0.0, progress);
  this->setTransform(QTransform::fromScale(progress_, 1.0));
}

void TimeBar::Launch(qreal seconds) {
  animation_.clear();
  timeline_.stop();
  timeline_.setDuration(qRound(1000 * seconds));
  animation_.setScaleAt(0.0, 1.0, 1.0);
  animation_.setScaleAt(1.0, 0.0, 1.0);
  timeline_.start();
}
