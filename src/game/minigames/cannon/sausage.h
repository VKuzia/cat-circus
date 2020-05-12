#ifndef SAUSAGE_H
#define SAUSAGE_H

#include "src/game/gameobject.h"

class Sausage : public GameObject {
 public:
  Sausage(GameView* game_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0);
  ~Sausage() override = default;

  void SetUp() override;
  void Update() override;
  void SetCaught(bool is_caught);
  bool move_down = true;

 private:
  static const qreal kZValue_;

  qreal delta_pos = 0;
  bool is_caught_ = false;
};

#endif  // SAUSAGE_H
