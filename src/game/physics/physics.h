#ifndef PHYSICS_H
#define PHYSICS_H
#include <QtMath>
#include <QPair>
#include <QVector>
#include <QVector2D>


class Physics {
 public:
    static void EllasticCollisionTwoObjects(const double&, QVector2D*,
                                           const double&, QVector2D*);


    static QVector2D EllasticCollisionWall(const QVector2D&,
                                                      double);

    static QPair<int, int> Advance(QVector2D*, const QPair<int, int>&);


 private:
    static const QVector2D g;

    static QPair<int, int> NewPosition(const QPair<int, int>&,
                                      const QVector2D&);
};

#endif  // PHYSICS_H
