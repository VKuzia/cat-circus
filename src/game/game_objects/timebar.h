#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QObject>
#include <QPropertyAnimation>

#include "src/game/gameobject.h"

class TimeBar : public GameObject {
  Q_OBJECT

 public:
  TimeBar(QGraphicsView* graphics_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0);
  TimeBar(QGraphicsView* graphics_view, qreal width, qreal height, QPointF pos);
  ~TimeBar() override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  void SetProgress(qreal progress);

 private:
  const QColor kBasicColor = QColor::fromRgb(81, 204, 24);
  qreal progress_ = 1;
};

#endif  // TIMEBAR_H
