#ifndef CLICKABLEBALL_H
#define CLICKABLEBALL_H

#include "src/game/graphicsobject.h"

class ClickableBall : public GraphicsObject {
 public:
  ClickableBall(QGraphicsView* graphics_view, qreal width, qreal height,
                qreal x = 0, qreal y = 0);
  ~ClickableBall() override;
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 private:
  const QColor kBasicColor = QColor::fromRgb(133, 50, 168);
};

#endif  // CLICKABLEBALL_H
