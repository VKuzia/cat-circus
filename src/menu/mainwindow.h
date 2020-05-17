#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void SetUp();

 public slots:
  void ChangeWidget();
  void ChangeToMainMenu();
  void ChangeToGame();
  void ChangeToSettings();
  void ChangeToAbout();
  void Exit();

 private:
  const QString kPathToBackground_ =
      QDir::currentPath() + "/data/images/background/main_background.gif";

  Ui::MainWindow* ui_;
  QWidget* widget_to_change_to_ = nullptr;

  void AnimateLoading();
  void SetGamePage();

  void resizeEvent(QResizeEvent* event) override;
};

#endif  // MAINWINDOW_H
