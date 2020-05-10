#ifndef NO_H
#define NO_H

#include "src/game/gameobject.h"

class No : public GameObject {
 public:
  No(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
     qreal y = 0, qreal floor_y_ = 0);
  ~No() override;
  void SetUp() override;

  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
};

#endif  // NO_H
