#ifndef SAUSAGE_H
#define SAUSAGE_H

#include "src/game/gameobject.h"

class Sausage : public GameObject {
 public:
  Sausage(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0, qreal floor_y_ = 0);
  ~Sausage() override;
  void SetUp() override;

  void Update() override;

  void SetCaught(bool is_caught);
  qreal GetRadius() const;

  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
  qreal delta_pos = 0;
  bool move_down = true;
  bool is_caught_ = false;
};

#endif  // SAUSAGE_H
