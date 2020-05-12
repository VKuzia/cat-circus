#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "src/game/gameobject.h"

class Speedometer : public GameObject {
 public:
  Speedometer(GameView* game_view, qreal width, qreal height, qreal x = 0,
              qreal y = 0);
  ~Speedometer() override = default;

  void SetUp() override;

 private:
  static const qreal kZValue_;
};

#endif  // SPEEDOMETER_H
