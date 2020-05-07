#include "src/game/gamewidget.h"

#include <QStackedLayout>
#include <QtMath>

#include "src/game/minigames/cannon/cannonmimigame.h"
#include "src/game/minigames/juggling/jugglingminigame.h"
#include "src/game/minigames/test/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::GameWidget) {
  ui_->setupUi(this);
  ui_->ui_game_view_->SetUp(width_, height_);

  connect(ui_->ui_score_page_, &ScorePage::Expired, this,
          &GameWidget::StartMinigame);
  connect(ui_->ui_score_page_, &ScorePage::Paused, this, &GameWidget::Pause);
  connect(ui_->ui_score_page_, &ScorePage::Retried, this, &GameWidget::Retry);
  connect(ui_->ui_score_page_, &ScorePage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);

  connect(ui_->ui_pause_page_, &PausePage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);
  connect(ui_->ui_pause_page_, &PausePage::Resume, this, &GameWidget::Resume);
}

void GameWidget::ReturnToMainMenu() {
  SetMinigame(nullptr);
  emit MainMenu();
}

void GameWidget::Pause() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_pause_page_);
}

void GameWidget::Resume() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_score_page_);
  ui_->ui_score_page_->Resume();
}

void GameWidget::Retry() { SetUp(); }

void GameWidget::InitMinigame() {
  // Some game picking logic should be here
  Minigame* minigame =
      new Cannonmimigame(ui_->ui_game_view_, current_difficulty_);
  SetMinigame(minigame);
  current_minigame_->Init();
}

void GameWidget::StartMinigame() {
  if (current_minigame_ == nullptr) {
    return;
  }
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_game_page_);
  connect(current_minigame_, &Minigame::Passed, this,
          &GameWidget::MinigamePassed);
  connect(current_minigame_, &Minigame::Failed, this,
          &GameWidget::MinigameFailed);
  current_minigame_->Start();
}

void GameWidget::ShowScore() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_score_page_);
  ui_->ui_score_page_->Animate();
}

void GameWidget::Lose() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_score_page_);
  SetMinigame(nullptr);
}

void GameWidget::MinigamePassed(int32_t score) {
  ui_->ui_score_page_->MiniGamePassed(score);
  ShowScore();
  // To increase difficulty staying in (0, 1)
  current_difficulty_ = qPow(current_difficulty_, kDifficultyPower);
  InitMinigame();
}

void GameWidget::MinigameFailed() {
  ui_->ui_score_page_->MiniGameFailed();
  if (ui_->ui_score_page_->GetLivesCount() > 0) {
    ShowScore();
    InitMinigame();
  } else {
    Lose();
  }
}

GameWidget::~GameWidget() {
  SetMinigame(nullptr);
  delete ui_;
}

void GameWidget::SetUp() {
  current_difficulty_ = kStartDifficulty_;
  // QStackedWidget doesn't resize widgets,
  // that were not visible before, but
  // ui_score_page_ needs to know its width in SetUp()
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_score_page_);
  ui_->ui_score_page_->SetUp();
  ShowScore();
  InitMinigame();
}

void GameWidget::SetMinigame(Minigame* minigame) {
  delete current_minigame_;
  current_minigame_ = minigame;
  ui_->ui_game_view_->SetMinigame(minigame);
}
