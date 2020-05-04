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

  void SetUp(const QSize& resolution);

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();
  void Pause();
  void Resume();
  void Retry();

 private:
  const float kDifficultyPower = 0.9f;
  const float kStartDifficulty_ = 0.1f;

  float current_difficulty_ = kStartDifficulty_;
  Ui::GameWidget* ui_;
  Minigame* current_minigame_ = nullptr;

  void InitMinigame();
  void StartMinigame();
  void ShowScore();
  void Lose();

  // Also deletes non-nullptr mini-games
  void SetMinigame(Minigame* minigame);

  void MinigamePassed(int32_t score);
  void MinigameFailed();
};

#endif  // GAMEWIDGET_H
