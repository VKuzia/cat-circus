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

  void MousePressEvent(QMouseEvent* event) override;
  void MouseReleaseEvent(QMouseEvent* event) override;
  void MouseMoveEvent(QMouseEvent* event) override;
  void KeyPressEvent(QKeyEvent* event) override;
  void KeyReleaseEvent(QKeyEvent* event) override;

 signals:

 public slots:

 private:
  int32_t kBasicDuration = 3000;

  void Stop() override;
  void Win() override;
  void Lose() override;
};

#endif  // TESTMINIGAME_H
