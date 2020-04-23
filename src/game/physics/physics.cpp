#include "physics.h"

#include <QVector2D>

Vector2D Vector2D::operator=(std::initializer_list<qreal> param) {
  return Vector2D(param);
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

namespace physics {
const QVector2D kGravity = {0, 9.80655};

void CollideTwoObjects(float mass1, QVector2D* velocity1, float mass2,
                       QVector2D* velocity2) {
  QVector2D velocity = *velocity1 - *velocity2;
  QVector2D u1 = velocity * mass2 / (mass1 + mass2);
  QVector2D u2 = velocity * mass1 / (mass1 + mass2);
  float peace = M_PI_2 / (mass1 + mass2);
  float angle1 = peace * mass2;
  float angle2 = peace * mass1;
  *velocity1 = {u1.x() * std::cos(angle1) + u1.y() * std::sin(angle1),
                u1.y() * std::cos(angle1) - u1.x() * std::sin(angle1)};
  *velocity2 = {u2.x() * std::cos(angle2) + u2.y() * std::sin(angle2),
                u2.y() * std::cos(angle2) - u2.x() * std::sin(angle2)};
}

QVector2D Reflect(QVector2D impulse, float wall_angle) {
  QVector2D wall_vector = {(std::cos(wall_angle)), (std::sin(wall_angle))};
  float alpha_cos = QVector2D::dotProduct(impulse, wall_vector) /
                    (impulse.length() * wall_vector.length());
  float alpha_sin = sin(acos(alpha_cos) + wall_angle);
  alpha_cos = cos(asin(alpha_sin));
  return {impulse.x() * alpha_cos, impulse.y() * alpha_sin};
}

QPointF Advance(QVector2D* velocity, QPointF coordinates) {
  QPointF answer = {coordinates.x() + velocity->x(),
                    coordinates.y() + velocity->y() + kGravity.y() / 2};
  velocity->setY(velocity->y() - kGravity.y());
  return answer;
}

QVector2D Throw(QPointF start, QPointF finish, float time) {
  QVector2D answer;
  answer.setX((finish.x() - start.x()) / time);
  answer.setY((finish.y() - start.y()) / time - (kGravity.y() * time) / 2);
  return answer;
}

}  // namespace physics
