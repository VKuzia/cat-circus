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
  GameObject(GameView* game_view, qreal width, qreal height, qreal x = 0,
             qreal y = 0);
  GameObject(GameView* game_view, qreal width, qreal height, QPointF pos);
  ~GameObject() override = default;

  virtual void SetUp();
  virtual void Update();

  void AddVelocity(qreal x, qreal y);
  void SetVelocity(qreal x, qreal y);
  void SetVelocity(Vector2D velocity);
  Vector2D GetVelocity() const;

  QRectF boundingRect() const override;

  qreal GetX() const;
  void SetX(qreal x);

  qreal GetY() const;
  void SetY(qreal y);

  QPointF GetPos() const;
  void SetPos(QPointF pos);

  void MoveByMeters(qreal x, qreal y);

 protected:
  // Represents 60 frames a second refresh time
  // Is used for motion calculus
  const qreal kUpdateTime = 1.0 / 60;
  const QRectF kDefaultBoundingRect;

  GameView* game_view_;
  qreal width_ = 0;
  qreal height_ = 0;
  qreal x_ = 0;
  qreal y_ = 0;
  Vector2D velocity_ = {0, 0};
};

#endif  // GAMEOBJECT_H
