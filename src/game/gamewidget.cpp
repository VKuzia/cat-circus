#include "src/game/gamewidget.h"

#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget) {
  ui->setupUi(this);
}

void GameWidget::ReturnToMainMenu() { emit MainMenu(); }

GameWidget::~GameWidget() { delete ui; }
