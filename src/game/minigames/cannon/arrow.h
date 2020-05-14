#ifndef ARROW_H
#define ARROW_H

#include "src/game/gameobject.h"

class Arrow : public GameObject {
 public:
  Arrow(GameView* game_view, qreal width, qreal height, qreal x = 0,
        qreal y = 0);
  ~Arrow() = default;

  void SetUp() override;
};
#endif  // ARROW_H
