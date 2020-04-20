#include "clickableball.h"

const QColor ClickableBall::kBasicColor = QColor::fromRgb(133, 50, 168);

ClickableBall::ClickableBall(QGraphicsView* graphics_view, float width,
                             float height, float x, float y)
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
