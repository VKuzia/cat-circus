#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector2D>
#include <QtMath>
#include <QPair>



class Physics {
 public:
    static void CollideTwoObjects(const double&, QVector2D*,
                                            const double&, QVector2D*);


    static QVector2D Reflect(const QVector2D&,
                                           double);

    static QPair<int, int> Advance(QVector2D*, const QPair<int, int>&);


 private:
    static const QVector2D g;
};

#endif  // PHYSICS_H
