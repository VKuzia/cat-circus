#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "src/game/minigame.h"

class TestMiniGame : public MiniGame {
  Q_OBJECT
 public:
  TestMiniGame(QGraphicsView* graphics_view, qreal difficulty);
  ~TestMiniGame() override;

  void Start() override;
  void Pause() override;
  void Resume() override;

 signals:

 public slots:

 private:
  int32_t kBasicDuration = 3000;

  void Stop() override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
