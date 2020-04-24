#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>

#include "src/game/gameview.h"

class GameObject : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

 public:
  GameObject(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
             qreal y = 0);
  GameObject(GameView* graphics_view, qreal width, qreal height, QPointF pos);
  ~GameObject() override = default;

  virtual void SetUp();
  virtual void Update();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 protected:
  GameView* graphics_view_;
  qreal width_;
  qreal height_;
};

#endif  // GAMEOBJECT_H
