#include "settingswidget.h"

#include "mainwindow.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);
}

void SettingsWidget::ReturnToMainMenu() { emit MainMenu(); }

void SettingsWidget::TurnVolume()
{
    if (ui_->ui_sound_check_box_->isChecked()) {
        ui_->ui_sound_check_box_->setText("Off");
    }
    else {
        ui_->ui_sound_check_box_->setText("On");
    }
}

SettingsWidget::~SettingsWidget() { delete ui_; }

void SettingsWidget::on_ui_sound_check_box__stateChanged(int arg1)
{
    TurnVolume();
}
