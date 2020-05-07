#ifndef CANNON_H
#define CANNON_H

#include <QSet>

#include "src/game/gameobject.h"
#include "src/game/minigames/cannon/cannoncat.h"

class Cannon : public GameObject {
 public:
  Cannon(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
         qreal y = 0, qreal floor_y_ = 0);
  ~Cannon() override = default;

  void SetUp() override;

  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
  qreal angle_ = 0;
  qreal power_ = 0;
  Vector2D start_vil = {0, 0};
  bool is_caught_ = false;
  bool is_fallen_ = false;
  bool in_flight = true;
  int caught_sausages = 0;
};

#endif  // CANNON_H
