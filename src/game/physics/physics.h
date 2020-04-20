#ifndef PHYSICS_H
#define PHYSICS_H

#include <QPair>
#include <QVector2D>
#include <QtMath>

namespace Physics {
void CollideTwoObjects(const float &mass1, QVector2D *velocity1,
                       const float &mass2, QVector2D *velocity2);

QVector2D Reflect(const QVector2D &impulse, double wall_angle);

QPoint Advance(QVector2D *velocity, const QPoint &coordinates);

QVector2D Throw(QPointF start, QPointF finish, float time);

extern const QVector2D kGravity;
// clang-format off
};  // namespace Physics
// clang-format on

#endif // PHYSICS_H
