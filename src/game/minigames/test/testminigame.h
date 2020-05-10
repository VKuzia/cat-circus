#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "src/game/gameview.h"
#include "src/game/minigame.h"
#include "src/game/minigames/test/clickableball.h"

class TestMinigame : public Minigame {
  Q_OBJECT

 public:
  TestMinigame(GameView* game_view, qreal difficulty,
               qreal pixels_in_meter = 100);
  ~TestMinigame() override = default;

  void Start() override;

  void MousePressEvent(QMouseEvent* event) override;
  void MouseReleaseEvent(QMouseEvent* event) override;
  void KeyPressEvent(QKeyEvent* event) override;
  void KeyReleaseEvent(QKeyEvent* event) override;

 private:
  const qreal kPixelsInMeter = 576 / 5;
  const int32_t kBasicDuration = 5000;
  const int32_t kBasicBallRadius = 1;
  const int32_t kBasicBallNumber = 3;

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kSimpleBackgroundBrush = QBrush(QColor::fromRgb(224, 107, 22));
  const QBrush kMousePressedBackgroundBrush =
      QBrush(QColor::fromRgb(200, 0, 0));
  const QBrush kKeyPressedBackgroundBrush = QBrush(QColor::fromRgb(0, 0, 200));
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  // Determines width of centered rectangle relatively
  // scene width in order not to generate circles at the edges
  const qreal kCenterRegionFactor = 0.8;

  int32_t balls_count_ = 0;
  int32_t ball_radius_ = 0;
  int32_t time_left_ = 0;
  ClickableBall* current_ball_ = nullptr;

  void SetUp() override;
  void SetUpLabel() override;
  void SetUpParameters() override;
  void AnimateTutorial() override;
  void StartGame() override;

  void Tick() override;
  void AddBall();
  void DeleteBall();
  QPointF GetRandomBallCenter() const;

  void Stop(Status) override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
