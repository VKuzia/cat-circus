#include "trampoline.h"

Trampoline::Trampoline(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      kPixmapFree_(GetPixmapLoader()->GetPixmap(
          "trampoline/trampoline_free.png", boundingRect().size().toSize())),
      kPixmapPushed_(GetPixmapLoader()->GetPixmap(
          "trampoline/trampoline_pushed.png", boundingRect().size().toSize())) {
}

void Trampoline::SetUp() { setPixmap(kPixmapFree_); }

void Trampoline::SetPushed(bool pushed) {
  if (pushed) {
    setPixmap(kPixmapPushed_);
  } else {
    setPixmap(kPixmapFree_);
  }
}
