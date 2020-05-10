#ifndef UNICYCLETIGER_H
#define UNICYCLETIGER_H

#include "src/game/gameobject.h"

class UnicycleTiger : public GameObject {
 public:
  UnicycleTiger(GameView* game_view, QSizeF size, QPointF pos);
  ~UnicycleTiger() override = default;

  void SetUp() override;

  void Update() override;
  void Stop();
};

#endif  // UNICYCLETIGER_H
