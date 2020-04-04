#include "pausepage.h"

#include <QMouseEvent>

#include "ui_pausepage.h"

PausePage::PausePage(QWidget* parent) : QWidget(parent), ui(new Ui::PausePage) {
  ui->setupUi(this);
  QPalette pal = palette();
  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  this->setAutoFillBackground(true);
  this->setPalette(pal);
}

void PausePage::EmitMainMenu() { emit MainMenu(); }

void PausePage::mousePressEvent(QMouseEvent*) {
  //  event->ignore();
  emit Resume();
}
