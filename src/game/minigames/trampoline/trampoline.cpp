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

  QPixmap pixmap(width, height);
  QPainter painter(&pixmap);
  painter.setBrush(QColor::fromRgb(20, 40, 200));
  painter.drawRect(0, 0, width, height);
  setOffset(-width / 2, -height / 2);
  setPixmap(pixmap.scaled(width, height));
}
