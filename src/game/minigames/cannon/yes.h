#ifndef YES_H
#define YES_H

#include "src/game/gameobject.h"

class Yes : public GameObject {
 public:
  Yes(GameView* game_view, qreal width, qreal height, qreal x = 0, qreal y = 0);
  ~Yes() override = default;

  void SetUp() override;
};

#endif  // YES_H
