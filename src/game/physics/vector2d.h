#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <QPointF>
#include <QtMath>

class Vector2D : public QPointF {
 public:
  Vector2D() : QPointF() {}
  Vector2D(std::initializer_list<qreal> rhs);
  Vector2D(Vector2D const& rhs) : QPointF(rhs) {}
  Vector2D(qreal x, qreal y) : QPointF(x, y) {}

  const Vector2D& operator=(const Vector2D& rhs) { return rhs; }
  Vector2D operator=(std::initializer_list<qreal> param);

  Vector2D operator+(Vector2D);

  Vector2D operator-(Vector2D);

  qreal operator*(Vector2D);
  Vector2D operator*(qreal);

  Vector2D operator/(qreal);

  qreal length() const;
};
#endif  // VECTOR2D_H
