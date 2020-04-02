#include "src/game/gamewidget.h"

#include "src/game/minigames/testminigame.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  ui->setupUi(this);
  ui->_graphics_view->setScene(new QGraphicsScene());
  ui->_graphics_view->scene()->setSceneRect(
      -this->width() / 2, -this->height() / 2, this->width(), this->height());

  connect(ui->_points_page, &PointsPage::Expired, this,
          &GameWidget::StartMiniGame);

  // To prevent mouse focus when mousePressEvent is triggered.
  // Now input focus is always on GameWidget.
  ui->_graphics_view->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void GameWidget::ReturnToMainMenu() { emit MainMenu(); }

void GameWidget::InitMiniGame() {
  // Some game picking logic should be here
  // This version is used only to implement MiniGame switch
  current_minigame_ = new TestMiniGame(ui->_graphics_view, 1);
}

void GameWidget::StartMiniGame() {
  if (current_minigame_ != nullptr) {
    ui->_stacked_widget->setCurrentWidget(ui->_game_page);
    connect(current_minigame_, &MiniGame::Passed, this,
            &GameWidget::SetPointsPage);
    current_minigame_->Start();
  }
}

void GameWidget::SetPointsPage() {
  ui->_stacked_widget->setCurrentWidget(ui->_points_page);
  ui->_points_page->Animate();
  // We will need to change to another game here soon
  if (current_minigame_ != nullptr) {
    delete current_minigame_;
    current_minigame_ = nullptr;
  }
  InitMiniGame();
}

GameWidget::~GameWidget() { delete ui; }

void GameWidget::SetUp() {
  InitMiniGame();
  SetPointsPage();
}
void GameWidget::mousePressEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MousePressEvent(event);
  }
}

void GameWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MouseReleaseEvent(event);
  }
}

void GameWidget::mouseMoveEvent(QMouseEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->MouseMoveEvent(event);
  }
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->KeyPressEvent(event);
  }
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) {
  if (current_minigame_ != nullptr) {
    current_minigame_->KeyReleaseEvent(event);
  }
}
