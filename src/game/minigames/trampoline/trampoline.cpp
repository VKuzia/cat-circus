#include "trampoline.h"

Trampoline::Trampoline(GameView* graphics_view, qreal width, qreal height,
                       qreal x, qreal y)
    : Trampoline(graphics_view, width, height, QPointF(x, y)) {}

Trampoline::Trampoline(GameView* graphics_view, qreal width, qreal height,
                       QPointF pos)
    : GameObject(graphics_view, width, height, pos) {}

void Trampoline::SetUp() {
  int32_t width = qRound(width_ * graphics_view_->GetPixelsInMeter());
  int32_t height = qRound(height_ * graphics_view_->GetPixelsInMeter());
  setOffset(-width / 2, -height / 2);

  pixmap_free_ =
      QPixmap(kPathToMinigameImages + "trampoline/trampoline_free.png");
  pixmap_free_.setMask(pixmap_free_.createHeuristicMask());
  pixmap_free_ = pixmap_free_.scaled(width, height);

  pixmap_pushed_ =
      QPixmap(kPathToMinigameImages + "trampoline/trampoline_pushed.png");
  pixmap_pushed_.setMask(pixmap_pushed_.createHeuristicMask());
  pixmap_pushed_ = pixmap_pushed_.scaled(width, height);
  setPixmap(pixmap_free_);
}

void Trampoline::SetPushed(bool pushed) {
  if (pushed) {
    setPixmap(pixmap_pushed_);
  } else {
    setPixmap(pixmap_free_);
  }
}
