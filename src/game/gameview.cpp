#include "gameview.h"

#include <QKeyEvent>

#include "src/game/minigame.h"

GameView::GameView(QWidget* parent) : QGraphicsView(parent) {
  this->setScene(new QGraphicsScene(this));
}

void GameView::SetUp(QSize resolution) {
  scale_ = 1.0 * resolution.width() / kBasicWidth_;
  this->setFixedSize(resolution);
  this->setRenderHints(QPainter::Antialiasing |
                       QPainter::SmoothPixmapTransform);
  this->setOptimizationFlags(DontSavePainterState);
  this->setCacheMode(CacheBackground);
  this->scene()->setSceneRect(-resolution.width() / 2, -resolution.height() / 2,
                              resolution.width(), resolution.height());
}

void GameView::mousePressEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MousePressEvent(event);
    // To propogate down to items
    QGraphicsView::mousePressEvent(event);
  }
}

void GameView::mouseReleaseEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MouseReleaseEvent(event);
  }
}

void GameView::mouseMoveEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MouseMoveEvent(event);
  }
}

void GameView::keyPressEvent(QKeyEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->KeyPressEvent(event);
  }
}

void GameView::keyReleaseEvent(QKeyEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->KeyReleaseEvent(event);
  }
}

void GameView::wheelEvent(QWheelEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->WheelEvent(event);
  }
}

void GameView::SetMinigame(Minigame* current_minigame) {
  // GameWidget controls deleting, only assignment required
  current_minigame_ = current_minigame;
}

void GameView::SetPixelsInMeter(qreal pixels_in_meter) {
  pixels_in_meter_ = pixels_in_meter * scale_;
}

qreal GameView::GetPixelsInMeter() const { return pixels_in_meter_; }

QString GameView::GetPathToMinigameImages() const {
  return kPathToMinigameImages_;
}
