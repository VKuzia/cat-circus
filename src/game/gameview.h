#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDir>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPropertyAnimation>

class Minigame;

class GameView : public QGraphicsView {
  Q_OBJECT
  Q_PROPERTY(qreal outroAnimationProgress READ GetOutroAnimationProgress WRITE
                 SetOutroAnimationProgress)

 public:
  enum class OutroStatus { kFailed, kPassed };

  explicit GameView(QWidget* parent = nullptr);
  ~GameView() override = default;

  void SetUp(int32_t width, int32_t height);

  // Should be called inside a current_minigame on win|lose
  // Apply effects to the whole scene, trigger OutroFinished
  void AnimateOutro(OutroStatus status);

  void SetMinigame(Minigame* current_minigame);

  void SetPixelsInMeter(qreal pixels_in_meter);
  qreal GetPixelsInMeter() const;

  QString GetPathToMinigameImages() const;

 signals:
  void OutroFinished();

 private:
  const QString kPathToMinigameImages_ =
      QDir::currentPath() + "/data/images/minigames/";

  const QColor kShadowColor_ = QColor::fromRgb(20, 20, 20);
  const int32_t kOutroAnimationDuration_ = 2200;
  const int32_t kOutroFadeInDuration_ = 300;
  const int32_t kOutroImageShowTime_ = 700;
  const qreal kOutroRectMaxOpacity_ = 0.7;
  // Shows image's width respectively to the width of GameView
  const qreal kOutroImageWidthFactor_ = 0.33;

  const qreal kFailedImageStartYFactor_ = 1;
  const qreal kPassedImageStartYFactor_ = -1;

  QPropertyAnimation outro_animation_;
  Minigame* current_minigame_ = nullptr;
  QGraphicsRectItem* outro_rect_ = nullptr;
  QGraphicsPixmapItem* failed_image_;
  QGraphicsPixmapItem* passed_image_;
  QGraphicsPixmapItem* current_outro_image_ = nullptr;
  qreal failed_image_start_y_ = 0;
  qreal passed_image_start_y_ = 0;
  qreal current_image_start_y_ = 0;
  qreal outro_animation_progress_ = 0;

  qreal pixels_in_meter_ = 0;

  void SetUpOutroRect();
  void SetUpOutroAnimation();

  void SetUpOutroImage(QGraphicsPixmapItem* image, const QString& file_name);

  void SetOutroAnimationProgress(qreal progress);
  qreal GetOutroAnimationProgress() const;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
