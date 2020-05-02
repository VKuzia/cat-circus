#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPropertyAnimation>

class Minigame;

class GameView : public QGraphicsView {
  Q_OBJECT
  Q_PROPERTY(qreal failedAnimationProgress READ GetFaildedAnimationProgress
                 WRITE SetFailedAnimationProgress)

 public:
  explicit GameView(QWidget* parent = nullptr);
  ~GameView() override = default;

  void SetUp(int32_t width, int32_t height);

  void AnimateFailed();

  void SetMinigame(Minigame* current_minigame);

  void SetPixelsInMeter(qreal pixels_in_meter);
  qreal GetPixelsInMeter() const;

 signals:
  void OutroFinished();

 private:
  const QColor kFailedShadowColor = QColor::fromRgb(20, 20, 20);
  const int32_t kFailedAnimationDuration = 2500;
  const int32_t kFailedFadeInDuration = 500;
  const qreal kFailedMaxBlurRadius = 15;
  const qreal kFailedMaxOpacity = 0.8;
  const qreal kFailedImageWidthFactor = 0.33;
  const qreal kFailedImageStartYFactor = 1.5;

  Minigame* current_minigame_ = nullptr;
  QPropertyAnimation failed_animation_;
  QGraphicsRectItem* failed_rect_ = nullptr;
  QGraphicsPixmapItem* failed_image_ = nullptr;
  qreal failed_image_start_y_ = 0;
  qreal failed_animation_progress_ = 0;
  qreal pixels_in_meter_ = 0;

  void SetFailedAnimationProgress(qreal progress);
  qreal GetFaildedAnimationProgress() const;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
