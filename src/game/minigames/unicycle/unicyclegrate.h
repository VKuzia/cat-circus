#ifndef UNICYCLEGRATE_H
#define UNICYCLEGRATE_H

#include "src/game/gameobject.h"

class UnicycleGrate : public GameObject {
 public:
  UnicycleGrate(GameView* game_view, QSizeF size, QPointF pos);
  ~UnicycleGrate() override = default;

  void SetUp() override;

  void Close();
};

#endif  // UNICYCLEGRATE_H
