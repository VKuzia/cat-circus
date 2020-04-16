#include "physics.h"

#include <QVector2D>


const QVector2D Physics::g = {0, 9.80655};

void Physics::CollideTwoObjects(const double& mass1,
                                         QVector2D* velocity1,
                                         const double& mass2,
                                         QVector2D* velocity2) {
    QVector2D velocity = *velocity1 - *velocity2;
    QVector2D u1 = velocity * mass2 / (mass1 + mass2);
    QVector2D u2 = velocity * mass1 / (mass1 + mass2);
    double peace = M_PI_2 / (mass1 + mass2);
    double angle_f = peace * mass2;
    double angle_s = peace * mass1;
    u1.setX(u1.x() * cos(angle_f) + u1.y() * sin(angle_f));
    u1.setY(u1.y() * cos(angle_f) - u1.x() * sin(angle_f));
    u2.setX(u2.x() * cos(angle_s) + u2.y() * sin(angle_s));
    u2.setY(u2.y() * cos(angle_s) - u2.x() * sin(angle_s));
    velocity1->setX(u1.x());
    velocity1->setY(u1.y());
    velocity2->setX(u2.x());
    velocity2->setY(u2.y());
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

QPair<int, int> Physics::Advance(QVector2D* velocity,
                                 const QPair<int, int>& coordinates) {
    QPair<int, int> answer = {coordinates.first + velocity->x(),
                              coordinates.second + velocity->y() + g.y() / 2};
    velocity->setY(velocity->y() - g.y());
    return answer;
}
