#include "src/game/gamewidget.h"

#include <QStackedLayout>

#include "src/game/minigames/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  ui->setupUi(this);
  ui->ui_game_view->SetUp(width_, height_);

  connect(ui->ui_points_page, &PointsPage::Expired, this,
          &GameWidget::StartMiniGame);
  connect(ui->ui_points_page, &PointsPage::Paused, this, &GameWidget::Pause);
  connect(ui->ui_points_page, &PointsPage::Retryed, this, &GameWidget::Retry);
  connect(ui->ui_points_page, &PointsPage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);

  connect(ui->ui_pause_page, &PausePage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);
  connect(ui->ui_pause_page, &PausePage::Resume, this, &GameWidget::Resume);
}

void GameWidget::ReturnToMainMenu() {
  SetMiniGame(nullptr);
  emit MainMenu();
}

void GameWidget::Pause() {
  ui->_stacked_widget->setCurrentWidget(ui->ui_pause_page);
}

void GameWidget::Resume() {
  ui->_stacked_widget->setCurrentWidget(ui->ui_points_page);
  ui->ui_points_page->Resume();
}

void GameWidget::Retry() { SetUp(); }

void GameWidget::InitMiniGame() {
  if (current_minigame_ != nullptr) {
    delete current_minigame_;
  }
  // Some game picking logic should be here
  // This version is used only to implement MiniGame switch
  current_difficulty_ = qMin(0.85, current_difficulty_ + 0.1);
  MiniGame* minigame = new TestMiniGame(ui->ui_game_view, current_difficulty_);
  SetMiniGame(minigame);
}

void GameWidget::StartMiniGame() {
  if (current_minigame_ != nullptr) {
    ui->_stacked_widget->setCurrentWidget(ui->ui_game_page);
    connect(current_minigame_, &MiniGame::Passed, this,
            &GameWidget::MiniGamePassed);
    connect(current_minigame_, &MiniGame::Failed, this,
            &GameWidget::MiniGameFailed);
    current_minigame_->Start();
  }
}

void GameWidget::ShowPoints() {
  ui->_stacked_widget->setCurrentWidget(ui->ui_points_page);
  ui->ui_points_page->Animate();
  // We will need to change to another game here soon
  InitMiniGame();
}

void GameWidget::MiniGamePassed(int64_t score) {
  ui->ui_points_page->MiniGamePassed(score);
  ShowPoints();
}

void GameWidget::MiniGameFailed() {
  ui->ui_points_page->MiniGameFailed();
  ShowPoints();
}

GameWidget::~GameWidget() { delete ui; }

void GameWidget::SetUp() {
  current_difficulty_ = 0;
  /* QStackedWidget doesn't resize widgets,
      that were not visible before, but
      _points_page needs to know its width in SetUp() */
  ui->_stacked_widget->setCurrentWidget(ui->ui_points_page);
  ui->ui_points_page->SetUp();
  ShowPoints();
}

void GameWidget::SetMiniGame(MiniGame* minigame) {
  current_minigame_ = minigame;
  ui->ui_game_view->SetMiniGame(minigame);
}
