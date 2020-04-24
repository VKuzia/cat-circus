#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "src/game/gameview.h"
#include "src/game/physics/physics.h"

class GameObject : public QObject, public QGraphicsPixmapItem {
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
  static const QString kPathToMinigameImages;
  static QString GetPathToMinigameImages();

  GameView* graphics_view_;
  qreal width_;
  qreal height_;
};

#endif  // GAMEOBJECT_H
