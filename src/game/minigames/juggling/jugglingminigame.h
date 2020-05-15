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
  JugglingMinigame(GameView* game_view, qreal difficulty,
                   qreal pixels_in_meter = 576 / 5.0);
  ~JugglingMinigame() override = default;

  void Start() override;

  void KeyPressEvent(QKeyEvent* event) override;

  const QSizeF kCatSize = {1.5, 2.1};
  const QPointF kCatPos = {0, 1};

  const qreal KTutorialHeight = -1.5;

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  const QPointF kBallStartPos = {4.6, 0};
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
  void SetUpLabel() override;
  void SetUpParameters() override;

  void AnimateTutorial() override;
  void StartGame() override;

  void Tick() override;

  void Stop(Status) override;
};

#endif  // JUGGLINGMINIGAME_H
