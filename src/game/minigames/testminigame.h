#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "src/game/minigame.h"

class TestMinigame : public Minigame {
  Q_OBJECT

 public:
  TestMinigame(QGraphicsView* graphics_view, float difficulty);
  ~TestMinigame() override;

  void Start() override;

  void MousePressEvent(QMouseEvent* event) override;
  void MouseReleaseEvent(QMouseEvent* event) override;
  void MouseMoveEvent(QMouseEvent* event) override;
  void KeyPressEvent(QKeyEvent* event) override;
  void KeyReleaseEvent(QKeyEvent* event) override;

 private:
  const int32_t kBasicDuration = 5000;
  const int32_t kBasicBallRadius = 100;
  const int32_t kBasicBallNumber = 3;

  int32_t balls_count_;
  int32_t ball_radius_;

  void AnimateTutorial() override;
  void StartGame() override;
  void AnimateOutro() override;

  void Tick() override;
  void AddBall();

  void Stop() override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
