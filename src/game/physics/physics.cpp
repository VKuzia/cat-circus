#include "physics.h"
#include <QtMath>
#include <QVector2D>


const QVector2D Physics::g =  {0, 9.80655};

QPair<int, int> Physics::NewPosition(const QPair<int, int>& current_c,
                                     const QVector2D& velocity) {
    return {current_c.first + velocity.x(),
            current_c.second + velocity.y()};
}


QVector2D Physics::EllasticCollisionWall(const QVector2D& impulse,
                                                  double wall_angle) {
    QVector2D wall_vector{static_cast<float>(cos(wall_angle)),
                          static_cast<float>(sin(wall_angle))};
    QPair<double, double> normal_wall{-wall_vector.y(), wall_vector.x()};
    double alpha_cos = QVector2D::dotProduct(impulse, wall_vector)/
                       (impulse.length()*wall_vector.length());
    double alpha_sin = sin(acos(alpha_cos) + wall_angle);
    alpha_cos = cos(asin(alpha_sin));
    return {static_cast<float>(impulse.x()*alpha_cos),
            static_cast<float>(impulse.y()*alpha_sin)};
}


QPair<int, int> Physics::Advance(QVector2D* velocity,
                                 const QPair<int, int>& coordinates) {
    QPair<int, int> answer = {coordinates.first + velocity->x(),
                              coordinates.second + velocity->y() + g.y()/2};
    velocity->setY(velocity->y() - g.y());
    return answer;
}




void Physics::EllasticCollisionTwoObjects(const double& mass_f,
                                          QVector2D* velocity_f,
                                          const double& mass_s,
                                          QVector2D* velocity_s) {
    QVector2D velocity = *velocity_f-*velocity_s;
    QVector2D u1 = velocity*mass_s/(mass_f+mass_s);
    QVector2D u2 = velocity*mass_f/(mass_f+mass_s);
    double peace = M_PI_2/(mass_f+mass_s);
    double angle_f = peace*mass_s;
    double angle_s = peace*mass_f;
    u1.setX(u1.x()*cos(angle_f) + u1.y()*sin(angle_f));
    u1.setY(u1.y()*cos(angle_f) - u1.x()*sin(angle_f));
    u2.setX(u2.x()*cos(angle_s) + u2.y()*sin(angle_s));
    u2.setY(u2.y()*cos(angle_s) - u2.x()*sin(angle_s));
    velocity_f->setX(u1.x());
    velocity_f->setY(u1.y());
    velocity_s->setX(u2.x());
    velocity_s->setY(u2.y());
}

