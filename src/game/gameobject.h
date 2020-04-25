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
  explicit GameObject(GameView* graphics_view);
  GameObject(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
             qreal y = 0);
  GameObject(GameView* graphics_view, qreal width, qreal height, QPointF pos);
  ~GameObject() override = default;

  virtual void SetUp();
  virtual void Update();

  QRectF boundingRect() const override;

  qreal GetX() const;
  void SetX(qreal x);

  qreal GetY() const;
  void SetY(qreal y);

  void MoveByMeters(qreal x, qreal y);

 protected:
  static const QString kPathToMinigameImages;

  // 60 frames period
  const qreal kUpdateTime = 1.0 / 60;
  const QRectF kDefaultBoundingRect;

  GameView* graphics_view_;
  qreal width_ = 0;
  qreal height_ = 0;
  qreal x_ = 0;
  qreal y_ = 0;
};

#endif  // GAMEOBJECT_H
