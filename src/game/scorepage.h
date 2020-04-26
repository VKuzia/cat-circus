#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>

namespace Ui {
class ScorePage;
}

class ScorePage : public QWidget {
  Q_OBJECT
  Q_PROPERTY(int score READ GetScore WRITE SetScore)

 public:
  explicit ScorePage(QWidget* parent = nullptr);
  ~ScorePage() override;

  void SetUp();
  void Animate();

  void MiniGamePassed(int32_t score);
  void MiniGameFailed();

  int32_t GetLivesCount() const;

 signals:
  void Expired();
  void Paused();
  void MainMenu();
  void Retried();

 public slots:
  void Pause();
  void Resume();
  void Retry();
  void ReturnToMainMenu();

 private:
  const QColor kActiveLifeColor = QColor::fromRgb(10, 230, 10, 200);
  const QColor kInactiveLifeColor = QColor::fromRgb(230, 10, 10, 200);

  const int32_t kExpireTime = 2500;
  const int32_t kScoreAnimationTime = 800;
  const int32_t kResumeTime = 1500;
  const int32_t kLifeInterval = 20;
  const int32_t kBasicLivesCount = 3;

  // Ratio of live height to lives_scene_ height;
  // Temporary parameter for lives appearance
  const qreal kLiveHeightFactor = 0.9;

  int32_t score_ = 0;
  int32_t lives_count_ = kBasicLivesCount;

  QGraphicsScene* lives_scene_;
  Ui::ScorePage* ui_;
  QVector<QGraphicsEllipseItem*> lives_;
  QPropertyAnimation score_animation_;
  QTimer expire_timer_;

  void SetUpLives();
  QGraphicsEllipseItem* GetNewLife(int32_t index) const;
  void RemoveLife();

  void SetScore(int32_t score);
  int32_t GetScore() const;
};

#endif  // POINTSPAGE_H
