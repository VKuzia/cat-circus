#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QGraphicsItem>
#include <QGraphicsView>

class GraphicsObject : public QGraphicsItem {
 public:
  GraphicsObject(QGraphicsView* graphics_view, float width, float height,
                 float x = 0, float y = 0);
  ~GraphicsObject() override;

  QRectF boundingRect() const override = 0;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override = 0;

 protected:
  QGraphicsView* graphics_view_;
  float width_;
  float height_;
};

#endif  // GRAPHICSOBJECT_H
