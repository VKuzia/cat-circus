#include "gameview.h"

#include <QDir>
#include <QPixmap>
#include <limits>

#include "src/game/minigame.h"

GameView::GameView(QWidget* parent)
    : QGraphicsView(parent),
      failed_image_(new QGraphicsPixmapItem()),
      passed_image_(new QGraphicsPixmapItem()) {
  this->setScene(new QGraphicsScene(this));
}

void GameView::SetUp(int32_t width, int32_t height) {
  this->setFixedSize(width, height);
  this->setLineWidth(0);
  this->setRenderHints(QPainter::Antialiasing |
                       QPainter::SmoothPixmapTransform);
  this->setOptimizationFlags(DontSavePainterState);
  this->setCacheMode(CacheBackground);
  this->setViewportUpdateMode(ViewportUpdateMode::MinimalViewportUpdate);
  scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
  this->scene()->setSceneRect(-width / 2, -height / 2, width, height);

  SetUpOutroRect();
  SetUpOutroAnimation();
  SetUpOutroImage(failed_image_, "failed.png");
  failed_image_start_y_ = this->height() * kFailedImageStartYFactor_;
  SetUpOutroImage(passed_image_, "passed.png");
  passed_image_start_y_ = this->height() * kPassedImageStartYFactor_;
}

void GameView::AnimateOutro(Status status) {
  minigame_status_ = status;
  outro_rect_->setVisible(true);
  outro_rect_->setOpacity(0);
  scene()->addItem(outro_rect_);
  switch (status) {
    case Status::kFailed:
      current_outro_image_ = failed_image_;
      current_image_start_y_ = failed_image_start_y_;
      break;
    case Status::kPassed:
      current_outro_image_ = passed_image_;
      current_image_start_y_ = passed_image_start_y_;
      break;
  }
  scene()->addItem(current_outro_image_);
  current_outro_image_->setVisible(true);
  outro_animation_.start();
}

void GameView::SetOutroAnimationProgress(qreal progress) {
  outro_animation_progress_ = progress;
  outro_rect_->setOpacity(kOutroRectMaxOpacity_ * outro_animation_progress_);
  // Moving to (0, 0)
  current_outro_image_->setY(current_image_start_y_ * (1 - progress));
}

qreal GameView::GetOutroAnimationProgress() const {
  return outro_animation_progress_;
}

void GameView::SetUpOutroAnimation() {
  outro_animation_.setPropertyName("outroAnimationProgress");
  outro_animation_.setTargetObject(this);
  outro_animation_.setDuration(kOutroAnimationDuration_);
  outro_animation_.setStartValue(0);
  // Stay at kOutroMaxOpacity_ when fading in ends
  outro_animation_.setKeyValueAt(
      (1.0 * kOutroFadeInDuration_) / kOutroAnimationDuration_, 1);
  outro_animation_.setEndValue(1);
  connect(&outro_animation_, &QPropertyAnimation::finished, this, [this] {
    outro_rect_->setVisible(false);
    outro_rect_->setOpacity(0);
    // To save them from scene()->clean() in Minigame destructor
    scene()->removeItem(outro_rect_);
    scene()->removeItem(current_outro_image_);
    switch (minigame_status_) {
      case Status::kFailed:
        emit MinigameFailed();
        break;
      case Status::kPassed:
        emit MinigamePassed(current_minigame_->GetScore());
        break;
    }
  });
}

void GameView::SetUpOutroImage(QGraphicsPixmapItem* image,
                               const QString& file_name) {
  QPixmap pixmap(QDir::currentPath() + "/data/images/gameview/" + file_name);
  pixmap =
      pixmap.scaledToWidth(qRound(this->width() * kOutroImageWidthFactor_));
  image->setPixmap(pixmap);
  image->setOffset(-pixmap.rect().center());
  image->setZValue(std::numeric_limits<qreal>::max());
  image->setVisible(false);
}

void GameView::SetUpOutroRect() {
  // QPainter draws rectangles with strange borders,
  // so we extend rect by a couple of pixels
  outro_rect_ =
      new QGraphicsRectItem(-this->width() / 2 - 1, -this->height() / 2 - 1,
                            this->width() + 2, this->height() + 2);
  outro_rect_->setVisible(false);
  outro_rect_->setOpacity(0);
  // Set "almost maximum" to set maximum for images (to be them totaly opaque)
  outro_rect_->setZValue(std::numeric_limits<qreal>::max() - 1);
  outro_rect_->setPen(Qt::NoPen);
  outro_rect_->setBrush(kShadowColor_);
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
