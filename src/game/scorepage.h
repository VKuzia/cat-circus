#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QDir>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMovie>
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
  const int32_t kExpireTime = 2500;
  const int32_t kScoreAnimationTime = 800;
  const int32_t kResumeTime = 1500;
  const int32_t kLivesCount = 3;

  // Ratio of life height relatively ui_lives_view_ height
  const qreal kLiveScaleYFactor = 0.9;
  const qreal kLiveScaleXFactor = 0.2;
  // Ratio of horizontal space between lives relatively life_width_
  const qreal kLifeIntervalXFactor = 0.3;
  // Disappear animation speed in percents
  const int32_t kLifeDisappearSpeed = 150;

  int32_t score_ = 0;
  QPropertyAnimation score_animation_;

  int32_t remaining_lives_ = kLivesCount;
  QSize life_size_;

  QGraphicsScene* lives_scene_;
  Ui::ScorePage* ui_;
  QVector<QGraphicsPixmapItem*> lives_;
  QMovie life_movie_;
  QMovie life_disappear_movie_;

  QTimer expire_timer_;
  bool is_minigame_passed_ = false;
  bool is_life_disappearing_ = false;

  void SetUpLives();
  QGraphicsPixmapItem* GetNewLife(int32_t index) const;
  void RemoveLife();

  void SetUpAnimations();

  void SetScore(int32_t score);
  int32_t GetScore() const;
};

#endif  // POINTSPAGE_H
