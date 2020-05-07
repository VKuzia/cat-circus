#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDir>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPropertyAnimation>

class Minigame;

class GameView : public QGraphicsView {
  Q_OBJECT
  Q_PROPERTY(qreal failedAnimationProgress READ GetFailedAnimationProgress WRITE
                 SetFailedAnimationProgress)
  Q_PROPERTY(qreal passedAnimationProgress READ GetPassedAnimationProgress WRITE
                 SetPassedAnimationProgress)

 public:
  explicit GameView(QWidget* parent = nullptr);
  ~GameView() override = default;

  void SetUp(int32_t width, int32_t height);

  // Should be called inside a current_minigame on win|lose;
  // apply effects to the whole scene, trigger OutroFinished
  void AnimatePassed();
  void AnimateFailed();

  void SetMinigame(Minigame* current_minigame);

  void SetPixelsInMeter(qreal pixels_in_meter);
  qreal GetPixelsInMeter() const;

  QString GetPathToMinigameImages() const;

 signals:
  void OutroFinished();

 private:
  const QString kPathToMinigameImages_ =
      QDir::currentPath() + "/data/images/minigames/";
  const QColor kShadowColor = QColor::fromRgb(20, 20, 20);
  const int32_t kPassedAnimationDuration = 2200;
  const int32_t kPassedFadeInDuration = 300;
  const int32_t kPassedImageShowTime = 700;
  const qreal kPassedMaxOpacity = 0.6;
  // Shows image's width respectively to the width of GameView
  const qreal kPassedImageWidthFactor = 0.33;

  const int32_t kFailedAnimationDuration = 2200;
  const int32_t kFailedFadeInDuration = 700;
  const qreal kFailedMaxOpacity = 0.8;
  const qreal kFailedImageWidthFactor = 0.33;
  // Shows image animation start point respectively to
  // the height of active GameView
  const qreal kFailedImageStartYFactor = 1.5;

  QPropertyAnimation failed_animation_;
  QPropertyAnimation passed_animation_;
  Minigame* current_minigame_ = nullptr;
  QGraphicsRectItem* outro_rect_ = nullptr;
  QGraphicsPixmapItem* failed_image_ = nullptr;
  QGraphicsPixmapItem* passed_image_ = nullptr;
  qreal failed_image_start_y_ = 0;
  qreal failed_animation_progress_ = 0;
  qreal passed_animation_progress_ = 0;
  qreal pixels_in_meter_ = 0;

  void SetUpOutroRect();
  void SetUpPassedAnimation();
  void SetUpFailedAnimation();

  void SetPassedAnimationProgress(qreal progress);
  qreal GetPassedAnimationProgress() const;

  void SetFailedAnimationProgress(qreal progress);
  qreal GetFailedAnimationProgress() const;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
