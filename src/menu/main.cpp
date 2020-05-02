#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "src/game/game.h"

void Start() {
  Game* game = new Game();
  game->Start();
}

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Start();
  return a.exec();
}
