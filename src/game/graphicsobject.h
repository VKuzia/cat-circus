#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QGraphicsItem>
#include <QGraphicsView>

class GraphicsObject : public QGraphicsItem {
 public:
  GraphicsObject(QGraphicsView* graphics_view, qreal width, qreal height,
                 qreal x = 0, qreal y = 0);
  ~GraphicsObject() override;
  QRectF boundingRect() const override = 0;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override = 0;

 protected:
  QGraphicsView* graphics_view_;
  qreal width_;
  qreal height_;
};

#endif  // GRAPHICSOBJECT_H
