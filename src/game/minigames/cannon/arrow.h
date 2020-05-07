#ifndef ARROW_H
#define ARROW_H
#include "src/game/gameobject.h"

class Arrow : public GameObject {
 public:
  Arrow(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
        qreal y = 0, qreal floor_y_ = 0);
  ~Arrow() override;
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
#endif  // ARROW_H
