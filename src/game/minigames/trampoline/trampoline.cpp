#include "trampoline.h"

Trampoline::Trampoline(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      kPixmapFree_(LoadPixmap("trampoline/trampoline_free.png")),
      kPixmapPushed_(LoadPixmap("trampoline/trampoline_pushed.png")) {}

void Trampoline::SetUp() { setPixmap(kPixmapFree_); }

void Trampoline::SetPushed(bool pushed) {
  if (pushed) {
    setPixmap(kPixmapPushed_);
  } else {
    setPixmap(kPixmapFree_);
  }
}
