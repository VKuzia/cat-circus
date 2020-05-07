#ifndef YES_H
#define YES_H

#include "src/game/gameobject.h"

class Yes : public GameObject {
 public:
  Yes(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
      qreal y = 0, qreal floor_y_ = 0);
  ~Yes() override;
  void SetUp() override;

 private:
  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
  qreal angle_ = 0;
  qreal power_ = 0;
  Vector2D start_vil = {0, 0};
  bool is_caught_ = false;
  bool is_fallen_ = false;
  bool in_flight = true;
  int caught_sausages = 0;
};

#endif  // YES_H
