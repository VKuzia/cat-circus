#include "physics.h"
#include <QtMath>
#include <QVector2D>




QPair<int, int> physics::newPosition(QPair<int, int>* current_c,
                                     const QVector2D& vilocity) {
    QPair<int, int> answer = {0,0};
    int new_x = current_c->first + vilocity.x();
    int new_y = current_c->second+vilocity.y();
    answer = {new_x, new_y};
    return answer;
}


QVector2D physics::ellasticCollisionWall(const QVector2D& impulse,
                                                  double wall_angle) {
    QVector2D answer{0, 0};
    QVector2D wall_vector{static_cast<float>(cos(wall_angle)),
                          static_cast<float>(sin(wall_angle))};
    QPair<double, double> normal_wall{-wall_vector.y(), wall_vector.x()};
    double alpha_cos = QVector2D::dotProduct(impulse, wall_vector)/
                       (impulse.length()*wall_vector.length());
    double alpha_sin = sin(acos(alpha_cos) + wall_angle);
    alpha_cos = cos(asin(alpha_sin));
    answer = {static_cast<float>(impulse.x()*alpha_cos),
              static_cast<float>(impulse.y()*alpha_sin)};
    return answer;
}


QPair<int, int> physics::Advance(QVector2D* vilocity,
                                 const QPair<int, int> coordinates) {
    QPair<int, int> answer = {coordinates.first + vilocity->x(),
                              coordinates.second + vilocity->y() + g.y()/2};
    vilocity->setY(vilocity->y() - g.y());
    return answer;
}




void ellasticColisionTwoObjects(const double& mass_f, QVector2D* vilocity_f,
                                const double& mass_s, QVector2D* vilocity_s) {
    QVector2D vilocity = *vilocity_f-*vilocity_s;
    QVector2D u1 = vilocity*mass_s/(mass_f+mass_s);
    QVector2D u2 = vilocity*mass_f/(mass_f+mass_s);
    double peace = M_PI_2/(mass_f+mass_s);
    double angle_f = peace*mass_s;
    double angle_s = peace*mass_f;
    u1.setX(u1.x()*cos(angle_f) + u1.y()*sin(angle_f));
    u1.setY(u1.y()*cos(angle_f) - u1.x()*sin(angle_f));
    u2.setX(u2.x()*cos(angle_s) + u2.y()*sin(angle_s));
    u2.setY(u2.y()*cos(angle_s) - u2.x()*sin(angle_s));
    vilocity_f->setX(u1.x());
    vilocity_f->setY(u1.y());
    vilocity_s->setX(u2.x());
    vilocity_s->setY(u2.y());
}
