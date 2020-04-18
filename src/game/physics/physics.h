#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector2D>
#include <QtMath>
#include <QPair>



namespace   Physics {
    void CollideTwoObjects(const float& mass1,
                           QVector2D* velocity1,
                           const float& mass2,
                           QVector2D* velocity2);


    QVector2D Reflect(const QVector2D& impulse,
                      double wall_angle);

    QPoint Advance(QVector2D* velocity,
                   const QPoint& coordinates);


    extern const QVector2D kGravity;
};  // namespace Physics

#endif  // PHYSICS_H
