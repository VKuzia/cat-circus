#include "aboutwidget.h"

#include <QResizeEvent>

#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::AboutWidget) {
  ui_->setupUi(this);
}

void AboutWidget::ReturnToMainMenu() { emit MainMenu(); }

void AboutWidget::resizeEvent(QResizeEvent* event) {
  qreal scale = event->size().width() * 1.0 / event->oldSize().width();
  if (scale < 0.1) {
    return;
  }
  ui_->ui_return_button_->Resize(scale);
}

AboutWidget::~AboutWidget() { delete ui_; }
