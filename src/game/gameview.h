#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

#include "src/game/minigame.h"

class GameView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GameView(QWidget* parent = nullptr);

  void SetUp(int32_t width, int32_t height);

  void SetMiniGame(MiniGame* current_minigame);

 signals:

 public slots:

 private:
  MiniGame* current_minigame_ = nullptr;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
