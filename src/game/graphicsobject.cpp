#include "graphicsobject.h"

GraphicsObject::GraphicsObject(QGraphicsView* graphics_view, float width,
                               float height, float x, float y)
    : graphics_view_(graphics_view), width_(width), height_(height) {
  setPos(x, y);
}

GraphicsObject::~GraphicsObject() {}
