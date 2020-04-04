#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "src/game/minigame.h"

class TestMiniGame : public MiniGame {
  Q_OBJECT

 public:
  TestMiniGame(QGraphicsView* graphics_view, qreal difficulty);
  ~TestMiniGame() override;

  void Start() override;

  void MousePressEvent(QMouseEvent* event) override;
  void MouseReleaseEvent(QMouseEvent* event) override;
  void MouseMoveEvent(QMouseEvent* event) override;
  void KeyPressEvent(QKeyEvent* event) override;
  void KeyReleaseEvent(QKeyEvent* event) override;

 signals:

 public slots:

 private:
  const int32_t kBasicDuration = 5000;
  const int32_t kBasicBallRadius = 100;
  const int32_t kBasicBallNumber = 3;

  int32_t balls_count_;
  int32_t ball_raduis_;

  void Tick() override;
  void AddBall();

  void Stop() override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
