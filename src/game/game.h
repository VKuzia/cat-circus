#ifndef GAME_H
#define GAME_H

#include <QString>

#include "src/menu/mainwindow.h"
#include "src/utility/infomanager.h"

class Game {
 public:
  explicit Game(InfoManager* info);
  void Start();

 public slots:

 private:
  InfoManager* info_;  // Contains game data
  MainWindow window_;  // Has no parent, every widget is its child
};

#endif  // GAME_H
