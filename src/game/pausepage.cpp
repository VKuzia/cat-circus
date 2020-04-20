#include "pausepage.h"

#include <QMouseEvent>

#include "ui_pausepage.h"

PausePage::PausePage(QWidget* parent)
    : QWidget(parent), ui_(new Ui::PausePage) {
  ui_->setupUi(this);
}

void PausePage::ReturnToMainMenu() { emit MainMenu(); }

void PausePage::mousePressEvent(QMouseEvent*) { emit Resume(); }
