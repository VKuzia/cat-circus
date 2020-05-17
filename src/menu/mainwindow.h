#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "audio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void SetUp();

 public slots:
  void ChangeWidget();
  void ChangeToMainMenu();
  void ChangeToGame();
  void ChangeToSettings();
  void ChangeToAbout();
  void Exit();

 private:
  Ui::MainWindow* ui_;
  QWidget* widget_to_change_to_ = nullptr;
  Audio* audio_;

  void AnimateLoading();
  void SetGamePage();
};

#endif  // MAINWINDOW_H
