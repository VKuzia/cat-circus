#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QTimer>
#include <QWidget>

namespace Ui {
class PointsPage;
}

class PointsPage : public QWidget {
  Q_OBJECT

 public:
  explicit PointsPage(QWidget* parent = nullptr);

  void SetUp();
  void Animate();

  void MiniGamePassed(int64_t score);
  void MiniGameFailed();

 signals:
  void Expired();
  void Paused();
  void MainMenu();
  void Retryed();

 public slots:
  void Pause();
  void Resume();
  void Retry();

 private:
  const int32_t kExpireTime = 2500;
  const int32_t kResumeTime = 1500;
  const int32_t kLiveInterval = 20;
  const int32_t kBasicLivesCount = 3;

  int32_t points_ = 0;
  int32_t lives_count_ = kBasicLivesCount;
  Ui::PointsPage* ui_;
  QTimer* expire_timer_;

  void SetUpLives();
  void UpdateLive(int32_t live_num);
};

#endif  // POINTSPAGE_H
