#ifndef PLATEMINIAME_H
#define PLATEMINIAME_H

#include "src/game/gameview.h"
#include "src/game/minigame.h"
#include "src/game/minigames/test/clickableball.h"

class PlateMinigame : public Minigame {
  Q_OBJECT

 public:
  PlateMinigame(GameView* game_view, qreal difficulty,
                qreal pixels_in_meter = 100);
  ~PlateMinigame() override = default;

  void Start() override;

 private:
  const QString kTutorialText_ =
      "Catch all sausages\nby clicking them!\nHurry up!";

  const int32_t kBasicDuration = 5000;
  const int32_t kBasicBallRadius = 1;
  const int32_t kBasicBallNumber = 3;

  // Determines width of centered rectangle relatively
  // scene width in order not to generate circles at the edges
  const qreal kCenterRegionFactor = 0.8;

  int32_t balls_count_ = 0;
  int32_t ball_radius_ = 0;
  int32_t time_left_ = 0;
  ClickableBall* current_ball_ = nullptr;

  void SetUp() override;
  void SetUpParameters() override;

  void AnimateTutorial() override;
  void StartGame() override;

  void Tick() override;
  void AddBall();
  void DeleteBall();
  QPointF GetRandomBallCenter() const;

  void Stop(MinigameStatus) override;
};

#endif  // PLATEMINIAME
