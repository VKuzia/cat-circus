#include "settingswidget.h"

#include "mainwindow.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);
}

void SettingsWidget::ReturnToMainMenu() { emit MainMenu(); }

SettingsWidget::~SettingsWidget() {}
