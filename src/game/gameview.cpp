#include "gameview.h"

GameView::GameView(QWidget* parent) : QGraphicsView(parent) {
  this->setScene(new QGraphicsScene(this));
}

void GameView::SetUp(QSize resolution) {
  this->setFixedSize(resolution.width(), resolution.height());
  this->setRenderHints(QPainter::Antialiasing |
                       QPainter::SmoothPixmapTransform);
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

void GameView::SetMinigame(Minigame* current_minigame) {
  // GameWidget controls deleting, only assignment required
  current_minigame_ = current_minigame;
}
