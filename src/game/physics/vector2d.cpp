#include "vector2d.h"

Vector2D Vector2D::operator=(std::initializer_list<qreal> param) {
  return param;
}

Vector2D::Vector2D(std::initializer_list<qreal> rhs) {
  Vector2D(*rhs.begin(), *(rhs.begin() + 1));
}

Vector2D Vector2D::operator+(Vector2D second) {
  return {this->x() + second.x(), this->y() + second.y()};
}

Vector2D Vector2D::operator-(Vector2D second) {
  return {this->x() + second.x(), this->y() + second.y()};
}

qreal Vector2D::operator*(Vector2D second) {
  return (this->x() * second.x() + this->y() * second.y());
}

Vector2D Vector2D::operator*(qreal num) {
  return {this->x() * num, this->y() * num};
}

Vector2D Vector2D::operator/(qreal num) {
  return {this->x() / num, this->y() / num};
}

qreal Vector2D::Length() const { return qSqrt(x() * x() + y() * y()); }
