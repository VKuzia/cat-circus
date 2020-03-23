#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H
#include "src/game/minigame.h"

class TestMinigame : public MiniGame {
 public:
  TestMinigame(QGraphicsView* render_area, double difficulty_ = 0.1);
};

#endif  // TESTMINIGAME_H
