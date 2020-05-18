#include "aboutwidget.h"

#include <QResizeEvent>

#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::AboutWidget) {
  ui_->setupUi(this);
}

void AboutWidget::ReturnToMainMenu() { emit MainMenu(); }

void AboutWidget::resizeEvent(QResizeEvent* event) {
  ui_->ui_return_button_->Resize(event);
}

AboutWidget::~AboutWidget() { delete ui_; }
