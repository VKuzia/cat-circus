#ifndef JUGGLINGMINIGAME_H
#define JUGGLINGMINIGAME_H
#include <QGraphicsEllipseItem>
#include <QSet>

#include "src/game/minigame.h"
#include "src/game/minigames/juggling/jugglingball.h"
#include "src/game/minigames/juggling/jugglingcat.h"

class JugglingMinigame : public Minigame {
  Q_OBJECT

 public:
  JugglingMinigame(GameView* graphics_view, qreal difficulty);
  ~JugglingMinigame() override;

  void Start() override;

  void KeyPressEvent(QKeyEvent* event) override;

 private:
  const qreal kBasicPixelsInMeter = 576 / 5.0;  // To show 5m height

  const qreal kCatWidth = 1.5;
  const qreal kCatHeight = 2.1;
  const qreal kCatY = 1;

  const qreal KTutorialHeight = -1.5;

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  const qreal kBallStartX = 4.6;
  const qreal kBallStartY = 0;
  const qreal kBallRadius = 0.11;
  const qreal kBallLaunchFlightTime = 1.3;

  const qreal kFloorHeight = 2.3;

  int32_t balls_count_ = 0;
  int32_t ball_air_time_ = 0;
  int32_t ball_launch_period_ = 0;
  JugglingCat* cat_ = nullptr;
  QSet<JugglingBall*> balls_;

  QTimer ball_timer_;

  void LaunchBall();

  void SetUp() override;
  void SetLabel() override;
  void SetParameters() override;

  void AnimateTutorial() override;
  void StartGame() override;
  void AnimateOutro() override;

  void Tick() override;

  void Stop(Status) override;
  void Win() override;
  void Lose() override;
};

#endif  // JUGGLINGMINIGAME_H
