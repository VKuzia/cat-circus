#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(int32_t width, int32_t height, QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void ChangeToMainMenu();
  void ChangeToGame();
  void ChangeToSettings();
  void ChangeToAbout();
  void Exit();

 private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
