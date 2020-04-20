#ifndef CLICKABLEBALL_H
#define CLICKABLEBALL_H

#include "src/game/graphicsobject.h"

class ClickableBall : public GraphicsObject {
 public:
  ClickableBall(QGraphicsView* graphics_view, float width, float height,
                float x = 0, float y = 0);
  ~ClickableBall() override;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 private:
  static const QColor kBasicColor;
};

#endif  // CLICKABLEBALL_H
