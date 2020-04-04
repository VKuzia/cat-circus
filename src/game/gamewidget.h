#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

#include "src/game/minigame.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget {
  Q_OBJECT

 public:
  explicit GameWidget(QWidget* parent = nullptr);
  ~GameWidget() override;

  void SetUp();

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();
  void Pause();
  void Resume();
  void Retry();

 private:
  Ui::GameWidget* ui;
  MiniGame* current_minigame_ = nullptr;

  qreal current_difficulty_ = 0;

  void InitMiniGame();
  void StartMiniGame();
  void ShowPoints();

  void MiniGamePassed(int64_t score);
  void MiniGameFailed();

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEWIDGET_H
