#include "physics.h"

#include <QVector2D>

const QVector2D physics::kGravity = {0, 9.80655};

void physics::CollideTwoObjects(const float &mass1, QVector2D *velocity1,
                                const float &mass2, QVector2D *velocity2) {
  QVector2D velocity = *velocity1 - *velocity2;
  QVector2D u1 = velocity * mass2 / (mass1 + mass2);
  QVector2D u2 = velocity * mass1 / (mass1 + mass2);
  float peace = M_PI_2 / (mass1 + mass2);
  float angle_f = peace * mass2;
  float angle_s = peace * mass1;
  *velocity1 = {(u1.x() * std::cos(angle_f) + u1.y() * std::sin(angle_f)),
                (u1.y() * std::cos(angle_f) - u1.x() * std::sin(angle_f))};
  *velocity2 = {(u2.x() * std::cos(angle_s) + u2.y() * std::sin(angle_s)),
                (u2.y() * std::cos(angle_s) - u2.x() * std::sin(angle_s))};
}

QVector2D physics::Reflect(const QVector2D &impulse, float wall_angle) {
  QVector2D wall_vector = {(std::cos(wall_angle)), (std::sin(wall_angle))};
  QPair<float, float> normal_wall{-wall_vector.y(), wall_vector.x()};
  float alpha_cos = QVector2D::dotProduct(impulse, wall_vector) /
                    (impulse.length() * wall_vector.length());
  float alpha_sin = sin(acos(alpha_cos) + wall_angle);
  alpha_cos = cos(asin(alpha_sin));
  return {(impulse.x() * alpha_cos), (impulse.y() * alpha_sin)};
}

QPointF physics::Advance(QVector2D *velocity, const QPointF &coordinates) {
  QPointF answer = {(coordinates.x() + velocity->x()),
                    (coordinates.y() + velocity->y() + kGravity.y() / 2)};
  velocity->setY(velocity->y() - kGravity.y());
  return answer;
}

QVector2D physics::Throw(QPointF start, QPointF finish, float time) {
  QVector2D answer;
  answer.setX((finish.x() - start.x()) / time);
  answer.setY((finish.y() - start.y()) / time -
              (physics::kGravity.y() * time) / 2);
  return answer;
}
