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
  int32_t width_ = 1024;
  int32_t height_ = 576;
  Ui::GameWidget* ui;
  MiniGame* current_minigame_ = nullptr;

  qreal current_difficulty_ = 0;

  void InitMiniGame();
  void StartMiniGame();
  void ShowPoints();

  // Also deletes non-nullptr mini-games
  void SetMiniGame(MiniGame* minigame);

  void MiniGamePassed(int64_t score);
  void MiniGameFailed();
};

#endif  // GAMEWIDGET_H
