#ifndef TRAMPOLINEMINIGAME_H
#define TRAMPOLINEMINIGAME_H

#include <QDir>

#include "src/game/minigame.h"
#include "src/game/minigames/trampoline/trampoline.h"
#include "src/game/minigames/trampoline/trampolinecat.h"
#include "src/game/minigames/trampoline/trampolinepath.h"
#include "src/game/minigames/trampoline/trampolinetile.h"

class TrampolineMinigame : public Minigame {
  Q_OBJECT

 public:
  TrampolineMinigame(GameView* game_view, qreal difficulty,
                     qreal pixels_in_meter = 576 / 8.0);
  ~TrampolineMinigame() override = default;

  void Start() override;

  void MousePressEvent(QMouseEvent*) override;
  void MouseReleaseEvent(QMouseEvent*) override;
  void MouseMoveEvent(QMouseEvent*) override;

 private:
  const QBrush kEmptyBackgroundBrush_ = Qt::NoBrush;
  const QBrush kWinBackgroundBrush_ = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush_ = QBrush(QColor::fromRgb(191, 8, 8));

  const QPen kMousePathPen_ = QPen(QBrush(QColor::fromRgb(200, 0, 0, 150)), 5);
  const int32_t kMousePathFadeAwayTime_ = 2000;

  const QSizeF kCatSize_ = {1.5, 1.5};
  const QPointF kCatStartPos_ = QPointF(-3.5, -2.5);
  const QPointF kFailAimPoint_ = {8, -1.5};
  const qreal kCatFlipY_ = -2;

  const int32_t kCorrectFlipTime_ = 1000;
  const int32_t kIncorrectFlipTime_ = 2500;

  const QSizeF kTileSize_ = {1.2, 1.2};
  const QPointF kTileCentrePos_ = {3.5, -2.5};
  const qreal kTileXInterval_ = 0.4;

  const QSizeF kTrampolineSize_ = {3, 1.5};
  const QPointF kTrampolineStartPos_ = QPointF(-3.5, 3);
  const qreal kTrampolineDepth_ = 0.5;

  const int32_t kFailFlyAwayTime_ = 1200;

  TrampolineCat* cat_ = nullptr;
  Trampoline* trampoline_ = nullptr;
  TrampolinePath* current_mouse_path_ = nullptr;
  QVector<TrampolineTile*> tiles_;
  int32_t flip_count_ = 0;
  int32_t flip_time_ = 0;
  int32_t swipe_count_ = 0;
  int32_t remaining_swipe_count_ = 0;
  bool is_mouse_pressed_ = false;
  bool is_successful_flip_ = false;
  bool is_making_flip_ = false;
  bool is_failed_ = false;

  void PrepareTiles();
  void SetTilesVisible(bool visible);
  void StartFlip();
  void FinishTile();
  void FinishFlip();

  void SetUp() override;
  void SetUpLabel() override;
  void SetUpParameters() override;
  void SetUpTiles();

  void AnimateTutorial() override;
  void StartGame() override;
  void AnimateOutro() override;

  void Tick() override;

  void Stop(Status) override;
  void Win() override;
  void Lose() override;
};

#endif  // TRAMPOLINEMINIGAME_H
