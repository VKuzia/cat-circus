#include "vector2d.h"

Vector2D::Vector2D(const Vector2D& rhs) : QPointF(rhs) {}

Vector2D::Vector2D(qreal x, qreal y) : QPointF(x, y) {}

Vector2D& Vector2D::operator=(Vector2D rhs) {
  setX(rhs.x());
  setY(rhs.y());
  return *this;
}

bool Vector2D::IsZero() {
  if (abs(x()) < 0.00001 && abs(y()) < 0.00001) {
    return true;
  }
  return false;
}

Vector2D operator+(Vector2D first, Vector2D second) {
  first += second;
  return first;
}

Vector2D& Vector2D::operator+=(Vector2D second) {
  setX(x() + second.x());
  setY(y() + second.y());
  return *this;
}

Vector2D operator-(Vector2D first, Vector2D second) {
  first -= second;
  return first;
}

Vector2D& Vector2D::operator-=(Vector2D second) {
  setX(x() - second.x());
  setY(y() - second.y());
  return *this;
}

qreal ScalarProduct(Vector2D first, Vector2D second) {
  return first.x() * second.x() + first.y() * second.y();
}

Vector2D operator*(Vector2D vector, qreal num) {
  vector *= num;
  return vector;
}

Vector2D& Vector2D::operator*=(qreal num) {
  setX(x() * num);
  setY(y() * num);
  return *this;
}

Vector2D operator/(Vector2D vector, qreal num) {
  vector /= num;
  return vector;
}

Vector2D& Vector2D::operator/=(qreal num) {
  setX(x() / num);
  setY(y() / num);
  return *this;
}

qreal Vector2D::Length() const { return qSqrt(x() * x() + y() * y()); }
