#ifndef CLICKABLEBALL_H
#define CLICKABLEBALL_H

#include <QGraphicsSceneMouseEvent>

#include "src/game/gameobject.h"

class ClickableBall : public GameObject {
  Q_OBJECT

 public:
  ClickableBall(QGraphicsView* graphics_view, float width, float height,
                float x = 0, float y = 0);
  ~ClickableBall() override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 signals:
  void Clicked();

 private:
  static const QColor kBasicColor;

  void mousePressEvent(QGraphicsSceneMouseEvent*) override;
};

#endif  // CLICKABLEBALL_H
