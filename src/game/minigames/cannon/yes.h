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
  int caught_sausages = 0;
};

#endif  // YES_H
