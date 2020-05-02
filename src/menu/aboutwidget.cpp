#include "aboutwidget.h"

#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::AboutWidget) {
  ui->setupUi(this);
}

void AboutWidget::ReturnToMainMenu() { emit MainMenu(); }

AboutWidget::~AboutWidget() { delete ui; }
