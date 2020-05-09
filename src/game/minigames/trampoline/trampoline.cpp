#include "trampoline.h"

Trampoline::Trampoline(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

void Trampoline::SetUp() {
  pixmap_free_ = GetPixmapFrom("trampoline/trampoline_free.png");
  pixmap_pushed_ = GetPixmapFrom("trampoline/trampoline_pushed.png");
  setPixmap(pixmap_free_);
}

void Trampoline::SetPushed(bool pushed) {
  if (pushed) {
    setPixmap(pixmap_pushed_);
  } else {
    setPixmap(pixmap_free_);
  }
}
