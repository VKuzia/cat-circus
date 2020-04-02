#include "timebar.h"

TimeBar::TimeBar(QGraphicsView* graphics_view, qreal width, qreal height,
                 qreal x, qreal y)
    : GraphicsObject(graphics_view, width, height, x, y) {}

TimeBar::~TimeBar() {}

QRectF TimeBar::boundingRect() const {
  return QRectF(-width_ * progress_ / 2, -height_ / 2, width_ * progress_,
                height_);
}

void TimeBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                    QWidget*) {
  painter->setBrush(kBasicColor);
  painter->setPen(Qt::NoPen);
  painter->drawRect(boundingRect());
}

void TimeBar::SetProgress(qreal progress) { progress_ = progress; }
