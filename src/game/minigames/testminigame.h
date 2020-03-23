#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H
#include "src/game/minigame.h"

class TestMinigame : public MiniGame {
 public:
  TestMinigame(QGraphicsView* render_area, double difficulty_);
};

#endif  // TESTMINIGAME_H
