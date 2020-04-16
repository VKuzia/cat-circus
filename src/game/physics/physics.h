#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector2D>
#include <QtMath>
#include <QPair>



namespace   Physics {
    static void CollideTwoObjects(const double&, QVector2D*,
                                            const double&, QVector2D*);


    static QVector2D Reflect(const QVector2D&,
                                           double);

    static QPoint Advance(QVector2D*, const QPoint&);


    static const QVector2D gg = {0, 9.80655};
};  // namespace Physics

#endif  // PHYSICS_H
