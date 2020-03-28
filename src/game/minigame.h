#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsView>

class MiniGame {
 public:
  MiniGame(QGraphicsView* render_area, double difficulty);
  virtual ~MiniGame() = default;

  virtual void Start() = 0;
  virtual void Win() = 0;
  virtual void Lose() = 0;
  virtual void Update() = 0;  // One frame changes according to game logic

 private:
  QGraphicsView* render_area_;  // All mini-game graphics is drawn here

  double difficulty_;
};

#endif  // MINIGAME_H
