#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsView>

class MiniGame {
 public:
  MiniGame(QGraphicsView* render_area, double difficulty_);
  virtual ~MiniGame();

  virtual void Start() = 0;   // starts the game loop
  virtual void Win() = 0;     // actions if player wins
  virtual void Lose() = 0;    // actoins if player loses
  virtual void Update() = 0;  // one frame update according to game logic

 private:
  QGraphicsView* render_area_;  // game graphics is drawn here

  double difficulty_;  // shows how difficult (how fast) should be the game
};

#endif  // MINIGAME_H
