#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "src/game/gameobject.h"

class Speedometer : public GameObject {
 public:
  Speedometer(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
              qreal y = 0, qreal floor_y_ = 0);
  ~Speedometer() override;
  void SetUp() override;

  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
};

#endif  // SPEEDOMETER_H
