#include "src/game/gamewidget.h"

#include <QStackedLayout>

#include "src/game/minigames/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::GameWidget) {
  ui_->setupUi(this);
  ui_->ui_game_view_->SetUp(width_, height_);

  connect(ui_->ui_points_page_, &PointsPage::Expired, this,
          &GameWidget::StartMinigame);
  connect(ui_->ui_points_page_, &PointsPage::Paused, this, &GameWidget::Pause);
  connect(ui_->ui_points_page_, &PointsPage::Retryed, this, &GameWidget::Retry);
  connect(ui_->ui_points_page_, &PointsPage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);

  connect(ui_->ui_pause_page_, &PausePage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);
  connect(ui_->ui_pause_page_, &PausePage::Resume, this, &GameWidget::Resume);
}

void GameWidget::ReturnToMainMenu() {
  if (current_minigame_ != nullptr) {
    delete current_minigame_;
  }
  SetMinigame(nullptr);
  emit MainMenu();
}

void GameWidget::Pause() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_pause_page_);
}

void GameWidget::Resume() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_points_page_);
  ui_->ui_points_page_->Resume();
}

void GameWidget::Retry() { SetUp(); }

void GameWidget::InitMinigame() {
  if (current_minigame_ != nullptr) {
    delete current_minigame_;
  }
  // Some game picking logic should be here
  // This version is used only to implement MiniGame switch
  current_difficulty_ = qMin(0.85f, current_difficulty_ + 0.1f);
  Minigame* minigame =
      new TestMinigame(ui_->ui_game_view_, current_difficulty_);
  SetMinigame(minigame);
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

void GameWidget::ShowPoints() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_points_page_);
  ui_->ui_points_page_->Animate();
  // We will need to change to another game here soon
  InitMinigame();
}

void GameWidget::MinigamePassed(int64_t score) {
  ui_->ui_points_page_->MiniGamePassed(score);
  ShowPoints();
}

void GameWidget::MinigameFailed() {
  ui_->ui_points_page_->MiniGameFailed();
  ShowPoints();
}

GameWidget::~GameWidget() { delete ui_; }

void GameWidget::SetUp() {
  current_difficulty_ = 0;
  // QStackedWidget doesn't resize widgets,
  // that were not visible before, but
  // ui_points_page_ needs to know its width in SetUp()
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_points_page_);
  ui_->ui_points_page_->SetUp();
  ShowPoints();
}

void GameWidget::SetMinigame(Minigame* minigame) {
  current_minigame_ = minigame;
  ui_->ui_game_view_->SetMinigame(minigame);
}
