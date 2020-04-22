#include "timebar.h"

#include <limits>

TimeBar::TimeBar(QGraphicsView* graphics_view, float width, float height,
                 float x, float y)
    : GameObject(graphics_view, width, height, x, y) {
  this->setCacheMode(ItemCoordinateCache);
  this->setZValue(std::numeric_limits<qreal>::max());
}

TimeBar::~TimeBar() {}

void TimeBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                    QWidget*) {
  painter->setBrush(kBasicColor);
  painter->setPen(Qt::NoPen);
  painter->drawRect(boundingRect());
}

void TimeBar::SetProgress(float progress) {
  progress_ = qMax(0.f, progress);
  this->setTransform(QTransform::fromScale(static_cast<qreal>(progress_), 1));
}
