#include "vector2d.h"

Vector2D::Vector2D(const Vector2D& rhs) : QPointF(rhs) {}

Vector2D::Vector2D(qreal x, qreal y) : QPointF(x, y) {}

Vector2D& Vector2D::operator=(Vector2D rhs) {
  setX(rhs.x());
  setY(rhs.y());
  return *this;
}

Vector2D Vector2D::operator+(Vector2D second) {
  return {x() + second.x(), y() + second.y()};
}

Vector2D& Vector2D::operator+=(Vector2D second) {
  setX(x() + second.x());
  setY(y() + second.y());
  return *this;
}

Vector2D Vector2D::operator-(Vector2D second) {
  return {x() - second.x(), y() - second.y()};
}

Vector2D& Vector2D::operator-=(Vector2D second) {
  setX(x() - second.x());
  setY(y() - second.y());
  return *this;
}

qreal Vector2D::ScalarProduct(Vector2D second) {
  return (x() * second.x() + y() * second.y());
}

Vector2D Vector2D::operator*(qreal num) { return {x() * num, y() * num}; }

Vector2D& Vector2D::operator*=(qreal num) {
  setX(x() * num);
  setY(y() * num);
  return *this;
}

Vector2D Vector2D::operator/(qreal num) { return {x() / num, y() / num}; }

Vector2D& Vector2D::operator/=(qreal num) {
  setX(x() / num);
  setY(y() / num);
  return *this;
}

qreal Vector2D::Length() const { return qSqrt(x() * x() + y() * y()); }
