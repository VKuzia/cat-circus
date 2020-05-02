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
  int level = 0;

 public slots:
  void ChangeToMainMenu(int score);
  void ChangeToMainMenu();
  void ChangeToGame();
  void ChangeToSettings();
  void ChangeToAbout();
  void Exit();

 private slots:
  void on_ui_stacked_widget_windowIconChanged(const QIcon &icon);

 private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
