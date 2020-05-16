#ifndef GAME_H
#define GAME_H

#include "src/menu/mainwindow.h"

class Game {
 public:
  Game();
  ~Game() = default;

  void Start();

 private:
  MainWindow window_;
};

#endif  // GAME_H
