#include "timebar.h"

#include <limits>

TimeBar::TimeBar(QGraphicsView* graphics_view, qreal width, qreal height,
                 qreal x, qreal y)
    : GameObject(graphics_view, width, height, x, y) {
  this->setCacheMode(ItemCoordinateCache);
  this->setZValue(std::numeric_limits<qreal>::max());
}

TimeBar::TimeBar(QGraphicsView* graphics_view, qreal width, qreal height,
                 QPointF pos)
    : TimeBar(graphics_view, width, height, pos.x(), pos.y()) {}

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
