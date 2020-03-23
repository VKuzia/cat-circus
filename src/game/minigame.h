#ifndef MINIGAME_H
#define MINIGAME_H
#include <QGraphicsView>

class MiniGame {
 public:
  MiniGame(QGraphicsView* render_area, double difficulty_);
  virtual ~MiniGame() = 0;

  virtual void Start() = 0;   // starts the game loop
  virtual void OnWin() = 0;   // actions if player wins
  virtual void OnLose() = 0;  // actoins if player loses
  virtual void Update() = 0;  // one frame update according to game logic

  // returns points scored; deletes content;
  // should be called after pregame_page is activeted
  virtual int64_t Delete() = 0;

 private:
  QGraphicsView* render_area_;  // render area; game graphics is here
  double difficulty_;  // shows how difficult (how fast) should be the game
};

#endif  // MINIGAME_H
