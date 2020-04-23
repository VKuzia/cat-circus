#ifndef CLICKABLEBALL_H
#define CLICKABLEBALL_H

#include <QGraphicsSceneMouseEvent>

#include "src/game/gameobject.h"

class ClickableBall : public GameObject {
  Q_OBJECT

 public:
  ClickableBall(QGraphicsView* graphics_view, qreal width, qreal height,
                qreal x = 0, qreal y = 0);
  ClickableBall(QGraphicsView* graphics_view, qreal width, qreal height,
                QPointF pos);
  ~ClickableBall() override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 signals:
  void Clicked();

 private:
  const QColor kBasicColor = QColor::fromRgb(133, 50, 168);

  void mousePressEvent(QGraphicsSceneMouseEvent*) override;
};

#endif  // CLICKABLEBALL_H
