#include "physics.h"

#include <QVector2D>

const QVector2D Physics::kGravity = {0, 9.80655};

void Physics::CollideTwoObjects(const float& mass1,
                                 QVector2D* velocity1,
                                 const float& mass2,
                                 QVector2D* velocity2) {
    QVector2D velocity = *velocity1 - *velocity2;
    QVector2D u1 = velocity * mass2 / (mass1 + mass2);
    QVector2D u2 = velocity * mass1 / (mass1 + mass2);
    float peace = M_PI_2 / (mass1 + mass2);
    float angle_f = peace * mass2;
    float angle_s = peace * mass1;
    *velocity1 = {static_cast<float>(u1.x() * cos(angle_f) + u1.y() * sin(angle_f)),
                  static_cast<float>(u1.y() * cos(angle_f) - u1.x() * sin(angle_f))};
    *velocity2 = {static_cast<float>(u2.x() * cos(angle_s) + u2.y() * sin(angle_s)),
                  static_cast<float>(u2.y() * cos(angle_s) - u2.x() * sin(angle_s))};
}

QVector2D Physics::Reflect(const QVector2D& impulse,
                                        double wall_angle) {
    QVector2D wall_vector{static_cast<float>(cos(wall_angle)),
                          static_cast<float>(sin(wall_angle))};
    QPair<float, float> normal_wall{-wall_vector.y(), wall_vector.x()};
    float alpha_cos = QVector2D::dotProduct(impulse, wall_vector) /
                       (impulse.length() * wall_vector.length());
    float alpha_sin = sin(acos(alpha_cos) + wall_angle);
    alpha_cos = cos(asin(alpha_sin));
    return {(impulse.x() * alpha_cos), (impulse.y()*alpha_sin)};
}

QPoint Physics::Advance(QVector2D* velocity,
                                 const QPoint& coordinates) {
    QPoint answer = {static_cast<int>(coordinates.x() + velocity->x()),
                     static_cast<int>(coordinates.y() + velocity->y() +
                                      kGravity.y() / 2)};
    velocity->setY(velocity->y() - kGravity.y());
    return answer;
}
