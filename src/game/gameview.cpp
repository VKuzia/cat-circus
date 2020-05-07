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
  this->setViewportUpdateMode(ViewportUpdateMode::MinimalViewportUpdate);
  scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
  this->scene()->setSceneRect(-width / 2, -height / 2, width, height);

  SetUpOutroRect();
  SetUpPassedAnimation();
  SetUpFailedAnimation();
}

void GameView::AnimatePassed() {
  outro_rect_->setVisible(true);
  outro_rect_->setOpacity(0);
  scene()->addItem(outro_rect_);
  passed_image_->setVisible(false);
  scene()->addItem(passed_image_);
  passed_animation_.start();
}

void GameView::AnimateFailed() {
  outro_rect_->setVisible(true);
  outro_rect_->setOpacity(0);
  scene()->addItem(outro_rect_);
  failed_image_->setVisible(true);
  scene()->addItem(failed_image_);
  failed_animation_.start();
}

void GameView::SetFailedAnimationProgress(qreal progress) {
  failed_animation_progress_ = progress;
  outro_rect_->setOpacity(kFailedMaxOpacity * failed_animation_progress_);
  // Moving up to (0, 0)
  failed_image_->setY(failed_image_start_y_ * (1 - progress));
}

qreal GameView::GetFailedAnimationProgress() const {
  return failed_animation_progress_;
}

void GameView::SetPassedAnimationProgress(qreal progress) {
  passed_animation_progress_ = progress;
  outro_rect_->setOpacity((kPassedMaxOpacity * passed_animation_progress_));
  if (passed_animation_.currentTime() >= kPassedImageShowTime &&
      !passed_image_->isVisible()) {
    passed_image_->setVisible(true);
  }
}

qreal GameView::GetPassedAnimationProgress() const {
  return passed_animation_progress_;
}

void GameView::SetUpPassedAnimation() {
  passed_animation_.setPropertyName("passedAnimationProgress");
  passed_animation_.setTargetObject(this);
  passed_animation_.setDuration(kPassedAnimationDuration);
  passed_animation_.setStartValue(0);
  // Stay an kPassedMaxOpacity when fading in ends
  passed_animation_.setKeyValueAt(
      (1.0 * kPassedFadeInDuration) / kPassedAnimationDuration, 1);
  passed_animation_.setEndValue(1);
  connect(&passed_animation_, &QPropertyAnimation::finished, this, [this] {
    outro_rect_->setVisible(false);
    passed_image_->setVisible(false);
    outro_rect_->setOpacity(0);
    // To keep undeleted when scene clears up in Minigame's destructor
    scene()->removeItem(outro_rect_);
    scene()->removeItem(passed_image_);
    emit OutroFinished();
  });

  QPixmap passed_pixmap(QDir::currentPath() +
                        "/data/images/gameview/passed.png");
  passed_pixmap = passed_pixmap.scaledToWidth(
      qRound(this->width() * kFailedImageWidthFactor));

  passed_image_ = new QGraphicsPixmapItem(passed_pixmap);
  passed_image_->setVisible(false);
  passed_image_->setOffset(-passed_pixmap.width() / 2,
                           -passed_pixmap.height() / 2);
  passed_image_->setZValue(std::numeric_limits<qreal>::max());
  passed_image_->setPos(0, 0);
}

void GameView::SetUpFailedAnimation() {
  failed_animation_.setPropertyName("failedAnimationProgress");
  failed_animation_.setTargetObject(this);
  failed_animation_.setDuration(kFailedAnimationDuration);
  failed_animation_.setStartValue(0);
  // Stay an kFailedMaxOpacity when fading in ends
  failed_animation_.setKeyValueAt(
      (1.0 * kFailedFadeInDuration) / kFailedAnimationDuration, 1);
  failed_animation_.setEndValue(1);
  connect(&failed_animation_, &QPropertyAnimation::finished, this, [this] {
    outro_rect_->setVisible(false);
    outro_rect_->setOpacity(0);
    scene()->removeItem(outro_rect_);
    scene()->removeItem(failed_image_);
    emit OutroFinished();
  });

  QPixmap failed_pixmap(QDir::currentPath() +
                        "/data/images/gameview/failed.png");
  failed_pixmap = failed_pixmap.scaledToWidth(
      qRound(this->width() * kFailedImageWidthFactor));

  failed_image_ = new QGraphicsPixmapItem(failed_pixmap);
  failed_image_->setVisible(false);
  failed_image_->setOffset(-failed_pixmap.width() / 2,
                           -failed_pixmap.height() / 2);
  failed_image_->setZValue(std::numeric_limits<qreal>::max());
  // Set position below the screen to animate moving up
  failed_image_start_y_ = this->height() * kFailedImageStartYFactor;
}

void GameView::SetUpOutroRect() {
  outro_rect_ =
      new QGraphicsRectItem(-this->width() / 2 + 1, -this->height() / 2 + 1,
                            this->width() + 2, this->height() + 2);
  outro_rect_->setVisible(false);
  outro_rect_->setOpacity(0);
  // Set "almost maximum" to set maximum for images (to be opaque)
  outro_rect_->setZValue(std::numeric_limits<qreal>::max() - 1);
  outro_rect_->setPen(Qt::NoPen);
  outro_rect_->setBrush(kShadowColor);
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
