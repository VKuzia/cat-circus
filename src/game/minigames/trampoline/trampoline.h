#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#include "src/game/gameobject.h"

class Trampoline : public GameObject {
 public:
  Trampoline(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
             qreal y = 0);
  Trampoline(GameView* graphics_view, qreal width, qreal height, QPointF pos);
  ~Trampoline() override = default;

  void SetUp() override;
};

#endif  // TRAMPOLINE_H
