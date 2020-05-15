#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#include "src/game/gameobject.h"

class Trampoline : public GameObject {
 public:
  Trampoline(GameView* game_view, QSizeF size, QPointF pos);
  ~Trampoline() override = default;

  void SetUp() override;

  void SetPushed(bool pushed);

 private:
  const QPixmap kPixmapFree_;
  const QPixmap kPixmapPushed_;
};

#endif  // TRAMPOLINE_H
