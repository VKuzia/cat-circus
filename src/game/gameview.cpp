#include "gameview.h"

#include <QDir>
#include <QPixmap>
#include <limits>

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

  failed_animation_.setPropertyName("failedAnimationProgress");
  failed_animation_.setTargetObject(this);
  failed_animation_.setDuration(kFailedAnimationDuration);
  failed_animation_.setStartValue(0);
  failed_animation_.setKeyValueAt(
      (1.0 * kFailedFadeInDuration) / kFailedAnimationDuration, 1);
  failed_animation_.setEndValue(1);
  connect(&failed_animation_, &QPropertyAnimation::finished, this, [this] {
    failed_rect_->setVisible(false);
    failed_rect_->setOpacity(0);
    scene()->removeItem(failed_rect_);
    scene()->removeItem(failed_image_);
    emit OutroFinished();
  });

  failed_rect_ =
      new QGraphicsRectItem(-this->width() / 2 + 1, -this->height() / 2 + 1,
                            this->width() + 2, this->height() + 2);
  failed_rect_->setVisible(false);
  failed_rect_->setOpacity(0);
  failed_rect_->setZValue(std::numeric_limits<qreal>::max() - 1);
  failed_rect_->setPen(Qt::NoPen);
  failed_rect_->setBrush(kFailedShadowColor);

  QPixmap failed_pixmap(QDir::currentPath() +
                        "/data/images/gameview/failed.png");
  failed_pixmap = failed_pixmap.scaledToWidth(
      qRound(this->width() * kFailedImageWidthFactor));

  failed_image_ = new QGraphicsPixmapItem(failed_pixmap);
  failed_image_->setVisible(false);
  failed_image_->setOffset(-failed_pixmap.width() / 2,
                           -failed_pixmap.height() / 2);
  failed_image_->setZValue(std::numeric_limits<qreal>::max());
  failed_image_start_y_ = this->height() * kFailedImageStartYFactor;
}

void GameView::AnimateFailed() {
  failed_rect_->setVisible(true);
  failed_rect_->setOpacity(0);
  scene()->addItem(failed_rect_);
  failed_image_->setVisible(true);
  scene()->addItem(failed_image_);
  failed_animation_.start();
}

void GameView::SetFailedAnimationProgress(qreal progress) {
  failed_animation_progress_ = progress;
  failed_rect_->setOpacity(kFailedMaxOpacity * failed_animation_progress_);
  failed_image_->setY(failed_image_start_y_ * (1 - progress));
}

qreal GameView::GetFaildedAnimationProgress() const {
  return failed_animation_progress_;
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
