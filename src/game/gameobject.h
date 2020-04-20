#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QGraphicsView>

class GameObject : public QGraphicsItem {
 public:
  GameObject(QGraphicsView* graphics_view, float width, float height,
             float x = 0, float y = 0);
  ~GameObject() override;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override = 0;

 protected:
  QGraphicsView* graphics_view_;
  float width_;
  float height_;
};

#endif  // GAMEOBJECT_H
