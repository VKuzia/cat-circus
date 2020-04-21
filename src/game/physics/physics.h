#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector2D>
#include <QtMath>

namespace physics {
void CollideTwoObjects(float mass1, QVector2D* velocity1, float mass2,
                       QVector2D* velocity2);

QVector2D Reflect(QVector2D impulse, float wall_angle);

QPointF Advance(QVector2D* velocity, QPointF coordinates);

QVector2D Throw(QPointF start, QPointF finish, float time);

extern const QVector2D kGravity;
};  // namespace physics

#endif  // PHYSICS_H
