#include "aboutwidget.h"

#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::AboutWidget) {
  ui_->setupUi(this);
}

void AboutWidget::ReturnToMainMenu() { emit MainMenu(); }

AboutWidget::~AboutWidget() { delete ui_; }
