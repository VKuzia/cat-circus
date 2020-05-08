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
  const QPixmap kUp =
      QPixmap(QDir::currentPath() + "/data/images/minigames/trampoline/up.png");
  const QPixmap kDown = QPixmap(QDir::currentPath() +
                                "/data/images/minigames/trampoline/down.png");
  const QPixmap kLeft = QPixmap(QDir::currentPath() +
                                "/data/images/minigames/trampoline/left.png");
  const QPixmap kRight = QPixmap(QDir::currentPath() +
                                 "/data/images/minigames/trampoline/right.png");

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  const QPen kMousePathPen = QPen(QBrush(QColor::fromRgb(200, 0, 0, 150)), 5);
  const int32_t kMousePathFadeAwayTime = 2000;

  const qreal kCatWidth = 1.5;
  const qreal kCatHeight = 1.5;
  const QPointF kCatStartPos = QPointF(-3.5, -2.5);
  const qreal kCatFlipHeight = -2;
  const Vector2D kWrongVelocity = {8, -9.5};

  const int32_t kCorrectFlipTime = 1000;
  const int32_t kIncorrectFlipTime = 2500;

  const qreal kTileWidth = 1.2;
  const qreal kTileHeight = 1.2;
  const qreal kTileX = 3.5;
  const qreal kTileXInterval = 0.4;
  const qreal kTileY = -2.5;

  const qreal kTrampolineWidth = 3;
  const qreal kTrampolineHeight = 1.5;
  const QPointF kTrampolineStartPos = QPointF(-3.5, 3);

  const int32_t kFlyAwayTime = 2800;

  TrampolineCat* cat_ = nullptr;
  Trampoline* trampoline_ = nullptr;
  TrampolinePath* current_mouse_path_ = nullptr;
  QVector<TrampolineTile*> tiles_;
  QPointF last_mouse_pressed_;
  QPointF first_mouse_pressed_;
  int32_t flip_count_ = 0;
  int32_t flip_time_ = 0;
  int32_t swipe_count_ = 0;
  int32_t current_swipe_count_ = 0;
  bool is_mouse_pressed_ = false;
  bool is_successful_flip_ = false;
  bool is_making_flip_ = false;
  bool is_lost_ = false;

  void MakeFlip();
  void PrepareTiles();
  void SetTilesVisible(bool visible);
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
