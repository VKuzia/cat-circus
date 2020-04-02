#include "clickableball.h"

ClickableBall::ClickableBall(QGraphicsView* graphics_view, qreal width,
                             qreal height, qreal x, qreal y)
    : GraphicsObject(graphics_view, width, height, x, y) {}

ClickableBall::~ClickableBall() {}

QRectF ClickableBall::boundingRect() const {
  return QRectF(-width_ / 2, -height_ / 2, width_, height_);
}

void ClickableBall::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                          QWidget*) {
  painter->setBrush(kBasicColor);
  painter->drawEllipse(boundingRect());
}
