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
  void KeyReleaseEvent(QKeyEvent* event) override;

 private:
  const int32_t kDuration = 3000;

  const QBrush kEmptyBackgroundBrush = Qt::NoBrush;
  const QBrush kKeyPressedBackgroundBrush = QBrush(QColor::fromRgb(0, 0, 200));
  const QBrush kWinBackgroundBrush = QBrush(QColor::fromRgb(10, 200, 10));
  const QBrush kLoseBackgroundBrush = QBrush(QColor::fromRgb(191, 8, 8));

  JugglingCat* cat_ = nullptr;
  QSet<JugglingBall*> balls_;
  QTimer ball_timer_;

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
