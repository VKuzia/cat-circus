#include "pausepage.h"

#include <QMouseEvent>
#include <QResizeEvent>

#include "ui_pausepage.h"

PausePage::PausePage(QWidget* parent)
    : QWidget(parent), ui_(new Ui::PausePage) {
  ui_->setupUi(this);
}

PausePage::~PausePage() { delete ui_; }

void PausePage::ReturnToMainMenu() { emit MainMenu(); }

void PausePage::mousePressEvent(QMouseEvent*) { emit Resume(); }

void PausePage::resizeEvent(QResizeEvent* event) {
  qreal scale = event->size().width() * 1.0 / event->oldSize().width();
  if (scale < 0.1) {
    return;
  }
  ui_->ui_main_menu_button_->Resize(scale);
}
