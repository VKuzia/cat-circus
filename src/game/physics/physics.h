#ifndef PHYSICS_H
#define PHYSICS_H

#include <QtMath>

#include "vector2d.h"

namespace physics {
void CollideTwoObjects(qreal mass1, Vector2D* velocity1, qreal mass2,
                       Vector2D* velocity2);

Vector2D Reflect(Vector2D impulse, qreal wall_angle);

QPointF Advance(Vector2D* velocity, QPointF coordinates);

extern const Vector2D kGravity;

Vector2D Throw(QPointF start, QPointF finish, qreal time,
               Vector2D acceleration = kGravity);

};  // namespace physics

#endif  // PHYSICS_H
