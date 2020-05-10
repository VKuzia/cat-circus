#ifndef UNICYCLEMINIGAME_H
#define UNICYCLEMINIGAME_H

#include "src/game/minigame.h"
#include "src/game/minigames/unicycle/unicyclecat.h"
#include "src/game/minigames/unicycle/unicycletiger.h"

class UnicycleMinigame : public Minigame {
 public:
  UnicycleMinigame(GameView* game_view, qreal difficulty,
                   qreal pixels_in_meter = 576 / 7.0);
  ~UnicycleMinigame() override = default;

  void Start() override;

  void KeyPressEvent(QKeyEvent* event) override;
  void KeyReleaseEvent(QKeyEvent* event) override;

 private:
  enum class CurrentKey { kAny, kLeft, kRight };

  const QBrush kEmptyBackgroundBrush_ = Qt::NoBrush;
  const QBrush kWinBackgroundBrush_ = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush_ = QBrush(QColor::fromRgb(191, 8, 8));

  const QPointF kCatStartPos_ = {-2.5, 1};
  const QSizeF kCatSize_ = {0.6, 1.5};
  const qreal kCatGoalX_ = 3;

  const QPointF kGratePos_ = {2.5, 1};
  const QSizeF kGrateSize_ = {0.5, 2};

  const QPointF kTigerStartPos_ = {-4.0, 1};
  const QSizeF kTigerSize_ = {2, 1.5};

  UnicycleCat* cat_ = nullptr;
  UnicycleTiger* tiger_ = nullptr;
  Vector2D cat_step_acceleration_;
  Vector2D tiger_velocity_;
  CurrentKey current_key_ = CurrentKey::kAny;

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

#endif  // UNICYCLEMINIGAME_H
