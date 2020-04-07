#ifndef PHYSICS_H
#define PHYSICS_H
#include <QtMath>
#include <QPair>
#include <QVector>
#include <QVector2D>


class physics {

public:
    static void ellasticColisionTwoObjects(const double&, QVector2D*,
                                           const double&, QVector2D*);

    static QVector2D ellasticCollisionWall(const QVector2D&,
                                                      double  );

    static QPair<int,int> Advance(QVector2D*,const QPair<int, int>);


private:
    constexpr static const QVector2D g =  {0, 9.80655};

    static QPair<int,int> newPosition(QPair<int, int>*,
                                      const QVector2D&);
};

#endif  // PHYSICS_H
