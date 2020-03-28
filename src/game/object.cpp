#include "src/game/object.h"

#include <QPainter>

QRectF Object::boundingRect() const {
  return QRectF(-bounding_width_ / 2, -bounding_height_ / 2, bounding_width_,
                bounding_height_);
}

void Object::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
