#ifndef UNICYCLECAT_H
#define UNICYCLECAT_H

#include "src/game/gameobject.h"

class UnicycleCat : public GameObject {
 public:
  UnicycleCat(GameView* game_view, QSizeF size, QPointF pos);
  ~UnicycleCat() override = default;

  void SetUp() override;

  void Update() override;

 private:
  Vector2D speed_loss_ = {0.02, 0};
};

#endif  // UNICYCLECAT_H
