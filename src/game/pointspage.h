#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QWidget>

namespace Ui {
class PointsPage;
}

class PointsPage : public QWidget {
  Q_OBJECT

 public:
  explicit PointsPage(QWidget* parent = nullptr);
  ~PointsPage() override;

  void SetUp();
  void Animate();

  void MiniGamePassed(int64_t score);
  void MiniGameFailed();

 signals:
  void Expired();
  void Paused();
  void MainMenu();
  void Retried();

 public slots:
  void Pause();
  void Resume();
  void Retry();

 private:
  const QColor kActiveLiveColor = QColor::fromRgb(10, 230, 10, 200);
  const QColor kInactiveLiveColor = QColor::fromRgb(230, 10, 10, 200);

  const int32_t kExpireTime = 2500;
  const int32_t kResumeTime = 1500;
  const int32_t kLiveInterval = 20;
  const int32_t kBasicLivesCount = 3;

  // Ratio of live height to lives_scene_ height;
  // Temporary parameter for lives appearance
  const float kLiveHeightFactor = 0.9f;

  int32_t points_ = 0;
  int32_t lives_count_ = kBasicLivesCount;

  QGraphicsScene* lives_scene_;
  Ui::PointsPage* ui_;
  QVector<QGraphicsEllipseItem*> lives_;
  QTimer expire_timer_;

  void SetUpLives();
  QGraphicsEllipseItem* GetNewLive(int32_t number) const;
  void RemoveLive();
};

#endif  // POINTSPAGE_H
