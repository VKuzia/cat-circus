#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector2D>
#include <QtMath>

class Vector2D : public QPointF {
 public:
  Vector2D() {}
  Vector2D(std::initializer_list<qreal>) {}
  Vector2D(Vector2D const&) {}
  Vector2D(qreal, qreal) {}

  const Vector2D& operator=(const Vector2D& rhs) { return rhs; }
  Vector2D operator=(std::initializer_list<qreal> param) {
    return Vector2D(param);
  }

  Vector2D operator+(Vector2D);

  Vector2D operator-(Vector2D);

  qreal operator*(Vector2D);
  Vector2D operator*(qreal);

  Vector2D operator/(qreal);
};

namespace physics {
void CollideTwoObjects(float mass1, Vector2D* velocity1, float mass2,
                       Vector2D* velocity2);

QVector2D Reflect(QVector2D impulse, float wall_angle);

QPointF Advance(QVector2D* velocity, QPointF coordinates);

QVector2D Throw(QPointF start, QPointF finish, float time);

extern const QVector2D kGravity;
};  // namespace physics

#endif  // PHYSICS_H
