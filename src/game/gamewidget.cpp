#include "src/game/gamewidget.h"

#include <QStackedLayout>

#include "src/game/minigames/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  ui->setupUi(this);
  ui->_game_view->SetUp(width_, height_);
  // To prevent mouse focus when mousePressEvent is triggered.
  // Now input focus is always on GameWidget.

  connect(ui->_points_page, &PointsPage::Expired, this,
          &GameWidget::StartMiniGame);
  connect(ui->_points_page, &PointsPage::Paused, this, &GameWidget::Pause);
  connect(ui->_points_page, &PointsPage::Retryed, this, &GameWidget::Retry);
  connect(ui->_points_page, &PointsPage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);

  connect(ui->_pause_page, &PausePage::MainMenu, this,
          &GameWidget::ReturnToMainMenu);

  connect(ui->_pause_page, &PausePage::Resume, this, &GameWidget::Resume);
}

void GameWidget::ReturnToMainMenu() {
  if (current_minigame_ != nullptr) {
    ui->_game_view->SetMiniGame(nullptr);
    current_minigame_ = nullptr;
  }
  emit MainMenu();
}

void GameWidget::Pause() {
  //  ui->_points_page->setVisible(true);
  ui->_stacked_widget->setCurrentWidget(ui->_pause_page);
}

void GameWidget::Resume() {
  ui->_stacked_widget->setCurrentWidget(ui->_points_page);
  ui->_points_page->Resume();
}

void GameWidget::Retry() { SetUp(); }

void GameWidget::InitMiniGame() {
  if (current_minigame_ != nullptr) {
    ui->_game_view->SetMiniGame(nullptr);
  }
  // Some game picking logic should be here
  // This version is used only to implement MiniGame switch
  current_difficulty_ = qMin(0.85, current_difficulty_ + 0.1);
  current_minigame_ = new TestMiniGame(ui->_game_view, current_difficulty_);
  ui->_game_view->SetMiniGame(current_minigame_);
}

void GameWidget::StartMiniGame() {
  if (current_minigame_ != nullptr) {
    ui->_stacked_widget->setCurrentWidget(ui->_game_page);
    connect(current_minigame_, &MiniGame::Passed, this,
            &GameWidget::MiniGamePassed);
    connect(current_minigame_, &MiniGame::Failed, this,
            &GameWidget::MiniGameFailed);
    current_minigame_->Start();
  }
}

void GameWidget::ShowPoints() {
  ui->_stacked_widget->setCurrentWidget(ui->_points_page);
  ui->_points_page->Animate();
  // We will need to change to another game here soon

  InitMiniGame();
}

void GameWidget::MiniGamePassed(int64_t score) {
  ui->_points_page->MiniGamePassed(score);
  ShowPoints();
}

void GameWidget::MiniGameFailed() {
  ui->_points_page->MiniGameFailed();
  ShowPoints();
}

GameWidget::~GameWidget() { delete ui; }

void GameWidget::SetUp() {
  current_difficulty_ = 0;
  InitMiniGame();
  ui->_stacked_widget->setCurrentWidget(ui->_points_page);
  ui->_points_page->SetUp();
  ShowPoints();
}
