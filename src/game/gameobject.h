#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QGraphicsView>

class GameObject : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

 public:
  GameObject(QGraphicsView* graphics_view, qreal width, qreal height,
             qreal x = 0, qreal y = 0);
  GameObject(QGraphicsView* graphics_view, qreal width, qreal height,
             QPointF pos);
  ~GameObject() override;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override = 0;

 protected:
  QGraphicsView* graphics_view_;
  qreal width_;
  qreal height_;
};

#endif  // GAMEOBJECT_H
