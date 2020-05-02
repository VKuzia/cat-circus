#include "timebar.h"

TimeBar::TimeBar(QGraphicsView* graphics_view, qreal width, qreal height,
                 qreal x, qreal y)
    : GraphicsObject(graphics_view, width, height, x, y) {
  this->setCacheMode(ItemCoordinateCache);
  this->setZValue(100);
}

TimeBar::~TimeBar() {}

QRectF TimeBar::boundingRect() const {
  return QRectF(-width_ / 2, -height_ / 2, width_, height_);
}

void TimeBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                    QWidget*) {
  painter->setBrush(kBasicColor);
  painter->setPen(Qt::NoPen);
  painter->drawRect(QRectF(-width_ / 2, -height_ / 2, width_, height_));
}

void TimeBar::SetProgress(qreal progress) {
  progress_ = qMax(0.0, progress);
  this->setTransform(QTransform::fromScale(progress_, 1));
}
