#include "src/game/gamewidget.h"

#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  //  , current_minigame_(nullptr)
  ui->setupUi(this);
}

void GameWidget::ReturnToMainMenu() { emit MainMenu(); }

GameWidget::~GameWidget() { delete ui; }
