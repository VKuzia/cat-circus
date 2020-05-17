#include "graphicsobject.h"

GraphicsObject::GraphicsObject(QGraphicsView* graphics_view, qreal width,
                               qreal height, qreal x, qreal y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(x, y);
}

GraphicsObject::~GraphicsObject() {}
