#include "gameview.h"

GameView::GameView(QWidget* parent) : QGraphicsView(parent) {
  this->setScene(new QGraphicsScene(this));
  this->setMouseTracking(false);
}

void GameView::SetUp(int32_t width, int32_t height) {
  this->setFixedSize(width, height);
  this->setRenderHints(QPainter::Antialiasing |
                       QPainter::SmoothPixmapTransform);
  this->scene()->setSceneRect(-width / 2, -height / 2, width, height);
}

void GameView::SetMiniGame(MiniGame* current_minigame) {
  if (current_minigame_ != nullptr) {
    delete current_minigame_;
    current_minigame_ = nullptr;
  }
  current_minigame_ = current_minigame;
}

void GameView::mousePressEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MousePressEvent(event);
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
