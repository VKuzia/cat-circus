#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#include "src/game/gameobject.h"

class Trampoline : public GameObject {
 public:
  Trampoline(GameView* game_view, qreal width, qreal height, qreal x = 0,
             qreal y = 0);
  Trampoline(GameView* game_view, qreal width, qreal height, QPointF pos);
  ~Trampoline() override = default;

  void SetUp() override;

  void SetPushed(bool pushed);

 private:
  QPixmap pixmap_free_;
  QPixmap pixmap_pushed_;
};

#endif  // TRAMPOLINE_H
