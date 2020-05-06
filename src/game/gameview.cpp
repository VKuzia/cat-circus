#include "gameview.h"

#include <QKeyEvent>

#include "src/game/minigame.h"

GameView::GameView(QWidget* parent) : QGraphicsView(parent) {
  this->setScene(new QGraphicsScene(this));
}

void GameView::SetUp(int32_t width, int32_t height) {
  this->setFixedSize(width, height);
  this->setRenderHints(QPainter::Antialiasing |
                       QPainter::SmoothPixmapTransform);
  this->setOptimizationFlags(DontSavePainterState);
  this->setCacheMode(CacheBackground);
  this->scene()->setSceneRect(-width / 2, -height / 2, width, height);
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

void GameView::SetMinigame(Minigame* current_minigame) {
  // GameWidget controls deleting, only assignment required
  current_minigame_ = current_minigame;
}

void GameView::SetPixelsInMeter(qreal pixels_in_meter) {
  pixels_in_meter_ = pixels_in_meter;
}

qreal GameView::GetPixelsInMeter() const { return pixels_in_meter_; }

QString GameView::GetPathToMinigameImages() const {
  return kPathToMinigameImages_;
}
