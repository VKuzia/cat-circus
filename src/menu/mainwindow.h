#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/utility/infomanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(InfoManager *info, QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void ChangeToMainMenu();
  void ChangeToGame();
  void ChangeToSettings();
  void ChangeToAbout();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
