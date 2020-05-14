#ifndef CANNON_H
#define CANNON_H

#include "src/game/gameobject.h"
#include "src/game/minigames/cannon/cannoncat.h"

class Cannon : public GameObject {
 public:
  Cannon(GameView* game_view, qreal width, qreal height, qreal x = 0,
         qreal y = 0);
  ~Cannon() override = default;

  void SetUp() override;
};

#endif  // CANNON_H
