#include "pausepage.h"

#include <QMouseEvent>

#include "ui_pausepage.h"

PausePage::PausePage(QWidget* parent)
    : QWidget(parent), ui(new Ui::PausePage) {}

void PausePage::EmitMainMenu() { emit MainMenu(); }

void PausePage::mousePressEvent(QMouseEvent*) { emit Resume(); }
