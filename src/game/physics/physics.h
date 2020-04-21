#ifndef PHYSICS_H
#define PHYSICS_H

#include <QPair>
#include <QVector2D>
#include <QtMath>

namespace physics {
void CollideTwoObjects(const float &mass1, QVector2D *velocity1,
                       const float &mass2, QVector2D *velocity2);

QVector2D Reflect(const QVector2D &impulse, float wall_angle);

QPointF Advance(QVector2D *velocity, const QPointF &coordinates);

QVector2D Throw(QPointF start, QPointF finish, float time);

extern const QVector2D kGravity;
};  // namespace physics

#endif  // PHYSICS_H
