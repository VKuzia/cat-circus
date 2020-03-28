#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QVector2D>

class Object : QGraphicsItem {
 public:
  Object() = default;
  virtual ~Object() override = default;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
             QWidget*) override;

 protected:
  bool is_movable_ = true;
  qreal bounding_width_;
  qreal bounding_height_;
  QVector2D velocity_;
  double mass_;

  QPixmap* sprite_ = nullptr;
};

#endif  // OBJECT_H
