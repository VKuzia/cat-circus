#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

//  #include "src/game/minigame.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget {
  Q_OBJECT

 public:
  explicit GameWidget(QWidget *parent = nullptr);
  ~GameWidget();

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();

 private:
  Ui::GameWidget *ui;
  //  MiniGame *current_minigame_;  // minigame running now,
};

#endif  // GAMEWIDGET_H
