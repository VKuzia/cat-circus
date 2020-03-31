#include "src/game/gamewidget.h"

#include "src/game/minigames/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  ui->setupUi(this);
  ui->_graphics_view->setScene(new QGraphicsScene());
}

void GameWidget::ReturnToMainMenu() { emit MainMenu(); }

void GameWidget::InitMiniGame() {
  // Some game picking logic should be here
  // This version is used to implement MiniGame switch
  current_minigame_ = new TestMiniGame(ui->_graphics_view, 1);
}

void GameWidget::StartMiniGame() {
  if (current_minigame_ != nullptr) {
    current_minigame_->Start();
  }
}

GameWidget::~GameWidget() { delete ui; }

void GameWidget::SetUp() {
  InitMiniGame();
  StartMiniGame();
}
