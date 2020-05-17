#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

  void AnimateLoading();
  void SetGamePage();

  void SetStyle();
};

#endif  // MAINWINDOW_H
