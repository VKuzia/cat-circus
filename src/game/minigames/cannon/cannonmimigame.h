#ifndef CANNONMIMIGAME_H
#define CANNONMIMIGAME_H
#include <QGraphicsEllipseItem>
#include <QProgressBar>
#include <QRandomGenerator>
#include <QSet>

#include "src/game/minigame.h"
#include "src/game/minigames/cannon/arrow.h"
#include "src/game/minigames/cannon/cannon.h"
#include "src/game/minigames/cannon/cannoncat.h"
#include "src/game/minigames/cannon/no.h"
#include "src/game/minigames/cannon/sausage.h"
#include "src/game/minigames/cannon/speedometer.h"
#include "src/game/minigames/cannon/yes.h"

class Cannonmimigame : public Minigame {
  Q_OBJECT

 public:
  Cannonmimigame(GameView* game_view, qreal difficulty,
                 qreal pixels_in_meter = 576 / 10.0);
  ~Cannonmimigame() override;

  void Start() override;

  void KeyPressEvent(QKeyEvent* event) override;

  const qreal kCatWidth = 1.5;
  const qreal kCatHeight = 2.1;
  const qreal kCatY = 3;

  const qreal KTutorialHeight = -1.5;

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  const qreal kCatStartX = 4.6;
  const qreal kCatStartY = 0;
  const qreal kCatRadius = 0.11;
  const qreal kCatLaunchFlightTime = 1.3;

  const qreal KSausageRadius = 0.6;

  const qreal kFloorHeight = 3.2;

  qreal sausage_a_param = 0;
  qreal sausage_b_param = 0;

  qreal angle_ = M_PI / 2;
  qreal power_ = 0;
  bool angle_increases_ = true;
  bool power_increases_ = true;
  bool cat_flight = false;
  bool params_choosen_angle_ = false;
  bool params_choosen_power_ = false;

  int32_t sausage_count_ = 0;
  int32_t ball_air_time_ = 0;
  int32_t sausage_launch_period_ = 0;
  int32_t number_to_win_ = 0;
  Cannon* cannon_ = nullptr;
  Cannoncat* cat_ = nullptr;

  Speedometer* speedometer_ = nullptr;

  Arrow* arrow_ = nullptr;

  QSet<Sausage*> sausages_;

  QSet<No*> not_caught_;
  QSet<Yes*> caught_;

  QTimer ball_timer_;

  void LaunchSausage();

  void SetUp() override;
  void SetUpLabel() override;
  void SetUpParameters() override;

  void AnimateTutorial() override;
  void StartGame() override;
  void AnimateOutro() override;

  void Tick() override;

  void Stop(Status) override;
  void Win() override;
  void Lose() override;
};

#endif  // CANNONMIMIGAME_H
