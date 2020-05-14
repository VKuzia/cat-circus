#ifndef NO_H
#define NO_H

#include "src/game/gameobject.h"

class No : public GameObject {
 public:
  No(GameView* game_view, qreal width, qreal height, qreal x = 0, qreal y = 0);
  ~No() override = default;

  void SetUp() override;
};

#endif  // NO_H
