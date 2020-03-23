#include <QApplication>
#include <QMessageBox>

//  #include "mainwindow.h"
//  #include "src/game/game.h"
//  #include "src/utility/infomanager.h"

void Start() {
  //  InfoManager info_manager;
  //  if (info_manager.LoadInfo(":/data/data.txt")) {
  //    Game* game = new Game(&info_manager);
  //    game->Start();
  //  } else {
  //    QMessageBox::critical(nullptr, "Unable to read info",
  //                          "Couldn't open game file\n");
  //    QApplication::exit(1);
  //  }
}

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  //  Start();
  return a.exec();
}
