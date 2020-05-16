#include "physics.h"

namespace physics {
const Vector2D kGravity = {0, 9.80655};

void CollideTwoObjects(qreal mass1, Vector2D* velocity1, qreal mass2,
                       Vector2D* velocity2) {
  Vector2D velocity = *velocity1 - *velocity2;
  Vector2D u1 = velocity * mass2 / (mass1 + mass2);
  Vector2D u2 = velocity * mass1 / (mass1 + mass2);
  qreal peace = M_PI_2 / (mass1 + mass2);
  qreal angle1 = peace * mass2;
  qreal angle2 = peace * mass1;
  *velocity1 = {u1.x() * std::cos(angle1) + u1.y() * std::sin(angle1),
                u1.y() * std::cos(angle1) - u1.x() * std::sin(angle1)};
  *velocity2 = {u2.x() * std::cos(angle2) + u2.y() * std::sin(angle2),
                u2.y() * std::cos(angle2) - u2.x() * std::sin(angle2)};
}

Vector2D Reflect(Vector2D impulse, qreal wall_angle) {
  Vector2D wall_vector = {(std::cos(wall_angle)), (std::sin(wall_angle))};
  qreal alpha_cos = Vector2D::dotProduct(impulse, wall_vector) /
                    (impulse.Length() * wall_vector.Length());
  qreal alpha_sin = sin(acos(alpha_cos) + wall_angle);
  alpha_cos = cos(asin(alpha_sin));
  return {impulse.x() * alpha_cos, impulse.y() * alpha_sin};
}

QPointF Advance(Vector2D* velocity, QPointF coordinates) {
  QPointF answer = {coordinates.x() + velocity->x(),
                    coordinates.y() + velocity->y() + kGravity.y() / 2};
  velocity->setY(velocity->y() - kGravity.y());
  return answer;
}

Vector2D Throw(QPointF start, QPointF finish, qreal time,
               Vector2D acceleration) {
  return {(finish.x() - start.x()) / time,
          (finish.y() - start.y()) / time - (acceleration.y() * time) / 2};
}

}  // namespace physics
