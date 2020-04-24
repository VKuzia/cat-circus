#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <QPointF>
#include <QtMath>

class Vector2D : public QPointF {
 public:
  Vector2D() = default;
  Vector2D(const Vector2D& rhs);
  Vector2D(qreal x, qreal y);

  Vector2D& operator=(Vector2D rhs);

  friend Vector2D operator+(Vector2D, Vector2D);
  Vector2D& operator+=(Vector2D);

  friend Vector2D operator-(Vector2D, Vector2D);
  Vector2D& operator-=(Vector2D);

  friend Vector2D operator*(Vector2D, qreal);
  Vector2D& operator*=(qreal);

  friend Vector2D operator/(Vector2D, qreal);
  Vector2D& operator/=(qreal);

  friend qreal ScalarProduct(Vector2D, Vector2D);
  qreal Length() const;
};
#endif  // VECTOR2D_H
