#ifndef CLICKABLEBALL_H
#define CLICKABLEBALL_H

#include "src/game/gameobject.h"

class ClickableBall : public GameObject {
 public:
  ClickableBall(QGraphicsView* graphics_view, float width, float height,
                float x = 0, float y = 0);
  ~ClickableBall() override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 private:
  static const QColor kBasicColor;
};

#endif  // CLICKABLEBALL_H
