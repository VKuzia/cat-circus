#include "vector2d.h"

Vector2D::Vector2D(const Vector2D& rhs) : QPointF(rhs) {}

Vector2D::Vector2D(qreal x, qreal y) : QPointF(x, y) {}

Vector2D& Vector2D::operator=(Vector2D rhs) {
  setX(rhs.x());
  setY(rhs.y());
  return *this;
}

Vector2D operator+(Vector2D first, Vector2D second) {
  return {first.x() + second.x(), first.y() + second.y()};
}

Vector2D& Vector2D::operator+=(Vector2D second) {
  *this = *this + second;
  return *this;
}

Vector2D operator-(Vector2D first, Vector2D second) {
  return {first.x() - second.x(), first.y() - second.y()};
}

Vector2D& Vector2D::operator-=(Vector2D second) {
  *this = *this - second;
  return *this;
}

qreal ScalarProduct(Vector2D first, Vector2D second) {
  return first.x() * second.x() + first.y() * second.y();
}

Vector2D operator*(Vector2D vector, qreal num) {
  return {vector.x() * num, vector.y() * num};
}

Vector2D& Vector2D::operator*=(qreal num) {
  *this = *this * num;
  return *this;
}

Vector2D operator/(Vector2D vector, qreal num) {
  return {vector.x() / num, vector.y() / num};
}

Vector2D& Vector2D::operator/=(qreal num) {
  *this = *this / num;
  return *this;
}

qreal Vector2D::Length() const { return qSqrt(x() * x() + y() * y()); }
