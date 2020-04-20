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
  Ui::GameWidget* ui_;
  Minigame* current_minigame_ = nullptr;

  float current_difficulty_ = 0;

  void InitMinigame();
  void StartMinigame();
  void ShowPoints();

  // Also deletes non-nullptr mini-games
  void SetMinigame(Minigame* minigame);

  void MinigamePassed(int64_t score);
  void MinigameFailed();
};

#endif  // GAMEWIDGET_H
