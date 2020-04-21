#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "src/game/game_objects/clickableball.h"
#include "src/game/minigame.h"

class TestMinigame : public Minigame {
  Q_OBJECT

 public:
  TestMinigame(QGraphicsView* graphics_view, float difficulty);
  ~TestMinigame() override;

  void SetUp() override;

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

  // Determines width of centered rectangle relatively
  // scene width in order not to generate circles at the edges
  const double kCenterRegionFactor = 0.8;

  int32_t balls_count_ = 0;
  int32_t ball_radius_ = 0;
  int32_t time_left_ = 0;
  ClickableBall* current_ball_ = nullptr;

  void AnimateTutorial() override;
  void StartGame() override;
  void AnimateOutro() override;

  void Tick() override;
  void AddBall();
  void DeleteBall();
  QPointF GetRandomBallCenter() const;

  void Stop() override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
