#ifndef GAME_H
#define GAME_H

#include <QString>

#include "src/menu/mainwindow.h"

class Game {
 public:
  Game();

  void Start();

 private:
  int32_t width_ = 1024;
  int32_t height_ = 576;
  MainWindow window_;
};

#endif  // GAME_H
